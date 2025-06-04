# Hacksat starter pack

- See the [mirage/](mirage/) directory for instructions on how to build and run
  a basic Mirage unikernel, and a starting template.
- See the [unikraft/](unikraft/) directory, the same for Unikraft.
- See [HACKING](./HACKING.md) for a description of what's explicitly in or out
  of scope for the exploit track, and our proposed reward scheme according to
  the severity of the discovered exploits.

The rest of this page documents the general usage of both the
[hacksat.dev](https://hacksat.dev) web portal and what capabilities are
accessible on-board from unikernels.

> [!NOTE]  
> Feel free to ask questions by either opening issues on this repository or
> sending an email to `hacksat@parsimoni.co`.

## Getting started

Here's the shortest possible method to get something running on our of our
computers:

- download a pre-built "ping" image for aarch64 CPUs: either
    [mirage](./mirage/example.arm64)
    or
    [unikraft](./unikraft/example.arm64)
- go to https://hacksat.dev and create an account or sign in
- create a project by clicking the "New project" button and give it a name
- head to the "Images" tab
- click the "Upload image" button and select the file you downloaded in the first step
- once created, click on the "Deploy" button on the top right, select the image you just created, and add the following runtime arguments:
  - for Mirage: `--ipv4 10.0.42.6/24`
  - for Unikraft: `netdev.ip=10.0.42.6/24 --`
- create the deployment, and then hit the Play button
- after refreshing the page, you should see your unikernel getting assigned a computer, and the logs from its run

**What do to next:** see the [mirage/](mirage/) and [unikraft/](unikraft/) directories for instructions on how to actually build these unikernels yourself, and start from this template to either exploit or build!

## Submissions

Submissions for either the "exploit" or "use-case" track or done by sending an email to
[hacksat@parsimoni.co](mailto:hacksat@parsimoni.c).

### Exploit track

> [!IMPORTANT]  
> Verify that your exploit is eligible by reading the scope rules in
> [HACKING](./HACKING.md).

Send as a brief description of your exploit, with as much detail as possible,
including if relevant:
- a detailed explanation of it
- a proof-of-concept unikernel (or artifact) reproducing the exploit
- the on-board computer it applies to, if it is specific to one
- the relevant times an attack was performed, so the logs can be checked
- any other detail you deem relevant so we can check the exploit is real and
    (ideally) reproducible.

Whether rewarded or not, all exploits in scope that are submitted will be
transparently published (and credited to their authors) in the final report.

### Use-case track

Send us an explanation of your idea for edge computing in space, and describe:
- its applicability (how broadly useful would your application be)
- your experiments building it as a unikernel (provide examples, compiled
    unikernels or source code if you can or want). Note that this can be at a
    proof-of-concept stage.
- its general resource usage:
  - memory and CPU requirements
  - how it interacts (or would interact) with the satellite capabilities:
      storage, sensors, networking, etc.
- your interest in demonstrating this idea in a live mission

## Constraints on uploaded unikernels

- 50 MB or less
- For aarch64 or x86_64 (fallback)
- Either a solo5 (mirage) or qemu-compatible unikernel
- Only expects a single network interface as connection to the on-board system.
- No attached volumes or initrd, everything must be part of the binary or come
  from the on-board capabilities.
- Logs larger than 500kB are truncated.
- All unikernels are killed after running more than 10 minutes.


> [!NOTE]  
> If your idea needs to lift some of these constraints, contact us
> at `hacksat@parsimoni.co`

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

The exact binaries for the unikernel that provides these capabilities along some
information about the stack used, can be found in [this directory](./onboard-software/service-provider).

Note that all authenticated endpoints use an API key that can be generated in
the "Key" tab of the web interface. That key must then be embedded in the
unikernel or passed as a CLI argument (see examples).

### Ping

- **Endpoint:** `GET /ping`
- no parameters or data
- **Response:** `pong`

This most simple capability is used to check that your unikernel is correctly
interfacing with the on-board system, and should simply return pong.

**The capabilities below are not yet deployed on the production computers.**

### Downlink

- **Endpoint:** `POST /downlink/:filename`
- **Authorization:** `Bearer API_KEY`
- **Body**: raw data to downlink
- **Response:** 201 Created on success

This endpoint is used to downlink arbitrary data (within a 5 Mb limit) to the
ground station, making it available as the given filename. The file will appear
in the web interface and be fetched from the on-board computer on demand, for
download.

### Orbital data

- **Endpoint:** `GET /orbital-parameters`
- no parameters or data
- **Response:** CSV data

The returned CSV data contains the current reading of the orbital parameters.
The CSV contains a header with a list of parameter names.

This simulated orbital data is based on the OPS-SAT 1 telemetry dataset. For
more details on the dataset and the kind of analysis you can perform with it
see: <https://opssat.esa.int/ops-sat-1/reentry_dataset/>.

### Sensor data

- **Endpoint:** `GET /sensors/imaging-01`
- no parameters or data
- **Response:** TIF image data

Produces an image file of a simulated onboard imaging sensor. Each image
measures 256x256 pixels and represent a distinct terrain type.

This dataset can be used to test terrain classification models.

The images are part of the UC Merced Land dataset. For more details see:
<http://weegee.vision.ucmerced.edu/datasets/landuse.html>.

### Restart

- **Endpoint:** `POST /restart`
- **Authorization:** `Bearer API_KEY`, admin account
- **Response:** 200 on success, 403 on failure

Restart the whole computer. This is a privileged endpoint that should only be
accessible by admin accounts.

### More to come

This list will be gradually expanded as the hackathon progresses through the
month.
