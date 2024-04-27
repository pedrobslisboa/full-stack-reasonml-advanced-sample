module Styles = {
  let wrapper = [%cx
    {|
    display: flex;
    align-items: center;
    text-decoration: none;
    padding: 10px;
    border: none;
    border-radius: 3px;
    cursor: pointer;
    font-weight: 300;
    font-size: 1em;
  |}
  ];

  let prefix = [%cx {|
    margin-right: 10px;
  |}];

  let outline = invert => {
    let primary = invert ? `transparent : `hex("db4d3f");
    let secondary = !invert ? `transparent : `hex("db4d3f");

    [%cx {|
        border: 1px solid $(primary);
        background-color: $(secondary);
        color: #db4d3f;
    |}];
  };

  let filled = invert => {
    let primary = invert ? `hex("fff") : `hex("db4d3f");
    let secondary = !invert ? `hex("fff") : `hex("db4d3f");

    [%cx
     {|
        background-color: $(primary);
        color: $(secondary);
    |}];
  };

  let text = invert => {
    let color = invert ? `hex("fff") : `hex("db4d3f");

    [%cx {|
    background-color: transparent;
    color: $(color);
  |}];
  };
};

[@react.component]
let make =
    (
      ~onClick=?,
      ~className=?,
      ~children=React.null,
      ~variant=`filled,
      ~invert=false,
      ~href=?,
      ~target=?,
      ~prefix=?,
    ) => {
  let vatiantClassName =
    switch (variant) {
    | `outline => Styles.outline(invert)
    | `filled => Styles.filled(invert)
    | `text => Styles.text(invert)
    };

  switch (href) {
  | Some(href) =>
    <a
      ?onClick
      ?target
      href
      className={Utils.classNames([
        Option.value(className, ~default=""),
        Styles.wrapper,
        vatiantClassName,
      ])}>
      {switch (prefix) {
       | Some(p) => <span className=Styles.prefix> p </span>
       | None => React.null
       }}
      children
    </a>
  | None =>
    <button
      ?onClick
      className={Utils.classNames([
        Option.value(className, ~default=""),
        Styles.wrapper,
        vatiantClassName,
      ])}>
      {switch (prefix) {
       | Some(p) => <span className=Styles.prefix> p </span>
       | None => React.null
       }}
      children
    </button>
  };
};
