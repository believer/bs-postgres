type pgClient;

[@bs.deriving abstract]
type config = {
  [@bs.optional]
  host: string,
  [@bs.optional]
  port: int,
  [@bs.optional]
  user: string,
  [@bs.optional]
  password: string,
  [@bs.optional]
  database: string,
};

[@bs.new] [@bs.module "pg"]
external createClient: config => pgClient = "Client";

[@bs.send] external connect: pgClient => Js.Promise.t(unit) = "";
[@bs.send] external close: pgClient => Js.Promise.t(unit) = "end";
[@bs.send]
external createQuery:
  (pgClient, string, array(string)) => Js.Promise.t(Js.Json.t) =
  "query";

let client = (~host=?, ~port=?, ~user=?, ~password=?, ~database=?, _) =>
  config(~host?, ~port?, ~user?, ~password?, ~database?, ())->createClient;

let query = (client, sql) =>
  Js.Promise.(
    client->createQuery(sql, [||])
    |> then_(res => Response.handleResponse(res) |> resolve)
    |> catch(err => `Error(Response.handleError(err)) |> resolve)
  );
