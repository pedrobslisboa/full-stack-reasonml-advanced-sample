module type Loader_page = {
  let getInitialProps:
    option(Bindings_Dream.request => Bindings.Js.Promise.t(Bindings.Json.t));
  let path: string;
  let make: Bindings_Json.t => React.element;
};

let loadedRoutes: ref(list(module Loader_page)) = ref([]);

let register =
    (
      ~path,
      ~getInitialProps,
      ~component: Bindings_Json.t => React.element,
      loadedRoutes,
    ) => {
  module R = {
    let path = path;
    let getInitialProps = getInitialProps;
    let make = component;
  };

  loadedRoutes := [((module R): (module Loader_page)), ...loadedRoutes^];
};

let getLoadedRoutes = (loadedRoutes): list(module Loader_page) =>
  switch (loadedRoutes^) {
  | [] => failwith("There are no registered Pages")
  | pages => pages
  };
