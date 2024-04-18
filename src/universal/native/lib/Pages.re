open DynamicRouting;

loadedRoutes
|> register(
     ~path=Pages_Pokemon.path,
     ~getInitialProps=Pages_Pokemon.getInitialProps,
     ~component=initialProps =>
     <Pages_Pokemon ?initialProps />
   );

loadedRoutes
|> register(~path=Pages_Portal.path, ~getInitialProps=None, ~component=_ =>
     <Pages_Portal />
   );

let loadedPages = getLoadedRoutes();
