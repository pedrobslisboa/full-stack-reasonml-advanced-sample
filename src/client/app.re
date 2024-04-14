module type Route = {
  let route: string;
  let getInitialProps:
    option(
      (string => option(string)) =>
      Shared_js_demo.Bindings.Js.Promise.t(Shared_js_demo.Bindings.Json.t),
    );

  [@react.component]
  let make: (~initialProps: Shared_js_demo.Bindings.Json.t=?) => React.element;
};

module Route = (R: Route) => {
  let route = R.route;
  let make = () => {
    (
      initialProps => {
        switch (initialProps) {
        | Some(props) => <R initialProps=props />
        | None => <R />
        };
      },
      Option.is_some(R.getInitialProps),
    );
  };
};

module PokemonRoute = Route(Shared_js_demo.Pages.Pokemon.Make);
module PortalRoute = Route(Shared_js_demo.Pages.Portal.Make);

module Main = {
  [@react.component]
  let make = () => {
    <Routes_handler
      pathMappingDetails={path =>
        switch (path) {
        | route when route == PokemonRoute.route => PokemonRoute.make()
        | route when route == PortalRoute.route => PortalRoute.make()
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
