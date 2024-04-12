[@react.component]
let make = (~children) =>
  <UniversalPortal_Shared.Components.Portal selector="head">
    children
  </UniversalPortal_Shared.Components.Portal>;
