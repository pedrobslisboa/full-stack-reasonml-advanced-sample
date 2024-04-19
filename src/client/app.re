// allow to create page directly on Shared_js_demo.Pages

let loadedRoutes = Shared_js_demo.Pages.loadedPages |> Array.of_list;

module NoRoute = {
  type props;
  let path = ""
  let getInitialProps = None
  let make = (_) => <div> {"404" |> React.string} </div>
  let decodeProps = None;
}

module Main = {
  [@react.component]
  let make = () => {
    <Routes_handler
      pathMappingDetails={path =>
        loadedRoutes
        |> Array.find_opt(
             (module P: Shared_js_demo.DynamicRouting.LoaderPage) =>
             P.path == path
           )
        |> (
          fun
          | Some((module P)) => ((module P): (module Shared_js_demo.DynamicRouting.LoaderPage))
          | None => (module NoRoute)
        )
      }
    />;
  };
};
switch (ReactDOM.querySelector("#root")) {
| Some(el) => <Main /> |> ReactDOM.Client.hydrateRoot(el) |> ignore
| None => ()
};
