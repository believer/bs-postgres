open Pg;
open Js.Promise;

let client = Pg.client(~host="localhost", ~port=5432, ());

client->Pg.connect |> ignore;

type user = {city: option(string)};

let mapRows = item =>
  Json.Decode.{city: item |> optional(field("city", string))};

Pg.query(~client, ~query="select * from users limit 10", ())
|> then_(res => {
     switch (res) {
     | Select(select) =>
       Js.log2("select", select.rows);

       /* Log it */
       let rows = select.rows->Belt.Array.map(mapRows);
       Js.log(rows);
     | _ => Js.log("Not select")
     };

     client->Pg.close |> ignore;

     resolve(true);
   })
|> catch(err => {
     Js.log(err);
     client->Pg.close |> ignore;
     resolve(true);
   });