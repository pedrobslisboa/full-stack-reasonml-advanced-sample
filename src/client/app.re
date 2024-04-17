// allow to create page directly on Shared_js_demo.Pages

let loadedRoutes = Shared_js_demo.Pages.loadedPages |> Array.of_list;

module Main = {
  [@react.component]
  let make = () => {
    <Routes_handler
      pathMappingDetails={path =>
        loadedRoutes
        |> Array.find_opt(
             (module P: Shared_js_demo.DynamicRouting.Loader_page) =>
             P.path == path
           )
        |> (
          fun
          | Some((module P)) => (P.make, Option.is_some(P.getInitialProps))
          | None => ((_ => <div> {"404" |> React.string} </div>), false)
        )
      }
    />;
  };
};
switch (ReactDOM.querySelector("#root")) {
| Some(el) => <Main /> |> ReactDOM.Client.hydrateRoot(el) |> ignore
| None => ()
};
