module Styles = {
  let wrapper = [%cx
    {|
    position: static;
    top:0;
    width: 100%;
    background-color: #db4d3f;


    @media (min-width: 1024px) {
      position: sticky;
    }
  |}
  ];

  let topBar = [%cx
    {|
    margin: 0 auto;
    display: flex;
    max-width: 1400px;
    width: 100%;
    justify-content: space-between;
    align-items: center;
    padding: 6px 20px;
    color: white;
  |}
  ];

  let menu = [%cx
    {|
    gap: 20px;
    list-style: none;
    margin: 0;
    padding: 0;
    display: none;

     @media (min-width: 1024px) {
      display: flex;
    }
  |}
  ];

  let mobileMenu = [%cx
    {|
    background-color: #c23426;
    gap: 10px;
    list-style: none;
    margin: 0;
    padding: 6px 20px;

     @media (min-width: 1024px) {
      display: none;
    }
  |}
  ];

  let button = [%cx
    {|
      opacity: 0.6;

      &:hover {
        opacity: 1;
      }
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
      margin-right: 20px;
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
          left: 2px;
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

module MobileMenu = {
  [@react.component]
  let make = (~activeItem) => {
    <ul className=Styles.mobileMenu>
      <Components_Button
        variant=`text
        invert=true
        className={Utils.classNames([
          Styles.button,
          activeItem == "/" ? Styles.active : "",
        ])}
        onClick={_ => {ReasonReactRouter.push("/")}}>
        {"Home" |> React.string}
      </Components_Button>
      <Components_Button
        variant=`text
        invert=true
        className={Utils.classNames([
          Styles.button,
          activeItem == "/portal" ? Styles.active : "",
        ])}
        onClick={_ => {ReasonReactRouter.push("/portal")}}>
        {"Univeral Portal" |> React.string}
      </Components_Button>
      <Components_Button
        variant=`text
        invert=true
        className={Utils.classNames([
          Styles.button,
          activeItem == "/pokemon" ? Styles.active : "",
        ])}
        onClick={_ => {ReasonReactRouter.push("/pokemon?name=ditto")}}>
        {"Pokemon" |> React.string}
      </Components_Button>
      <Components_Button
        variant=`text
        invert=true
        className={Utils.classNames([Styles.button])}
        target="__blank"
        href="https://github.com/pedrobslisboa/full-stack-reasonml-advanced-sample">
        {"Github" |> React.string}
      </Components_Button>
      <Components_Button
        variant=`text
        invert=true
        className={Utils.classNames([Styles.button])}
        target="__blank"
        href="https://sancho.dev/blog/server-side-rendering-react-in-ocaml">
        {"@davesnx Article" |> React.string}
      </Components_Button>
    </ul>;
  };
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

  <div className=Styles.wrapper>
    <div className=Styles.topBar>
      <span className=Styles.logo />
      <ul className=Styles.menu>
        <Components_Button
          variant=`text
          invert=true
          className={Utils.classNames([
            Styles.button,
            active == "/" ? Styles.active : "",
          ])}
          onClick={_ => {ReasonReactRouter.push("/")}}>
          {"Home" |> React.string}
        </Components_Button>
        <Components_Button
          variant=`text
          invert=true
          className={Utils.classNames([
            Styles.button,
            active == "/portal" ? Styles.active : "",
          ])}
          onClick={_ => {ReasonReactRouter.push("/portal")}}>
          {"Univeral Portal" |> React.string}
        </Components_Button>
        <Components_Button
          variant=`text
          invert=true
          className={Utils.classNames([
            Styles.button,
            active == "/pokemon" ? Styles.active : "",
          ])}
          onClick={_ => {ReasonReactRouter.push("/pokemon?name=ditto")}}>
          {"Pokemon Page (with getInitialProps)" |> React.string}
        </Components_Button>
        <Components_Button
          variant=`text
          invert=true
          className={Utils.classNames([Styles.button])}
          target="__blank"
          href="https://github.com/pedrobslisboa/full-stack-reasonml-advanced-sample">
          {"Github" |> React.string}
        </Components_Button>
        <Components_Button
          variant=`text
          invert=true
          className={Utils.classNames([Styles.button])}
          target="__blank"
          href="https://sancho.dev/blog/server-side-rendering-react-in-ocaml">
          {"David Sancho Article" |> React.string}
        </Components_Button>
      </ul>
    </div>
    <MobileMenu activeItem=active />
  </div>;
};
