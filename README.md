# Hacksat starter pack

- See the [mirage/](mirage/) directory for instructions on how to build and run
  a basic Mirage unikernel, and a starting template.
- See the [unikraft/](unikraft/) directory, the same for Unikraft.

The rest of this page documents the general usage of both the
[hacksat.dev](https://hacksat.dev) web portal and what capabilities are
accessible on-board from unikernels.

## Constraints on uploaded unikernels

- 50 MB or less
- For aarch64 or x86_64 (fallback)
- Either a solo5 (mirage) or qemu-compatible unikernel
- Only expects a single network interface as connection to the on-board system.
- No attached volumes or initrd, everything must be part of the binary or come
  from the on-board capabilities.
- Logs larger than 500kB are truncated.
- All unikernels are killed after running more than 10 minutes.

If your idea needs to lift some of these constraints, contact us
(hacksat@parsimoni.co).

## Information about the infrastructure

### On-board computers

- UCM-IMX8MP (provided by DPhi Space)
  - aarch64, 4 cores
  - 4 Gb RAM
  - Linux kernel 6.6.23
  - both qemu and solo5 backends available
- LX2160 ARDB Rev.2 (provided by Thales Alenia Space)
  - aarch64, 16 cores
  - 32 Gb RAM
  - Linux kernel 6.1.55
  - both qemu and solo5 backends available
- Colossus Kestrel (provided by Colossus Compute)
  - aarch64, 4 cores
  - 8 Gb RAM
  - Linux kernel 4.9.337-tegra, with backported KVM patches
  - qemu not available for security, solo5 available
- Off-the shelf server, fallback
  - x86_64, 8 cores
  - 8 Gb RAM
  - Linux kernel 5.15.0-139
  - both qemu and solo5 backends available

Deployments are dispatched to a compatible computer based on the current load of
each. All computers and the Hackathon backend (hosting hacksat.dev) are running
on the same network, talking over a TLS-encrypted Cap'n'Proto protocol.

### Virtualization

Virtual machines monitors for KVM:
- [solo5-hvt](https://github.com/Solo5/solo5) 0.9.1 for MirageOS
  - arguments passed:
    `--mem=MEMORY_LIMIT --net:service=TAP_NAME --net-mac:service=GENERATED_MAC -- UNIKERNEL_ARGS`
- qemu (KVM) 9.2.2 for Unikraft
  - arguments passed:
    ```
    -enable-kvm -nographic -nodefaults -machine virt -cpu host -serial stdio \
        -netdev tap,id=hnet0,ifname=TAP_NAME,vhost=off,script=no,downscript=no \
        -device virtio-net-pci,netdev=hnet0,id=net0 \
        -append 'UNIKERNEL_ARGS'
    ```

All unikernels are connected to a `tap` interface (with a random MAC address) created on the fly.

### Networking

A running unikernel is bridged to every other unikernel running on the same
computer, and the "service-provider" unikernel.

The "service-provider" unikernel is always-running unikernel on core 0 with 512
Mb of RAM allocated, listening at IP 10.0.42.2 on port 80, and responding to
HTTP request, unencrypted. It is used to provide the services below.

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

This list will be gradually expanded as the hackathon progresses through the
month.
