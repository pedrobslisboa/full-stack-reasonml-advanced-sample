open Yojson.Basic.Util;

type t = Yojson.Basic.t;

/**

let label = json => json |> member("label") |> to_string;
let value = json => json |> member("value") |> to_string;
let population = json => json |> member("population") |> to_int;

let countries = json => {
  `List(
    {
      json
      |> to_list
      |> List.map(country => {
           let value = country |> member("value") |> to_string;
           let label = country |> member("label") |> to_string;

           `Assoc([
             ("value", `String(value)),
             ("label", `String(label)),
             ("population", `Int(population(country))),
           ]);
         });
    },
  );
};
 */

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
