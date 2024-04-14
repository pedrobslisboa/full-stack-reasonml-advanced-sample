open Yojson.Basic.Util;

type t = Yojson.Basic.t;

type jsonTypes = [
  | `String(string)
  | `Int(int)
  | `List(list(t))
  | `Assoc(list((string, t)))
];

let from_string = Yojson.Basic.from_string;
let to_string = Yojson.Basic.to_string;

module Decode = {
  let field = (fieldName, decoder, json) => {
    json |> member(fieldName) |> decoder;
  };

  let string = value => {
    value |> to_string;
  };

  let int = value => {
    value |> to_int;
  };

  let list = (decodeFn, value) => {
    value |> to_list |> List.map(decodeFn);
  };
};

module Utils = {
  let to_string = Yojson.Basic.Util.to_string;
  let to_int = Yojson.Basic.Util.to_int;
  let to_list = (json: t): list('a) => Yojson.Basic.Util.to_list(json);

  let member = Yojson.Basic.Util.member;
};
