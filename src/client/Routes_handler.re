type nodeList;
type document;

let rec joinUrlPaths = paths =>
  switch (paths) {
  | [] => "/"
  | [hd] => "/" ++ hd
  | [hd, ...tail] => hd ++ "/" ++ joinUrlPaths(tail)
  };

[@react.component]
let make = (~pathMappingDetails: (string) => (module Shared_js_demo.DynamicRouting.LoaderPage)) => {
  let url = ReasonReactRouter.useUrl();
  let currentRoute = React.useRef(url.path |> joinUrlPaths);
  let (loading, setLoading) = React.useState(() => false);
  let (renderRoute, setRenderRoute) =
    React.useState(() => { 
      module P = (val pathMappingDetails(url.path |> joinUrlPaths));


      let initialProps =
        Webapi.Dom.(
          {
            switch (
              Option.is_some(P.getInitialProps),
              document |> Document.getElementById("__DATA__"),
            ) {
            | (true, Some(el)) =>
              let data =
                Element.innerText(el)
                |> Shared_js_demo.Bindings.Json.from_string;

              Some(data);
            | _ => None
            };
          }
        );

      P.make(initialProps)
    });

  React.useEffect1(
    () => {
      currentRoute.current == (url.path |> joinUrlPaths)
        ? ()
        : {
          setLoading(_ => true);
          module P = (val pathMappingDetails(url.path |> joinUrlPaths));

          if (Option.is_some(P.getInitialProps)) {
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
                   setRenderRoute(_ =>
                     P.make(Some(props))
                   );

                   () |> resolve;
                 })
              |> catch(_ => {
                   setRenderRoute(_ => P.make(None));

                   setLoading(_ => false);

                   () |> resolve;
                 })
              |> ignore
            );
          } else {
            setLoading(_ => false);
            setRenderRoute(_ => P.make(None));
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
