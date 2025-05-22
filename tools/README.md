# Petrel CLI build tool

Given Docker on the machine and a `petrel.json` file, fully automate unikernel building.

## Install

`petrel` is distributed as a statically-linked executable for x86_64

```bash
$ chmod +x ./petrel-cli.x86
$ cp ./petrel-cli.x86 ~/.local/bin/petrel
```

## Configure

Create `petrel.json` (see examples in `mirage/` and `unikraft/`) in the
unikernel's repository.

## Run

```bash
$ petrel build
$ tree _petrel
_petrel
├── qemu-amd64
│   ├── Dockerfile
│   └── image
└── qemu-arm64
    ├── Dockerfile
    └── image
```
