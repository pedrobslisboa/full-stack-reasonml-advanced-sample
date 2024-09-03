[@react.component]
let make = (~children) =>
  <UniversalPortal_Shared.Portal selector="head">
    children
  </UniversalPortal_Shared.Portal>;
