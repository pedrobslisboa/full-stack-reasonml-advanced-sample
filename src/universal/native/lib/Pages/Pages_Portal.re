module Styles = {
  let modal = [%cx
    {|
    position: absolute;
    top: 0;
    left: 0;
    width: 100%;
    background-color: rgba(0, 0, 0, 0.3);
    height: 100%;
    display: flex;
    justify-content: center;
    align-items: center;
    color: #393939;
  |}
  ];

  let modalContent = [%cx
    {|
    display: flex;
    flex-direction: column;
    background-color: #fff;
    padding: 20px;
    border-radius: 20px;
    box-shadow: 0 0 10px 0 rgba(0, 0, 0, 0.3);
  |}
  ];

  let button = [%cx
    {|
    background-color: #db4d3f;
    color: #fff;
    padding: 10px;
    border: none;
    border-radius: 3px;
    margin-top: 10px;
    cursor: pointer;
  |}
  ];
};

let path = "/";

[@react.component]
let make = () => {
  let (modalOpen, setModalOpen) = React.useState(_ => true);
  let buttonRef = React.useRef(Bindings.Js.Nullable.null);
  let modalRef = React.useRef(Bindings.Js.Nullable.null);

  Hooks_useClickOutsideHandler.make(
    ~reference=modalRef,
    ~ignoreElements=Some([|buttonRef|]),
    ~handler=
      _ =>
        if (modalOpen) {
          setModalOpen(_ => false);
        },
    (),
  );

  <Components.Layout>
    <Components.Head>
      <title> {"Home " |> React.string} </title>
    </Components.Head>
    <button
      className=Styles.button
      ref={ReactDOM.Ref.domRef(buttonRef)}
      onClick={_ => setModalOpen(_ => true)}>
      {"Open modal" |> React.string}
    </button>
    {modalOpen
       ? <UniversalPortal_Shared.Components.Portal selector="body">
           <div className=Styles.modal>
             <div
               ref={ReactDOM.Ref.domRef(modalRef)}
               className=Styles.modalContent>
               {"Hey, I'm a universal portal, disable JS on your dev tools and check that I'll still here"
                |> React.string}
               <button
                 className=Styles.button
                 onClick={_ => setModalOpen(_ => false)}>
                 {"Close" |> React.string}
               </button>
             </div>
           </div>
         </UniversalPortal_Shared.Components.Portal>
       : React.null}
  </Components.Layout>;
};
