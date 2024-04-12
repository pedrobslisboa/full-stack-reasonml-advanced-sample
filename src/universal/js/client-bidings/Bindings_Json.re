type t;

external typeof: 'a => string = "#typeof";
external parseExp: string => option(t) = "JSON.parse";
external stringify: t => string = "JSON.stringify";
external isArray: 'a => bool = "Array.isArray";
exception String_Exception(string);

let from_string = string => {
  switch (parseExp(string)) {
  | Some(json) => json
  | None => raise(String_Exception("Invalid JSON"))
  };
};

let to_string = json => stringify(json);

module Decode = {
  let field = (fieldName, decodeFn, json) => {
    switch (typeof(json)) {
    | "object" =>
      let field = [%mel.raw {|json[fieldName]|}];

      switch (field) {
      | _ => decodeFn(field)
      };
    | _ => raise(String_Exception("Expected field " ++ fieldName))
    };
  };

  let string = json => {
    switch (typeof(json)) {
    | "string" => json
    | _ => raise(String_Exception("Expected string"))
    };
  };

  let int = json => {
    switch (typeof(json)) {
    | "number" => json
    | _ => raise(String_Exception("Expected int"))
    };
  };

  let list = (decodeFn, json) => {
    decodeFn |> ignore;
    switch (json |> isArray) {
    | true =>
      let arr = [%mel.raw {|json|}];
      let len = Array.length(arr);
      let rec loop = (i, acc) =>
        if (i == len) {
          acc;
        } else {
          loop(i + 1, acc @ [decodeFn(arr[i])]);
        };

      loop(0, []);
    | _ => raise(String_Exception("Expected list"))
    };
  };
};

module Utils = {
  let to_string = json => {
    switch (typeof(json)) {
    | "string" => json
    | _ => raise(String_Exception("Expected string"))
    };
  };

  let to_int = json => {
    switch (typeof(json)) {
    | "number" => json
    | _ => raise(String_Exception("Expected int"))
    };
  };

  let to_list = json => Decode.list(x => x, json);

  let member = (fieldName, json) => {
    switch (typeof(json)) {
    | "object" =>
      let field = [%mel.raw {|json[fieldName]|}];

      switch (field) {
      | _ => field
      };
    | _ => raise(String_Exception("Expected field " ++ fieldName))
    };
  };
};
