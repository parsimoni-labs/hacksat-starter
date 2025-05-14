open Lwt.Infix
open Cmdliner

let (let*) = Lwt.bind

module Client (Client : Cohttp_lwt.S.Client) = struct
  let start ctx =
    let uri = Uri.of_string "http://10.0.42.2/ping" in
    Logs.info (fun f -> f "Fetching %a with Cohttp" Uri.pp uri);
    let* (reponse, body) = Client.get ~ctx uri in
    let* body = Cohttp_lwt.Body.to_string body in
    Logs.info (fun f -> f "Received: %s" body);
    Lwt.return_unit
end
