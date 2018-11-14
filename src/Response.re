module Select = {
  type t = {rows: array(Js.Json.t)};

  let rowsGet = rows => rows;

  let make = json =>
    Json.Decode.{rows: json |> field("rows", array(rowsGet))};
};

module Insert = {
  type t = {rowCount: int};

  let make = json => Json.Decode.{rowCount: json |> field("rowCount", int)};
};

type t =
  | Error(Js.String.t)
  | Select(Select.t)
  | Insert(Insert.t);

let handleResponse = response =>
  Json.Decode.(
    switch (response |> field("command", string)) {
    | "SELECT" => Select(Select.make(response))
    | "INSERT" => Insert(Insert.make(response))
    | _ => Error("err")
    }
  );

let handleError = err => Js.String.make(err);
