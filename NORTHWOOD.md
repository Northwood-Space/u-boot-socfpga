# Northwood Altera U-Boot

## Developer Environment
```bash
$ nix develop .#
```

This will drop you into a shell with all of the required tools to compile U-Boot, including symlinking our Arm Trusted Firmware (ATF) BL31 binary.

### menuconfig
Uncomment out `# menuconfig = true` in the `flake.nix` and reenter your shell with `nix develop .#`

### xconfig
Uncomment out `# xconfig = true` in the `flake.nix` and reenter your shell with `nix develop .#`

## Building
For instructions on how to build U-Boot, please follow upstream U-Boot documentation or Altera's [Building Bootloader for Stratix10](https://www.rocketboards.org/foswiki/Documentation/BuildingBootloaderStratix10).
To simplify automation, there is a `justfile` at the root of this repository that will build the bootloader for you.
Listing the current commands and their functionality can be done using `just --list`

