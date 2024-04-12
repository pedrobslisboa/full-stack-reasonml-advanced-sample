// Client only, not isomorphic
external fetch: string => Bindings_Js.Promise.t(Bindings_Json.t) = "fetch";

module Response = {
  [@mel.send]
  external json: Bindings_Json.t => Bindings_Js.Promise.t(Bindings_Json.t) =
    "json";
};
