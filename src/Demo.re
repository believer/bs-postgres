open Pg;
open Js.Promise;

let client = Pg.client(~host="localhost", ~port=5432, ());

client->Pg.connect |> ignore;

type user = {city: string};

let mapRows = item =>
  Json.Decode.{city: item |> withDefault("", field("city", string))};

Pg.query(~client, ~query="select * from users limit 10", ())
|> then_(res => {
     switch (res) {
     | Select(select) =>
       Js.log2("select", select.rows);

       /* Log it */
       let rows = select.rows->Belt.Array.map(mapRows);
       Js.log(rows);
     | Insert(insert) => Js.log2("insert", insert.rowCount)
     | something => Js.log2("Not select", something)
     };

     client->Pg.close |> ignore;

     resolve(true);
   })
|> catch(err => {
     Js.log(err);
     client->Pg.close |> ignore;
     resolve(true);
   });
