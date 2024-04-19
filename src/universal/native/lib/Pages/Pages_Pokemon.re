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

let initialPropsDefault: Services.GetPokemon.pokemon = {
  name: "bulbasaur",
  sprites: {
    other: {
      dream_world: {
        front_default: "https://raw.githubusercontent.com/PokeAPI/sprites/master/sprites/pokemon/other/dream-world/1.svg",
      },
    },
  },
  abilities: [
    {
      ability: {
        name: "overgrow",
      },
    },
    {
      ability: {
        name: "chlorophyll",
      },
    },
  ],
};

let path = "/pokemon";

type props = Services.GetPokemon.pokemon;

// Runs only on the server
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

let decodeProps = (json) => switch (json) {
  | Some(j) => Services.GetPokemon.decodeJson(j)
  | None => initialPropsDefault
};

let make = (initialProps: props) => {
  <Components.Layout>
    <Components.Head>
      <title> {"Pokemon: " ++ initialProps.name ++ "" |> React.string} </title>
    </Components.Head>
    <div className=Styles.pokemon>
      <div className=Styles.pokemonCard>
        <h1> {initialProps.name |> React.string} </h1>
        <img
          className=Styles.pokemonImage
          src={initialProps.sprites.other.dream_world.front_default}
          alt={initialProps.name}
        />
        <ul className=Styles.abilitiesClass>
          {initialProps.abilities
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
