# MiniGrok 🤖✨

**The cute AI assistant for your Nintendo 3DS**

MiniGrok is a 3GX plugin for Luma3DS that brings a chat with Grok directly to your console – including a cute face, screen reading, file access and title launching. Everything with permission prompts.

## Features (Concept)

- **Hotkey**: Select + X (changeable)
- Overlay menu in the style of Rosalina
- Chat window with MiniGrok face + animations
- Read screen (framebuffer capture) → send to Grok
- Read / write / create files (with permission)
- Open / launch titles (with permission)
- Multi-language (EN / DE / more planned)
- Settings via separate CIA (later)
- API key in `sd:/luma/plugins/MiniGrok/api.txt`

> **Important**: MiniGrok is a **client**. The actual AI runs at xAI. The 3DS needs internet and responses take a few seconds.

## Current Status

This is the **project skeleton** (v0.1 – Foundation).

- Basic structure with CTRPluginFramework
- Menu system
- Permission system stub
- Chat UI stub + face animation placeholders
- File and title stubs
- Multi-language foundation
- Build system ready
- GitHub Actions workflow

The hard parts (real API calls, screen capture, custom renderer for the face) are marked as TODOs and still need to be implemented.

## GitHub Actions

A workflow runs on every push / PR to `main`:

- Uses the official `devkitpro/devkitarm` Docker image
- Installs `3ds-dev` packages
- Attempts to build the project
- Uploads artifacts (logs + any produced binaries)

You can also trigger it manually via **Actions → Build MiniGrok → Run workflow**.

> **Note**: A complete `.3gx` currently requires CTRPluginFramework (`libctrpf`) + `3gxtool`. The CI currently documents the environment and collects build logs until those are fully integrated.

## Requirements to Build (locally)

1. **devkitPro** with the `3ds-dev` metapackage
2. **CTRPluginFramework** (libctrpf) installed
3. **3gxtool** (`pacman -S 3gxtool` or manual)
4. Optional: firmtool / makerom for advanced builds

### Installing CTRPluginFramework

```bash
# Example (adjust depending on version)
git clone https://github.com/PabloMK7/CTRPluginFramework-BlankTemplate
# or take the current libctrpf version and place it in $DEVKITPRO/libctrpf
```

## Building

```bash
cd MiniGrok
make
```

The finished file will be in `output/MiniGrok.3gx` (or similar).

## Installation on the 3DS

1. Luma3DS with Plugin Loader enabled (Rosalina → Plugin Loader = Enabled)
2. Copy the plugin here:
   ```
   sd:/luma/plugins/default.3gx          # for all titles
   # or
   sd:/luma/plugins/<TITLEID>/MiniGrok.3gx
   ```
3. Optional: create folder
   ```
   sd:/luma/plugins/MiniGrok/
   └── api.txt          # your xAI API key (one line)
   ```

## Project Structure

```
MiniGrok/
├── source/
│   ├── main.cpp              # Entry + menu
│   ├── MiniGrokChat.cpp      # Chat logic
│   ├── FaceAnimation.cpp     # Face + animations
│   ├── Permissions.cpp       # Permission dialogs
│   ├── FileHelper.cpp        # File operations
│   ├── TitleHelper.cpp       # Launch titles
│   └── Language.cpp          # Multi-language
├── include/
│   ├── MiniGrokChat.hpp
│   ├── FaceAnimation.hpp
│   ├── Permissions.hpp
│   ├── FileHelper.hpp
│   ├── TitleHelper.hpp
│   └── Language.hpp
├── resources/                # GFX (sprites, face frames, UI)
├── romfs/                    # optional
├── Makefile
├── .gitignore
└── README.md
```

## Next Steps (Roadmap)

- [ ] Custom overlay UI (not just PluginMenu)
- [ ] Simple face with 2–4 animation frames
- [ ] Implement screen capture
- [ ] HTTP client for xAI API (difficult because of TLS)
- [ ] Polish permission dialogs
- [ ] More languages
- [ ] Settings CIA
- [ ] Better animations & sounds
- [ ] Full CI production of `.3gx` (with vendored libctrpf)

## License

This project is open source.  
MiniGrok itself is a fan project and not officially affiliated with xAI.

---

**Made with ❤️ for the 3DS homebrew scene**  
*MiniGrok – small, cute, helpful.*
