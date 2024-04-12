open Lwt;
open Cohttp_lwt_unix;

// let getCountries = _ => {
//   let uri =
//     Uri.of_string(
//       "https://gist.githubusercontent.com/pedrobslisboa/1a6af944bc5f70067018df6f0ab30263/raw/f987794a5be8bb40bb92595f615024a59123a6dc/country-list-population.json",
//     );
//   Client.get(uri)
//   >>= (
//     ((_, body)) => {
//       body
//       |> Cohttp_lwt.Body.to_string
//       >|= (
//         body => {
//           let json = Yojson.Basic.from_string(body);

//           Some(resultJson(json));
//         }
//       );
//     }
//   );
// };

let fetch = url => {
  let uri = Uri.of_string(url);

  Client.get(uri)
  >>= (
    ((_, body)) => {
      body
      |> Cohttp_lwt.Body.to_string
      >|= (
        body => {
          let json = Bindings_Json.from_string(body);

          json;
        }
      );
    }
  );
};

// module Response = {
//   [@mel.send]
//   external json: Bindings_Json.t => Bindings_Js.Promise.t(Bindings_Json.t) =
//     "json";
// };

module Response = {
  let json = json => {
    Js.Promise.resolve(json);
  };
};
