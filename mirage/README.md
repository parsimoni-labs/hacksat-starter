# Example Mirage kernel

## Building

### Automatically with petrel

- Retrieve and install the [`petrel` CLI](../tools)
- Edit `petrel.json` as desired and run `petrel build`
- The resulting unikernels are in `_petrel/TARGET_NAME/image`

### Manually with docker

- Run:
  ```bash
  $ docker build -t builder .
  $ id=$(docker run -dt builder)
  $ docker cp $id:/mnt/output/image example.arm64
  $ docker kill $id
  ```
- The resulting unikernel is at `example.arm64`.

If you just want to test it, this repository contains a pre-built unikernel
(`example.x86` and `example.arm64`).

## Running

- You can upload it on `hacksat.dev` as an *image*
- To run it, *deploy the image* and specify the following runtime arguments:
  ```
  --ipv4 10.0.42.6/24
  ```
  You can use any other IP in the 10.0.42.1/24 range.
- The logs should display "pong" as a reponse from the satellite.

## Hacking

Read the hacksat docs for what interaction your unikernel can have with the
simulated satellite, and head out to [MirageOS' website](https://mirage.io/docs)
to learn what is possible to do with MirageOS and how to write more complex
applications.
