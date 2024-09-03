module Styles = {
  let loader = [%cx
    {|
  display: flex;
  flex-direction: column;
  height: 100%;
  width: 100%;
|}
  ];

  let loadingAnimation = [%keyframe
    {|
     0% {
      left:0%;
      right:100%;
      width:0%;
    }
    10% {
      left:0%;
      right:75%;
      width:25%;
    }
    90% {
      right:0%;
      left:75%;
      width:25%;
    }
    100% {
      left:100%;
      right:0%;
      width:0%;
    }
|}
  ];

  let loaderBar = [%cx
    {|
  position: absolute;
  border-radius: 10px;
  height: 2px;
  top: 0;
  right: 100%;
  bottom: 0;
  left: 0;
  background: #fff;
  width: 0;
  animation: 500ms linear infinite;
  animation-name: $(loadingAnimation);
|}
  ];
};

[@react.component]
let make = () => {
  <UniversalPortal_Shared.Portal selector="body">
    <div className=Styles.loader> <div className=Styles.loaderBar /> </div>
  </UniversalPortal_Shared.Portal>;
};
