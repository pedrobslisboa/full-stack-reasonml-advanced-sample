let rec classNames = classes => {
  switch (classes) {
  | [] => ""
  | [x] => x
  | [x, ...rest] => x ++ " " ++ classNames(rest)
  };
};

module List = {
  let slice = (i, k, list: list('a)) => {
    let rec drop = (n, list) =>
      switch (list) {
      | [] => []
      | [_, ...xs] as z => n == 0 ? z : drop(n - 1, xs)
      };

    let rec take = (n, list) =>
      switch (list) {
      | [] => []
      | [x, ...xs] => n == 0 ? [] : [x, ...take(n - 1, xs)]
      };

    take(k - i + 1, drop(i, list));
  };
};
