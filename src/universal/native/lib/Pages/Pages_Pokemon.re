open Bindings.Json.Utils;

type dreamWorld = {front_default: string};
type other = {dream_world: dreamWorld};
type sprites = {other};
type ability = {name: string};
type abilityRecord = {ability};

type props = {
  name: string,
  sprites,
  abilities: list(abilityRecord),
};

let route = "/pokemon";

let defaultProps = {
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

let name = json => json |> member("name") |> to_string;
let sprites = json => {
  `Assoc([
    (
      "other",
      `Assoc([
        (
          "dream_world",
          `Assoc([
            (
              "front_default",
              `String(
                json
                |> member("sprites")
                |> member("other")
                |> member("dream_world")
                |> member("front_default")
                |> to_string,
              ),
            ),
          ]),
        ),
      ]),
    ),
  ]);
};

let abilities = json => {
  `List(
    {
      json
      |> member("abilities")
      |> to_list
      |> List.map(abil => {
           `Assoc([
             (
               "ability",
               `Assoc([
                 (
                   "name",
                   `String(
                     abil |> member("ability") |> member("name") |> to_string,
                   ),
                 ),
               ]),
             ),
           ])
         });
    },
  );
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

let resultJsonToRecord = (json): props => {
  let name = json |> member("name") |> to_string;
  let sprites = json |> extractSprites;
  let abilities = json |> extractAbilities;

  {name, sprites, abilities};
};

let isomorphicFunction = (~server, ~client) => {
  switch%platform (Runtime.platform) {
  | Client =>
    server |> ignore;
    client();
  | Server =>
    client |> ignore;
    server();
  };
};

let getInitialProps =
  Some(
    query => {
      let name =
        switch (query("name")) {
        | Some(name) => name
        | None => "bulbasaur"
        };

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
    },
  );

module Styles = {
  let pokemon = [%cx
    {|
  color: #393939;
  height: 100%;
  width: 100%;
  display: flex;
  align-items: center;
  justify-content: center;
|}
  ];

  let pokemonCard = [%cx
    {|
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  padding: 20px;
  border-radius: 20px;
  box-shadow: 0 0 10px 0 rgba(0, 0, 0, 0.3);
  margin: 20px;
  background-color: white;
  width: 200px;
|}
  ];

  let pokemonImage = [%cx {|
   width: 100px;
  height: 100px;
  |}];

  let abilitiesClass = [%cx
    {|
  padding: 0;
  display: flex;
  flex-wrap: wrap;
  gap: 5px;
  |}
  ];

  let ability = [%cx
    {|
  padding: 5px 10px;
  list-style: none;
  border-radius: 5px;
  background-color: #3498db;
  color: white;
  |}
  ];
};

[@react.component]
let make = (~initialProps=Bindings.Json.from_string("{}")) => {
  let props = initialProps |> resultJsonToRecord;

  <Components.Layout>
    <Components.Head>
      <title> {"Pokemon: " ++ props.name ++ "" |> React.string} </title>
    </Components.Head>
    <div className=Styles.pokemon>
      <div className=Styles.pokemonCard>
        <h1> {props.name |> React.string} </h1>
        <img
          className=Styles.pokemonImage
          src={props.sprites.other.dream_world.front_default}
          alt={props.name}
        />
        <ul className=Styles.abilitiesClass>
          {props.abilities
           |> List.map(ab => {
                <li className=Styles.ability key={ab.ability.name}>
                  {ab.ability.name |> React.string}
                </li>
              })
           |> Array.of_list
           |> React.array}
        </ul>
      </div>
    </div>
  </Components.Layout>;
};
