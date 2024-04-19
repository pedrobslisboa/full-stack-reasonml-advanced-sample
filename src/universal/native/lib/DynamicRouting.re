module type Page = {
  type props;

  let getInitialProps:
    option(Bindings_Dream.request => Bindings.Js.Promise.t(Bindings.Json.t));
  let path: string;
  let make: (props) => React.element;
  let decodeProps: option(Bindings.Json.t) => props;
};

module type PageNoGetInitialProps = {
  let path: string;
  let make: unit => React.element;
};

module type LoaderPage = {
  type props;

  let getInitialProps:
    option(Bindings_Dream.request => Bindings.Js.Promise.t(Bindings.Json.t));
  let path: string;
  let make: option(Bindings.Json.t) => React.element;
};



let loadedRoutes: ref(list(module LoaderPage)) = ref([]);

let register = (module R: Page) => {
  module Route = {
    type props = R.props;


  let getInitialProps = R.getInitialProps;
  let path = R.path;
  let make = (json) => json |> R.decodeProps |> R.make
  };

  loadedRoutes := [((module Route): (module LoaderPage)), ...loadedRoutes^];
};

let registerNoInitialProps = (module R: PageNoGetInitialProps) => {
  module Route = {
    type props = unit;

    let path = R.path;
    let getInitialProps: option(Bindings_Dream.request => Bindings.Js.Promise.t(Bindings.Json.t)) = None
    let make = (_) => R.make();
  };

  loadedRoutes := [((module Route): (module LoaderPage)), ...loadedRoutes^];
};

let getLoadedRoutes = (): list(module LoaderPage) =>
  switch (loadedRoutes^) {
  | [] => failwith("There are no registered Pages")
  | pages => pages
  };
