module type LoaderPage = {
  let getInitialProps:
    option(Bindings_Dream.request => Bindings.Js.Promise.t(Bindings.Json.t));
  let path: string;
  let make: option(Bindings_Json.t) => React.element;
};

let loadedRoutes: ref(list(module LoaderPage)) = ref([]);

let register = (~path, ~getInitialProps, ~component, loadedRoutes) => {
  module R = {
    let path = path;
    let getInitialProps = getInitialProps;
    let make = component;
  };

  loadedRoutes := [((module R): (module LoaderPage)), ...loadedRoutes^];
};

let getLoadedRoutes = (): list(module LoaderPage) =>
  switch (loadedRoutes^) {
  | [] => failwith("There are no registered Pages")
  | pages => pages
  };
