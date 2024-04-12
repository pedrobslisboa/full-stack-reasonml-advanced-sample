module Form = {
  type t = React.Event.Form.t;
  type target = {value: string};

  [@mel.get] external target: t => Bindings_WebApi.Element.t('a) = "target";
};

module Keyboard = {
  type t = React.Event.Keyboard.t;

  [@mel.get] external key: t => string = "key";
};

module UI = {
  type t = React.Event.UI.t;

  [@mel.get] external target: t => Bindings_WebApi.Element.t('a) = "target";
};

module Mouse = {
  type t = React.Event.Mouse.t;
};
