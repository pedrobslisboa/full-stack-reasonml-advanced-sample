# Fullstack ReasonML Sample

## Table of Contents

- [Introduction](#introduction)
- [Installation](#installation)
- [Routing](#routing)
- [Running](#running)
- [License](#license)
- [Improvements](#improvements)

## Introduction

This is an advanced full-stack application using ReasonML and React. It serves as a sample project to demonstrate how to build an application with ReasonML and React, including a native ReasonML server.

You can access it here: https://native-reason-react-advanced-80387dde2d3c.herokuapp.com/

This project utilizes the following main libraries:

- reasonml
- reason-react
- server-reason-react
- melange
- styled-ppx (emotion)

Keep in mind that the project is still in development and may not be production-ready. It's just a sample project I'm having fun with. :)

## Routing

For an easy way to build and manage data flow, this project uses the `getInitialProps` system, which retrieves data from the server and passes it to the client. It supports both SPA and SSR functionalities.

Example:
```reason
open DynamicRouting;

loadedRoutes
|> register(
     ~path="/",
     ~getInitialProps=(_) => Binding.Json.from_string("Hello World"),
     ~component=initialProps =>
     <h1> {ReasonReact.string(initialProps |> Binding.Json.to_string)} </h1>
   );
   
// Register more routes here

let loadedPages = getLoadedRoutes();
```

The `~getInitialProps` is defined as:
```reason
let getInitialProps: option(Bindings_Dream.request => Bindings.Js.Promise.t(Bindings.Json.t));
```

It returns a promise with a JSON object which you must decode into your data at the component level.

The idea is to eventually provide a better way to construct a prop type with a built-in decoder, perhaps using a PPX, similar to `deriving yojson` but universal.

```reason
// Pages_Home.re
type props = [%json { name: string }];

let json = {
    name: "John"
};

let decodedProps = props_of_yojson(json);
let jsonProps = props_to_yojson(decodedProps);

// Pages.re
loadedRoutes
|> register(
     ~path=Pages_Home.path,
     ~getInitialProps=Pages_Home.getInitialProps,
     ~decode=Pages_Home.decode,
     ~component=(initialProps) => <Pages_Home.component ?initialProps />
   );
```

This approach aims to streamline data handling and type management, eliminating the need for manual decoding.

However, we still need to specify the decoder when registering routes. An alternative improvement is to deliver a module for route registration, allowing for better organization of routes and components.

```reason
open DynamicRouting;

loadedRoutes |> register((module Pages_Home): (module Binding.DynamicRouting.LoaderPage));
```

This method simplifies route registration without specifying a decoder or any module contract, facilitating better code organization.

Please note:
- I'm not sure if this is feasible with ReasonML, but it's worth exploring.
- I'm still mastering Universal ReasonML, so implementation may take some time.
- I welcome your collaboration. :)

## Installation

```sh
    make install
```

With Docker:

```sh
    make docker-build
```

## Running

```sh
    make run
```

With Docker:

```sh
    make docker-run
```

## License

MIT

## Improvements

- Increase test coverage.
    - Test custom hooks with the appropriate testing library.
- Enhance custom bindings.
- Improve error handling.
- Implement Git hooks.
- Set up CI/CD
