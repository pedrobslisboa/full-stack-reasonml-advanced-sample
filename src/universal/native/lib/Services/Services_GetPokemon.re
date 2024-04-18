open Bindings.Json.Utils;

type dreamWorld = {front_default: string};
type other = {dream_world: dreamWorld};
type sprites = {other};
type ability = {name: string};
type abilityRecord = {ability};

type pokemon = {
  name: string,
  sprites,
  abilities: list(abilityRecord),
};

let defaultPokemon = {
  name: "pikachu",
  sprites: {
    other: {
      dream_world: {
        front_default: "",
      },
    },
  },
  abilities: [{
                ability: {
                  name: "static",
                },
              }],
};

let extractSprites = (json): sprites => {
  let front_default_url =
    json
    |> member("sprites")
    |> member("other")
    |> member("dream_world")
    |> member("front_default")
    |> to_string;

  {
    other: {
      dream_world: {
        front_default: front_default_url,
      },
    },
  };
};

let extractAbilities = (json): list(abilityRecord) => {
  json
  |> member("abilities")
  |> to_list
  |> List.map(abil => {
       let value: abilityRecord = {
         ability: {
           name: abil |> member("ability") |> member("name") |> to_string,
         },
       };

       value;
     });
};

let decodeJson = (json): pokemon => {
  let name = json |> member("name") |> to_string;
  let sprites = json |> extractSprites;
  let abilities = json |> extractAbilities;

  {name, sprites, abilities};
};

let make = name => {
  let url = "https://pokeapi.co/api/v2/pokemon/" ++ name;
  Bindings.Js.Promise.(
    Bindings.Fetch.fetch(url)
    |> then_(response =>
         try(response |> Bindings.Fetch.Response.json) {
         | _ =>
           print_endline("Error parsing JSON");
           raise(Not_found);
         }
       )
    |> then_(data => {data |> resolve})
  );
};
