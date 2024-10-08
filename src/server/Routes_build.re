open Lwt;

let indexFile = open_in_bin("./public/index.html");
let indexFileString =
  really_input_string(indexFile, in_channel_length(indexFile));

let appendUniversalStyles = (html) => {
  let soup = html |> Soup.parse;

  let stylesElement = (CSS.style_tag()) |> ReactDOM.renderToString |> Soup.parse;

  switch (soup |> Soup.select_one("head")) {
  | None => ()
  | Some(head) => Soup.append_child(head, stylesElement)
  };

  soup |> Soup.to_string;
};

let getQuery = (req, value) => Dream.query(req, value);

let make = (~path, ~renderApp, ~getInitialProps as getInitialPropsOpt) => [
  Dream.get(
    path,
    req => {
      let portals:
        ref(array(UniversalPortal_Shared.Portal.portal)) =
        ref([||]);

      let getInitialProps =
        switch (getInitialPropsOpt) {
        | Some(getInitialProps) => (
            req =>
              getInitialProps(req) >>= (props => Lwt.return(Some(props)))
          )
        | None => (_ => Lwt.return(None))
        };

      getInitialProps(req)
      >>= (
        props => {
          let html =
            ReactDOM.renderToString(
              UniversalPortal_Server.collectPortals(
                renderApp(props),
                (
                  collectedPortal: UniversalPortal_Shared.Portal.portal,
                ) => {
                portals := Array.append(portals^, [|collectedPortal|])
              }),
            );

          let initialPropsJson =
            switch (props) {
            | Some(props) =>
              "<script id=\"__DATA__\" type=\"application/json\">"
              ++ Shared_native_demo.Bindings.Json.to_string(props)
              ++ "</script>"
            | None => ""
            };

          Str.global_replace(
            Str.regexp("<div id=\"root\"></div>"),
            "<div id=\"root\">" ++ html ++ "</div>" ++ initialPropsJson,
            indexFileString,
          )
          |> UniversalPortal_Server.appendUniversalPortals(_, portals^)
          |> appendUniversalStyles
          |> Dream.html;
        }
      );
    },
  ),
  Dream.get(
    "/api/initial-props" ++ path,
    request => {
      let getInitialProps =
        switch (getInitialPropsOpt) {
        | Some(getInitialProps) => getInitialProps
        | None => (
            _ =>
              Lwt.return(
                Shared_native_demo.Bindings.Json.from_string("null"),
              )
          )
        };
      getInitialProps(request)
      >>= (
        props =>
          Shared_native_demo.Bindings.Json.to_string(props) |> Dream.json
      );
    },
  ),
];
