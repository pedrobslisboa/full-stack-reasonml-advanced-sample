// allow to create page directly on Shared_native_demo.Pages

let loadedRoutes = Shared_native_demo.Pages.loadedPages;

let dynamicRoutesList =
  loadedRoutes
  |> List.map((module M: Shared_native_demo.DynamicRouting.Loader_page) => {
       Routes_build.make(
         ~path=M.path,
         ~renderApp=initialProps => M.make(initialProps),
         ~getInitialProps=M.getInitialProps,
       )
     })
  |> List.flatten;

let handler =
  Dream.router([
    Dream.get("/public/**", Dream.static("./public")),
    ...dynamicRoutesList,
  ]);

let interface =
  switch (Sys.getenv_opt("SERVER_INTERFACE")) {
  | Some(env) => env
  | None => "localhost"
  };

let port =
  switch (Sys.getenv_opt("PORT")) {
  | Some(v) => v |> int_of_string
  | None => 8000
  };

Dream.run(~port, ~interface, handler);
