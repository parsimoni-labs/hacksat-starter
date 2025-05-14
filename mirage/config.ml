(* mirage >= 4.7.0 & < 4.10.0 *)
open Mirage

let client =
  let packages = [
      package ~pin:"git+https://github.com/Firobe/ocaml-cohttp.git#fix-mirage-client" "cohttp-mirage";
      package ~pin:"git+https://github.com/Firobe/ocaml-cohttp.git#fix-mirage-client" "cohttp-lwt";
      package ~pin:"git+https://github.com/Firobe/ocaml-cohttp.git#fix-mirage-client" "cohttp";
      package ~pin:"git+https://github.com/Firobe/ocaml-cohttp.git#fix-mirage-client" "http";
      package "duration"
  ] in
  main ~packages "Unikernel.Client" (http_client @-> job)

let () =
  let stack = generic_stackv4v6 default_network in
  let res_dns = resolver_dns stack in
  let conduit = conduit_direct ~tls:false stack in
  let job = [ client $ cohttp_client res_dns conduit ] in
  register "http-fetch" job
