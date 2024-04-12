let pokemonRoute =
  Routes_build.make(
    ~route=Shared_native_demo.Pages.Pokemon.route,
    ~renderApp=
      initialProps => <Shared_native_demo.Pages.Pokemon initialProps />,
    ~initialProps=
      switch (Shared_native_demo.Pages.Pokemon.getInitialProps) {
      | Some(getInitialProps) => getInitialProps
      | None => (
          _ => Lwt.return(Shared_native_demo.Bindings.Json.from_string("{}"))
        )
      },
  );

let portalRoute =
  Routes_build.make(
    ~route=Shared_native_demo.Pages.Portal.route,
    ~renderApp=_ => <Shared_native_demo.Pages.Portal />,
    ~initialProps=
      switch (Shared_native_demo.Pages.Portal.getInitialProps) {
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
