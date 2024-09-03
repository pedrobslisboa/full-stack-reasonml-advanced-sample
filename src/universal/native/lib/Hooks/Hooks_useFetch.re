type return = {
  data: option(Bindings.Json.t),
  loading: bool,
  error: option(string),
};

let make = url => {
  let (data, setData) = React.useState(_ => None);
  let (loading, setLoading) = React.useState(_ => true);
  let (error, setError) = React.useState(_ => None);

  switch%platform () {
  | Server => 
    let _ = setData;
    let _ = setLoading;
    let _ = setError;
  | Client => ()
  };

  React.useEffect1(
    () => {
      let fetch = () =>
        Bindings.Js.Promise.(
          Bindings.Fetch.fetch(url)
          |> then_(response =>
               try(response |> Bindings.Fetch.Response.json) {
               | _ =>
                 print_endline("Error parsing JSON");
                 raise(Not_found);
               }
             )
          |> then_(data => {
               setData(_ => Some(data));
               setLoading(_ => false);

               () |> resolve;
             })
          |> catch(_ => {
               setError(_ => Some("Error"));
               setLoading(_ => false);

               () |> resolve;
             })
          |> ignore
        );

      fetch() |> ignore;

      None;
    },
    [|url|],
  );

  {data, loading, error};
};
