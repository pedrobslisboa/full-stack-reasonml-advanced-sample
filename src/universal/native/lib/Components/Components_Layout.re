[%styled.global
  {|
  * {
    box-sizing: border-box;
  }
  
  body {
    font-family: -apple-system,system-ui,BlinkMacSystemFont,"Segoe UI",Roboto,"Helvetica Neue",Arial,sans-serif;
    margin: 0;
    background: #f2f2f2;
  }

  pre, code {
      white-space: pre-line;
  }

  pre > code > span {
      white-space: pre;
  }
|}
];

[@react.component]
let make = (~children, ~className="") => {
  <div className={Utils.classNames(["layout", className])}>
    <Components_TopBar />
    <div className="content"> children </div>
  </div>;
};
