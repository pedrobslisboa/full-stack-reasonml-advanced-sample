module Styles = {
  let topBar = [%cx
    {|
    display: flex;
    justify-content: space-between;
    align-items: center;
    padding: 10px;
    background-color: #db4d3f;
    color: white;
  |}
  ];

  let menu = [%cx
    {|
    display: flex;
    gap: 20px;
    list-style: none;
    margin: 0;
  |}
  ];

  let button = [%cx
    {|
      opacity: 0.6;
      border: none;
      color: white;
      cursor: pointer;
      font-size: 1em;
      background-color: transparent;
    |}
  ];

  let active = [%cx {|
    opacity: 1;
  |}];

  let logo = [%cx
    {|
      position: relative;
      align-items: center;
      color: #fff;
      display: flex;
      border: 2px solid white;
      border-radius: 2px;
      overflow: hidden;
      min-width: 38px;
      min-height: 38px;
      margin-left: 20px;
      box-sizing: border-box;

      :after {
        font-weight: 700;
        font-size: 20px;
        content: "REI";
        color: white;
        position: absolute;
        width: 26px;
        line-height: 1;
        left: 9px;
        bottom: 0;
        overflow: hidden;
        transition: all 0.5s cubic-bezier(0.18, 0.89, 0.31, 1.16);
      }

      &:hover:after {
          width: 34px;
          left: 5px;
      }
  |}
  ];
};

let rec joinUrlPaths = paths =>
  switch (paths) {
  | [] => "/"
  | [hd] => "/" ++ hd
  | [hd, ...tail] => hd ++ "/" ++ joinUrlPaths(tail)
  };

[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();
  let (active, setActive) = React.useState(_ => "");

  React.useEffect1(
    () => {
      setActive(_ => url.path |> joinUrlPaths);

      None;
    },
    [|url|],
  );

  <div className=Styles.topBar>
    <span className=Styles.logo />
    {"SSR SPA React Reason Native" |> React.string}
    <ul className=Styles.menu>
      <button
        className={Utils.classNames([
          Styles.button,
          active == "/" ? Styles.active : "",
        ])}
        onClick={_ => {ReasonReactRouter.push("/")}}>
        {"Home" |> React.string}
      </button>
      <button
        className={Utils.classNames([
          Styles.button,
          active == "/pokemon" ? Styles.active : "",
        ])}
        onClick={_ => {ReasonReactRouter.push("/pokemon?name=ditto")}}>
        {"Pokemon Page (Fetch from Pokemon API with getInitialProps)"
         |> React.string}
      </button>
    </ul>
  </div>;
};
