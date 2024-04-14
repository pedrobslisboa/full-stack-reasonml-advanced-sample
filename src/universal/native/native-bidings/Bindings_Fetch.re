open Lwt;
open Cohttp_lwt_unix;

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

module Response = {
  let json = json => {
    Js.Promise.resolve(json);
  };
};
