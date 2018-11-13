module Select = {
  type t = {rows: array(Js.Json.t)};

  let rowsGet = rows => rows;

  let make = json =>
    Json.Decode.{rows: json |> field("rows", array(rowsGet))};
};

type t = [ | `Select(Select.t) | `Error];

let handleResponse = response =>
  switch (Js.Json.classify(response)) {
  | Js.Json.JSONObject(_) => `Select(Select.make(response))
  | _ => `Error
  };
