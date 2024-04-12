module Styles = {
  let topBar = [%cx
    {|
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 10px;
  background-color: #0c466d;
  color: white;
|}
  ];

  let menu = [%cx {|
  display: flex;
  gap: 20px;
  list-style: none;
|}];

  let button = [%cx
    {|
  padding: 10px 20px;
  border: 2px solid white;
  border-radius: 5px;
  color: white;
  cursor: pointer;
  background-color: transparent;
|}
  ];
};

[@react.component]
let make = () => {
  <div className=Styles.topBar>
    {"SSR SPA React Reason Native" |> React.string}
    <ul className=Styles.menu>
      <button
        className=Styles.button onClick={_ => {ReasonReactRouter.push("/")}}>
        {"Home" |> React.string}
      </button>
      <button
        className=Styles.button
        onClick={_ => {ReasonReactRouter.push("/pokemon?name=ditto")}}>
        {"Pokemon Page (Fetch from Pokemon API with getInitialProps)"
         |> React.string}
      </button>
    </ul>
  </div>;
};
