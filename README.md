# Fullstack Reasonml Sample

## Table of Contents

- [Introduction](#introduction)
- [Installation](#installation)
- [Routing](#routing)
- [Running](#running)
- [License](#license)
- [Improvements](#improvements)

## Introduction

This is an advanced full-stack applicaiton with Reasonml and React.
It work as a sample project to show how to build an advanced application with Reasonml and React, with a native Reasonml server.

You can access here: https://native-reason-react-advanced-80387dde2d3c.herokuapp.com/

This project uses the following main libraries:

- reasnml
- reason-react
- server-reason-react
- melange
- styled-ppx (emotion)

Keep in mind that the project is still in development and I'm not sure it's production ready.
It's just a sample I'm having fun with. :)

## Routing

For a easy way to build and keep info together, this project works with getInitialProps system, that is a way to get data from server and pass to the client. Working on SPA and SSR.


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
   
// register more routes here

let loadedPages = getLoadedRoutes();
```

The `~getInitialProps` has the following contract:
```reason
let getInitialProps: option(Bindings_Dream.request => Bindings.Js.Promise.t(Bindings.Json.t));
```

So it returns a promise with a json object and you must decode the json object to your data at the component.

The idea is to in the future provide a better way to construct a prop type with buildt-in decoder, maybe with a ppx, similar to deriving yojson but universal.

```reason
// Pages_Home.re
type props = [%json { name: string }];

let json = {
    name: "John"
}

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

That way we would be able to have a better way to handle the data and the types, no decode needed.

But we still have to declare the decode for the register, the other way to improve it is to delivery a module to register the routes, so we can have a better way to organize the routes and the components.

```reason
open DynamicRouting;

loadedRoutes |> register((module Pages_Home): (module Binding.DynamicRouting.LoaderPage));
```

That way we don't need to have to declare on the register the decode or any module contract, we could have a better way to organize the code.

Keep in mind that:
- I don't know if it is possible to do that with Reasonml, but it is a good idea to try.
- I'm still learning Universal Reasonml, so it can take a while to implement it.
- You can help me with that. :)

## Installation

```sh
    Make install
```

With docker:

```sh
    Make docker-build
```

## Running

```sh
    Make run
```

With docker:

```sh
    Make docker-run
```

## License

MIT

## Improvements

- Increase test coverage.
    - Test custom hooks with proper testing library.
- Increase custom Bindings.
- Better error handling.
- Githooks
- CI/CD

