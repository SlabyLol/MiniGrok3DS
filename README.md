# MiniGrok

Cute AI assistant **3GX plugin** for Nintendo 3DS (Luma3DS + CTRPluginFramework).

## Quick install (manual)

1. Download artifact **MiniGrok-3gx** from Actions
2. Copy `MiniGrok.3gx` to:
   ```text
   sd:/luma/plugins/default.3gx
   ```
   (for one game only: `sd:/luma/plugins/<TITLEID>/MiniGrok.3gx`)
3. Rosalina → Plugin Loader = **Enabled**
4. Start a game → **SELECT + X**

## Installer (all games)

Actions also builds **MiniGrok-Installer**:

1. Download artifact **MiniGrok-Installer**
2. Put `MiniGrokInstaller.3dsx` on SD (e.g. `/3ds/`)
3. Open with **Homebrew Launcher**
4. It writes `default.3gx` automatically
5. Reboot, enable Plugin Loader, start any game, **SELECT + X**

`.cia` is built when `makerom` is available in CI (optional).

## Build

Plugin (BlankTemplate layout):

```bash
make
```

Installer (after plugin exists):

```bash
cp MiniGrok.3gx installer/data/
cd installer && make
```

## Hotkey

**SELECT + X**

OSD on load: `MiniGrok loaded!`
