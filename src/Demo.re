open Js.Promise;

let client = Pg.client(~host="localhost", ~port=5432, ());

client->Pg.connect |> then_(_ => resolve(true));

Pg.query(client, "select * from users")
|> then_(res => {
     switch (res) {
     | `Select(value) => Js.log2("value", value)
     | `Error => Js.log("error")
     };

     resolve(true);
   });

client->Pg.close |> then_(_ => resolve(true));