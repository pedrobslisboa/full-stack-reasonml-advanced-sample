[@react.component]
let make = (~children, ~className="") => {
  <div className={Utils.classNames(["layout", className])}>
    <Components_TopBar />
    <div className="content"> children </div>
  </div>;
};
