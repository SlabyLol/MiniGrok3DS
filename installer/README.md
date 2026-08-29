# MiniGrok Installer

Homebrew app that installs `MiniGrok.3gx` to:

```text
sd:/luma/plugins/default.3gx
```

so the plugin loads for **all games**.

## Build (CI does this)

1. Build the plugin (`MiniGrok.3gx`) first
2. Copy it to `installer/data/MiniGrok.3gx`
3. `cd installer && make`

Produces `MiniGrokInstaller.3dsx` (and optionally `.cia`).

## Use on 3DS

1. Install/run the installer via Homebrew Launcher (`.3dsx`) or CIA
2. Press START when done
3. Enable Plugin Loader in Rosalina
4. Reboot, start any game, **SELECT + X**
