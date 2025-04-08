default:
  just --list

# Run all required cleaning commands
[group('Build')]
clean:
  make clean && make mrproper

[group('Build')]
build:
  just beamformer

# Build the Beamformer U-Boot
[group('Build')]
build-beamformer:
  make -j$(nproc) $makeFlags

# Generate .config for the beamformer defconfig
[group('Build')]
configure-beamformer:
  make nw-beamformer_defconfig

# Configure and build the beamformer U-Boot
[group('Build')]
beamformer:
  just configure-beamformer
  just link-bl31
  just build-beamformer

# Link arm trusted firmware into root directory. Replacing if it already exists
[group('Build')]
link-bl31:
  ln -sf $BL31 .
