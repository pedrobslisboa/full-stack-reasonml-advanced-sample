include Js;

type t('a) = {..} as 'a;

module Promise = {
  type t('a);
  type error = exn;

  external resolve: 'a => t('a) = "%identity";
  external reject: exn => t('a) = "%identity";
  [@mel.send.pipe: t('a)] external catch: (exn => t('a)) => t('a) = "catch";
  [@mel.send.pipe: t('a)] external then_: ('a => t('b)) => t('b) = "then";
};

module String = {
  [@mel.send.pipe: 'a] external includes: string => bool = "includes";
};
