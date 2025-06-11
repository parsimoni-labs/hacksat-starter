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

**Create a tap interface**

```
$ ip tuntap add tap100 mode tap
$ ip addr add 10.0.42.1/24 dev tap100
$ ip link set dev tap100 up
```

**Run the unikernel**

```
$ solo5-hvt --mem=512 --net:service=tap100 UNIKERNEL_FILE`
$ curl http://10.0.42.2/ping
```
