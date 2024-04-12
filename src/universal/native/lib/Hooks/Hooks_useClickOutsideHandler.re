let make =
    (
      ~reference:
         React.ref(Bindings.Js.Nullable.t(Bindings.WebApi.Element.t('a))),
      ~handler,
      ~ignoreElements:
         option(
           array(
             React.ref(
               Bindings.Js.Nullable.t(Bindings.WebApi.Element.t('b)),
             ),
           ),
         )=None,
      (),
    ) =>
  React.useEffect3(
    () => {
      let listener = e => {
        switch (reference.current |> Bindings.Js.Nullable.toOption) {
        | None => ()
        | Some(refValue) =>
          {
            let refContainsIgnoreElement =
              switch (ignoreElements) {
              | None => false
              | Some(ignoreElementsArray) =>
                Array.exists(
                  (
                    el:
                      React.ref(
                        Bindings.Js.Nullable.t(
                          Bindings.WebApi.Element.t('b),
                        ),
                      ),
                  ) => {
                    switch (el.current |> Bindings.Js.Nullable.toOption) {
                    | None => false
                    | Some(ignoreElement) =>
                      Bindings.WebApi.Node.contains(
                        ignoreElement,
                        Bindings.Event.Form.target(e),
                      )
                    }
                  },
                  ignoreElementsArray,
                )
              };

            let containsRef =
              Bindings.WebApi.Node.contains(
                refValue,
                Bindings.Event.Form.target(e),
              );
            if (!containsRef && !refContainsIgnoreElement) {
              handler(e);
            };
          };
          ();
        };
      };

      Bindings.WebApi.Document.addEventListener("click", listener);

      Some(
        () => {
          Bindings.WebApi.Document.removeEventListener("click", listener)
        },
      );
    },
    (reference, handler, ignoreElements),
  );
