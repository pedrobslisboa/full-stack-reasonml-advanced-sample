type t('a) = {..} as 'a;

module Promise = {
  type t('a) = Lwt.t('a);
  type error = exn;

  let resolve = Lwt.return;
  let reject = Lwt.fail;

  let then_ = (p, fn) => Lwt.bind(fn, p);

  let catch = (handler: exn => t('a), promise: t('a)): t('a) =>
    Lwt.catch(() => promise, handler);
};

module String = {
  let includes = (substring, mainString) => {
    let stringRegex = Str.regexp_string(mainString);

    switch (Str.search_forward(stringRegex, substring, 0) |> ignore) {
    | exception Not_found => false
    | _ => true
    };
  };
};

type nullable('a) = option('a);
type null('a) = option('a);

module Nullable = {
  type t('a) = nullable('a);
  let null = None;

  external toOption: null('a) => option('a) = "%identity";
};
