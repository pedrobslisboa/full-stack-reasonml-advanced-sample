type nodeList;
type document;

let rec joinUrlPaths = paths =>
  switch (paths) {
  | [] => "/"
  | [hd] => "/" ++ hd
  | [hd, ...tail] => hd ++ "/" ++ joinUrlPaths(tail)
  };

[@react.component]
let make = (~pathMappingDetails) => {
  let url = ReasonReactRouter.useUrl();
  let currentRoute = React.useRef(url.path |> joinUrlPaths);
  let (loading, setLoading) = React.useState(() => false);
  let (renderRoute, setRenderRoute) =
    React.useState(() => {
      let (renderRoute, hasInitialProps) =
        pathMappingDetails(url.path |> joinUrlPaths);

      let initialProps =
        Webapi.Dom.(
          {
            switch (
              hasInitialProps,
              document |> Document.getElementById("__DATA__"),
            ) {
            | (true, Some(el)) =>
              let data =
                Element.innerText(el)
                |> Shared_js_demo.Bindings.Json.from_string;

              data;
            | _ => Shared_js_demo.Bindings.Json.from_string("null")
            };
          }
        );

      renderRoute(initialProps);
    });

  React.useEffect1(
    () => {
      currentRoute.current == (url.path |> joinUrlPaths)
        ? ()
        : {
          setLoading(_ => true);
          let (renderRouteComponent, hasInitialProps) =
            pathMappingDetails(url.path |> joinUrlPaths);
          if (hasInitialProps) {
            Shared_js_demo.Bindings.Js.Promise.(
              Shared_js_demo.Bindings.Fetch.fetch(
                "/api/initial-props"
                ++ (url.path |> joinUrlPaths)
                ++ (
                  switch (url.search) {
                  | "" => ""
                  | search => "?" ++ search
                  }
                ),
              )
              |> then_(response =>
                   try(response |> Shared_js_demo.Bindings.Fetch.Response.json) {
                   | _ =>
                     Js.log("Error parsing JSON");
                     raise(Not_found);
                   }
                 )
              |> then_(props => {
                   setLoading(_ => false);
                   setRenderRoute(_ => renderRouteComponent(props));

                   () |> resolve;
                 })
              |> catch(_ => {
                   setRenderRoute(_ =>
                     renderRouteComponent(
                       Shared_js_demo.Bindings.Json.from_string("null"),
                     )
                   );

                   setLoading(_ => false);

                   () |> resolve;
                 })
              |> ignore
            );
          } else {
            setLoading(_ => false);
            setRenderRoute(_ =>
              renderRouteComponent(
                Shared_js_demo.Bindings.Json.from_string("null"),
              )
            );
          };
        };

      currentRoute.current = url.path |> joinUrlPaths;

      None;
    },
    [|url.path|],
  );

  UniversalPortal_Shared.Hooks.UseRemoveServerPortals.make();

  <>
    {loading ? <Shared_js_demo.Components.Loader /> : React.null}
    renderRoute
  </>;
};
