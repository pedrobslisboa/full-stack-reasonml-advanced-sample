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

let initialPropsDefault =
  Bindings.Json.from_string(
    {|
      {
        "name": "bulbasaur",
        "sprites": {
          "other": {
            "dream_world": {
              "front_default": "https://raw.githubusercontent.com/PokeAPI/sprites/master/sprites/pokemon/other/dream-world/1.svg"
            }
          }
        },
        "abilities": [
          {
            "ability": {
              "name": "overgrow"
            }
          },
          {
            "ability": {
              "name": "chlorophyll"
            }
          }
        ]
      }
    |},
  );

let path = "/pokemon";

// Runs only on the server
// but we keep it close to the component
// to a better overview of the page
let getInitialProps =
  Some(
    req => {
      let name =
        switch (Bindings_Dream.query(req, "name")) {
        | Some(name) => name
        | None => "bulbasaur"
        };

      Services.GetPokemon.make(name);
    },
  );

type props = Services.GetPokemon.pokemon;

[@react.component]
let make = (~initialProps=initialPropsDefault) => {
  let props: props = initialProps |> Services.GetPokemon.decodeJson;

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
           |> List.map((ab: Services.GetPokemon.abilityRecord) => {
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
