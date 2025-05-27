# Example Unikraft kernel

## Building

### With docker

You can build this project with docker by running the following commands:
```bash
$ docker build -t kraft .
$ docker run -it -v "$PWD:/mnt/build" kraft build --plat qemu --arch arm64 
```

The build results can be found in `.unikraft/build/`.

### Manually with kraftkit

- Install [`kraftkit`](https://unikraft.org/docs/cli/install)
- Run:
  ```bash
  $ export UK_CFLAGS="-std=gnu17 -Wno-implicit-function-declaration"
  $ kraft build --plat qemu --arch x86_64 # for x86-64
  $ kraft build --plat qemu --arch arm64 # for aarch64
  ```
- The resulting unikernel is at `.unikraft/build/http-c_qemu-*`.

If you just want to test it, this repository contains a pre-built unikernel
(`example.x86` and `example.arm64`).


## Running

- You can upload it on `hacksat.dev` as an *image*
- To run it, *deploy the image* and specify the following runtime arguments:
  ```
  netdev.ip=10.0.42.6/24 --
  ```
  The `--` is important. You can use any other IP in the 10.0.42.1/24 range.
- The logs should display "pong" as a reponse from the satellite.

## Hacking

Read the hacksat docs for what interaction your unikernel can have with the
simulated satellite, and head out to [Unikraft's website](https://unikraft.org/docs/getting-started)
to learn what is possible to do with Unikraft and how to write more complex
applications.
