module Main = {
  [@react.component]
  let make = () => {
    <Routes_handler
      pathMappingDetails={path =>
        switch (path) {
        | route when route == Shared_js_demo.Pages.Pokemon.route => (
            (
              initialProps => {
                switch (initialProps) {
                | Some(props) =>
                  <Shared_js_demo.Pages.Pokemon initialProps=props />
                | None => <Shared_js_demo.Pages.Pokemon />
                };
              }
            ),
            Option.is_some(Shared_js_demo.Pages.Pokemon.getInitialProps),
          )
        | route when route == Shared_js_demo.Pages.Portal.route => (
            (_ => <Shared_js_demo.Pages.Portal />),
            Option.is_some(Shared_js_demo.Pages.Portal.getInitialProps),
          )
        | _ =>
          Js.log("No matching route found");
          ((_ => <div />), false);
        }
      }
    />;
  };
};
switch (ReactDOM.querySelector("#root")) {
| Some(el) => <Main /> |> ReactDOM.Client.hydrateRoot(el) |> ignore
| None => ()
};
