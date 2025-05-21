# Service provider unikernel

These are the exact binaries of the currently deployed "service-provider"
unikernel on board of all runners. It is built using MirageOS, with the
following (open-source) components:

- OCaml version 5.3.0
- Mirage version 4.9.0
  - mirage-ethernet
  - mirage-arp
  - mirage-tcpip
- http/af (ocaml-h1) 1.0.0 as the HTTP server

## Running

`solo5-hvt --mem 512 --net:service=TAP_NAME -- -l debug`

where `TAP_NAME` is a Linux tap device bridged to client unikernels
