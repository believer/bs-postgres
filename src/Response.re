module Select = {
  [@bs.deriving abstract]
  type t = {rows: array(Js.Json.t)};

  let make = rows => t(~rows);
};

type t = [ | `Select(Select.t) | `Error];

let handleResponse = response => {
  Js.log2("classification", Js.Json.classify(response));

  switch (Js.Json.classify(response)) {
  | Js.Json.JSONArray(rows) => `Select(Select.make(rows))
  | _ => `Error
  };
};