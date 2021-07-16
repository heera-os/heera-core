# Heera Core

Heera system core (based on cyber-workspace->>https://github.com/cyberos/cyber-workspace)

## Compile dependencies

```shell
sudo pacman -S extra-cmake-modules pkgconf qt5-base qt5-quickcontrols2 qt5-x11extras qt5-tools kwindowsystem polkit polkit-qt5 pulseaudio polkit-qt5
```

https://github.com/Skycoder42/QHotkey

## Runtime

```shell
pulseaudio
```

## Build

```shell
mkdir build
cd build
cmake ..
make
```

## Install

```shell
sudo make install
```
