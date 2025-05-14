# Hacksat starter pack

- See the [mirage/](mirage/) directory for instructions on how to build and run
  a basic Mirage unikernel, and a starting template.
- See the [unikraft/](unikraft/) directory, the same for Unikraft.

The rest of this page documents the general usage of both the
[hacksat.dev](https://hacksat.dev) web portal and what capabilities are
accessible on-board from unikernels.

## Constraints on uploaded unikernels

- 50 MB or less
- For x86_64 or aarch64
- Either a solo5 (mirage) or qemu-compatible unikernel
- Only expects a single network interface as connection to the on-board system.
- No attached volumes or initrd, everything must be part of the binary or come
  from the on-board capabilities.
- Logs larger than 500kB are truncated.

## On-board capabilities

On-board capabilities are accessible through a simple REST HTTP interface.
The on-board server servicing capabilities request is always reachable at IP
`10.0.42.2` on port 80.

This means to indirect with the satellite, unikernels need to embed a simple
HTTP client implementation. Examples in the `mirage` and `unikraft` directories
show how to do this.

### Ping

- **Endpoint:** `GET /ping`
- no parameters or data
- **Response:** `pong`

This most simple capability is used to check that your unikernel is correctly
interfacing with the on-board system, and should simply return pong.

### More to come

This list will be gradually expanded as the hackathon progress through the
month.
