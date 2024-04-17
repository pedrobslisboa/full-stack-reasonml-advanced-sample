DynamicRouting.register(
  ~path=Pages_Pokemon.path,
  ~getInitialProps=Pages_Pokemon.getInitialProps,
  ~component=initialProps => <Pages_Pokemon initialProps />,
  DynamicRouting.loadedRoutes,
);

DynamicRouting.register(
  ~path=Pages_Portal.path,
  ~getInitialProps=None,
  ~component=_ => <Pages_Portal />,
  DynamicRouting.loadedRoutes,
);

let loadedPages = DynamicRouting.getLoadedRoutes(DynamicRouting.loadedRoutes);
