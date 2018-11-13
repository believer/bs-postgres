module Select = {
  type t = {rows: array(Js.Json.t)};

  let rowsGet = rows => rows;

  let make = json =>
    Json.Decode.{rows: json |> field("rows", array(rowsGet))};
};

type command =
  | CommandSelect
  | CommandUnknown;

type responseType = {command};

type t = [ | `Error(Js.String.t) | `Select(Select.t)];

let responseType = json =>
  Json.Decode.{
    command:
      switch (json |> field("command", string)) {
      | "SELECT" => CommandSelect
      | _ => CommandUnknown
      },
  };

let handleResponse = response =>
  switch (response->responseType.command) {
  | CommandSelect => `Select(Select.make(response))
  | _ => `Error("err")
  };

let handleError = err => Js.String.make(err);
