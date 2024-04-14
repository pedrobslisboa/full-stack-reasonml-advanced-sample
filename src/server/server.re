let pokemonRoute =
  Routes_build.make(
    ~route=Shared_native_demo.Pages.Pokemon.Make.route,
    ~renderApp=
      initialProps => <Shared_native_demo.Pages.Pokemon.Make initialProps />,
    ~initialProps=
      switch (Shared_native_demo.Pages.Pokemon.Make.getInitialProps) {
      | Some(getInitialProps) => getInitialProps
      | None => (
          _ => Lwt.return(Shared_native_demo.Bindings.Json.from_string("{}"))
        )
      },
  );

let getFolderContent = folder => Sys.readdir(folder);
let rec getRecursiveFolderContent = folder =>
  getFolderContent(folder)
  |> Array.map(file => {
       let path = folder ++ "/" ++ file;
       Sys.is_directory(path) ? getRecursiveFolderContent(path) : [path];
     })
  |> Array.to_list
  |> List.concat;

getRecursiveFolderContent("./src") |> List.iter(print_endline);

let portalRoute =
  Routes_build.make(
    ~route=Shared_native_demo.Pages.Portal.Make.route,
    ~renderApp=_ => <Shared_native_demo.Pages.Portal.Make />,
    ~initialProps=
      switch (Shared_native_demo.Pages.Portal.Make.getInitialProps) {
      | Some(getInitialProps) => getInitialProps
      | None => (
          _ => Lwt.return(Shared_native_demo.Bindings.Json.from_string("{}"))
        )
      },
  );

let handler =
  Dream.router([
    Dream.get("/public/**", Dream.static("./public")),
    ...List.concat([pokemonRoute, portalRoute]),
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
