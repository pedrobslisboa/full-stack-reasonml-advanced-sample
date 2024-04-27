module Styles = {
  let wrapper = [%cx
    {|
    padding: 10px;
    margin: 0 auto;
    gap: 20px;
    max-width: 1400px;
    display: flex;
    flex-direction: column;
    align-items: center;

    @media (min-width: 1024px) {
      padding: 40px;
    }
  |}
  ];

  let reasonml = [%cx
    {|
    width: 300px;

    @media (min-width: 1024px) {
      width: 600px;
    }
  |}
  ];

  let descriptionWrapper = [%cx
    {|
    gap: 20px;
    margin-top: 10px;
    display: flex;
    font-size: 12px;
    flex-direction: column;
    font-weight: 300;
    color: #444;
    align-items: center;

    @media (min-width: 1024px) {
      font-size: 14px;
      flex-direction: row;
      gap: 60px;
      margin-top: 30px;
    }
  |}
  ];

  let description = [%cx
    {|
    text-align: center;
    font-size: 24px;
    line-height: 1.2em;
    text-align:center;
    max-width: 400px;
  |}
  ];

  let buttonGroup = [%cx
    {|
      display: flex;
      gap: 20px;
      font-size: 14px;
      flex-direction: column;
      align-items: center;



      @media (min-width: 1024px) {
        flex-direction: row;
      }
  |}
  ];
};

let path = "/";

[@react.component]
let make = () => {
  <Components.Layout>
    <Components.Head>
      <title> {"Home " |> React.string} </title>
    </Components.Head>
    <div className=Styles.wrapper>
      <img className=Styles.reasonml src="/public/reasonml.svg" />
      <div className=Styles.descriptionWrapper>
        <Components_Highlight />
        <span className=Styles.description>
          {"An application rendering ReasonReact natively. Much faster, much safer, much cooler!"
           |> React.string}
        </span>
      </div>
      <div className=Styles.buttonGroup>
        <Components_Button
          prefix={<img height="24" src="/public/github.svg" />}
          target="__blank"
          href="https://github.com/pedrobslisboa/full-stack-reasonml-advanced-sample">
          {"Github" |> React.string}
        </Components_Button>
        <Components_Button
          variant=`outline
          target="__blank"
          href="https://sancho.dev/blog/server-side-rendering-react-in-ocaml">
          {"Reason SSR Article by @davesnx" |> React.string}
        </Components_Button>
      </div>
    </div>
  </Components.Layout>;
};
