open Lwt;

let indexFile = open_in_bin("./public/index.html");
let indexFileString =
  really_input_string(indexFile, in_channel_length(indexFile));

let appendUniversalStyles = (html, styles) => {
  let soup = html |> Soup.parse;

  let stylesElement = "<style>" ++ styles ++ "</styles>" |> Soup.parse;

  switch (soup |> Soup.select_one("head")) {
  | None => ()
  | Some(head) => Soup.append_child(head, stylesElement)
  };

  soup |> Soup.to_string;
};

let getQuery = (req, value) => Dream.query(req, value);

let make = (~route, ~renderApp, ~initialProps) => [
  Dream.get(
    route,
    req => {
      let portals:
        ref(array(UniversalPortal_Shared.Components.Portal.portal)) =
        ref([||]);

      let cssStyles = CssJs.render_style_tag();

      initialProps(getQuery(req))
      >>= (
        props => {
          let html =
            ReactDOM.renderToString(
              UniversalPortal_Server.collectPortals(
                renderApp(props),
                (
                  collectedPortal: UniversalPortal_Shared.Components.Portal.portal,
                ) => {
                portals := Array.append(portals^, [|collectedPortal|])
              }),
            );

          Str.global_replace(
            Str.regexp("<div id=\"root\"></div>"),
            "<div id=\"root\">"
            ++ html
            ++ "</div><script id=\"__DATA__\" type=\"application/json\">"
            ++ Shared_native_demo.Bindings.Json.to_string(props)
            ++ "</script>",
            indexFileString,
          )
          |> UniversalPortal_Server.appendUniversalPortals(_, portals^)
          |> appendUniversalStyles(_, cssStyles)
          |> Dream.html;
        }
      );
    },
  ),
  Dream.get("/api/initial-props" ++ route, request => {
    initialProps(getQuery(request))
    >>= (
      props => Shared_native_demo.Bindings.Json.to_string(props) |> Dream.json
    )
  }),
];
