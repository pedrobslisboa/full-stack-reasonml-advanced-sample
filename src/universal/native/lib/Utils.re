let getUnit = value =>
  switch (value) {
  | x when x >= 1000000. => `Millions
  | x when x >= 1000. => `Thousands
  | _ => `Hundreds
  };

let formatPopulation = population => {
  switch (getUnit(population)) {
  | `Millions => population /. 1000000. |> Printf.sprintf("%.1fkk")
  | `Thousands => population /. 1000. |> Printf.sprintf("%.1fk")

  | `Hundreds => population |> Printf.sprintf("%.0f")
  };
};

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
