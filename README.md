# MiniGrok

Cute AI assistant plugin for Nintendo 3DS (CTRPluginFramework / 3GX).

Built on the official **CTRPluginFramework BlankTemplate** layout.
CI uses `pablomk7/libctrpf:0.8.0` (same as BlankTemplate).

## Install

1. Rosalina → Plugin Loader = **Enabled**
2. Copy artifact to: `sd:/luma/plugins/default.3gx`
3. Remove other default plugins (e.g. Nimbus) while testing
4. Start a **game**
5. Open: **SELECT + X**

You should see OSD: `MiniGrok loaded!`

## Build

```bash
make
```

Produces `MiniGrok.3gx`.
