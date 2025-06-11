open Lwt.Infix
open Cmdliner

let (let*) = Lwt.bind

module Client (Client : Cohttp_lwt.S.Client) = struct
  let threshold = 500

  let get ctx uri =
    let uri = Uri.of_string uri in
    Logs.info (fun f -> f "Fetching %a with Cohttp" Uri.pp uri);
    let* (reponse, body) = Client.get ~ctx uri in
    let* body = Cohttp_lwt.Body.to_string body in
    let to_print =
      if String.length body > threshold then
        String.sub body 0 threshold
      else body
    in
    Logs.info (fun f -> f "Received: %s" to_print);
    Logs.info (fun f -> f "(total size: %d)" (String.length body));
    Lwt.return_unit

  let start ctx =
    let* () = get ctx "http://10.0.42.2/ping" in
    let* () = get ctx "http://10.0.42.2/orbital-parameters" in
    let* () = get ctx "http://10.0.42.2/sensors/imaging-01" in
    Lwt.return_unit
end
