open Js.Promise;
open BsPostgres.Response.Select;

let client = Pg.client(~host="localhost", ~port=5432, ());

client->Pg.connect
|> then_(_ => resolve(true))
|> catch(err => {
     Js.log(err);
     resolve(true);
   });

type user = {city: option(string)};

Pg.query(client, "select * from users limit 10")
|> then_(res => {
     switch (res) {
     | `Select(select) =>
       Js.log2("select", select.rows);
       let rows =
         select.rows
         ->Belt.Array.map(item =>
             Json.Decode.{city: item |> optional(field("city", string))}
           );

       Js.log(rows);
     | `Error(err) => Js.log2("error", err)
     };

     client->Pg.close |> ignore;

     resolve(true);
   })
|> catch(err => {
     Js.log(err);
     client->Pg.close |> ignore;
     resolve(true);
   });
