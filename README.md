# Cache cleaner

![Platform](https://img.shields.io/badge/message-Linux-lightgrey?label=Platform)
[![Release](https://img.shields.io/github/v/release/eufjdknasquwy/cache-cleaner-linux?label=Release)](https://github.com/eufjdknasquwy/cache-cleaner-linux/releases)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![Changelog](https://img.shields.io/badge/Changelog-blue)](CHANGELOG.md)
![C++](https://img.shields.io/badge/C%2B%2B-20-blue)
![GTKmm3](https://img.shields.io/badge/GTKmm-3-blue?logo=gtk&logoColor=white)
[![Linux testing](https://img.shields.io/github/actions/workflow/status/eufjdknasquwy/cache-cleaner-linux/ci.yml?label=Linux-testing&branch=main)](https://github.com/eufjdknasquwy/cache-cleaner-linux/actions/workflows/ci.yml)
[![Download AppImage](https://img.shields.io/badge/Download-AppImage-blue?logo=appimage&logoColor=white)](https://github.com/eufjdknasquwy/cache-cleaner-linux/releases/latest/download/cache-cleaner-x86_64.AppImage)
[![Download Binary](https://img.shields.io/badge/Download-Binary-blue?logo=linux&logoColor=white)](https://github.com/eufjdknasquwy/cache-cleaner-linux/releases/latest/download/cache-cleaner)

A utility for Linux to free disk space by cleaning caches of package managers and other caches

## Table of contents

- [Status](#status)
- [Screenshots](#screenshots)
- [Features](#features)
- [How it works](#how-it-works)
- [Dependencies](#dependencies)
- [Installation](#installation)
- [Usage](#usage)
- [Configuration](#configuration)
- [Limitations](#limitations)
- [Known issues](#known-issues)
- [Roadmap](#roadmap)
- [Changelog](#changelog)
- [License](#license)
- [Credits](#credits)

## Status

**Alpha v0.5.0** — supports `yay`, `paru`, `pip`, `go`, `nuget`, `npm`,
and system caches: `pacman`, `apt`, `dnf`, `flatpak`, `snap`, `journalctl`.
Supports GUI and CLI (headless) modes.

## Screenshots

![GUI](docs/screenshots/GUI.png)
![CLI](docs/screenshots/CLI.png)

## Features

### GUI
- Categories by danger level
- Checkboxes for individual paths, displayed in a table
- Confirmations before deleting
- Clear trash button
- Tray

### CLI
- `--list` - list all caches
- `--delete-safe`, `--delete-warning`, `--delete-unknown`, `--delete-system`, `--delete-user` - delete cache in category (all caches)
- `-y` / `--yes`, `--dry-run` - for scripts / testing
- `t` / `--tray` — run in tray
- `-V` / `--verbose` - show debug logs
- `--trash` - clear trash bin

### Cache support
- AUR helpers: `yay`, `paru`
- Programming languages such as `pip`, `go`, `nuget`, `npm`
- System package managers such as `pacman`, `apt`, `dnf`, `flatpak`, `snap`
- System cache and logs: `docker, podman, journalctl`

### Configuration
- You can add your own caches by editing `~/.config/cache-cleaner/user_categories.json`.
See [Configuration](#configuration-1)

## How it works

1. Reads built-in and user JSON configs with cache paths
2. Displays them in the window as table rows, grouped by danger level
3. When you click **Clear selected**:
   - **Non-system caches** are moved to trash
   - **System caches** are cleared via `pkexec` (sudo)
4. Confirms before cleaning

## Dependencies

- A C++20 compiler (GCC 10+ or Clang 11+ or other)
- CMake 3.16+
- nlohmann-json
- gtkmm-3.0 (or gtkmm3-dev version)
- GUI polkit agent (**recommended**, as program or system **may freeze** on system cache cleaning in GUI, if you do not have it. e.g. polkit-gnome)

## Installation

### AUR (Arch-based distributions)
Currently, the AUR package is not available. But you can build it yourself:
```bash
makepkg -si
```

### Other distributions (appimage)
1. Go to the [Releases](https://github.com/eufjdknasquwy/cache-cleaner-linux/releases) page.
2. Download the latest `cache-cleaner-x86_64.AppImage` file
3. Open directory with downloaded file in terminal, make it executable and launch it:
  ```bash
  chmod +x cache-cleaner-x86_64.AppImage
  ./cache-cleaner-x86_64.AppImage
  ```

### Other distributions (building from source)
```bash
git clone https://github.com/eufjdknasquwy/cache-cleaner-linux
cd cache-cleaner-linux
cmake -B build -S .
cmake --build build
sudo cmake --install build # for .desktop file and a terminal command in your system
```

## Usage

### GUI
1. Install the program (see above)
2. Run:
  ```bash
  cache-cleaner
  # or appimage version:
  ./cache-cleaner-x86_64.AppImage
  ```
3. Select the caches you want to clean and confirm

### CLI
See `cache-cleaner --help` in your terminal

## Configuration

`~/.config/cache-cleaner/user_categories.json` - path to custom configuration

Example:
```json
{
  "categories": [
    {
      "entries": [
        { "name": "my-app", "desc": "cache of my app", "path": "~/.cache/my-app", "type": "path" },
        { "name": "some-app", "path": "~/some-app", "type": "command", "command": "some-app --clean-cache", "root": false }
      ]
    }
  ]
}
```
For details, see [Configuration](docs/configuration/Configuration.md)

## Limitations

- Linux only
- Root caches require GUI polkit agent
- Cannot launch user's own scripts for cleaning cache **yet**

## Known issues

- No fallback to `sudo` if `pkexec` is unavailable
- No progress bar for delete operations
- No way to cancel deletion (except for Ctrl+C)
- Currently no AUR repository

## Roadmap

### Done
- [x] Cleaning package manager caches such as `pip`, `yay` and more
- [x] Cleaning system caches and system package managers such as `pacman`, `apt` and more
- [x] Cleaning systemd logs (`journalctl`)
- [x] Confirmation dialogs before deleting
- [x] Root cache cleaning
- [x] CLI mode
- [x] Report after cleaning
- [x] Cache size showcase and sorting by descending size
- [x] Logging in terminal and to file
- [x] Colorful logging in terminal
- [x] `--dry-run` and `--yes` options for scripts
- [x] Export clear report to JSON
- [x] Custom style and animations
- [x] User feedback in GUI (error messages)
- [x] Notifications
- [x] Tray
- [x] Preview before deletion
- [x] Freed size in notifications and clear report

### Planned
- [ ] Port from GTK3 to GTK4 and port from Appindicator to Appindicator-glib
- [ ] Progress bar when deleting
- [ ] Ability to cancel deletion
- [ ] Search cache in categories
- [ ] Disk analyzer
- [ ] Button to delete from every category
- [ ] Hotkeys
- [ ] Cleaner of old Linux kernels
- [ ] Big files finder - top x biggest files
- [ ] Script type for user config (can add a script to execute)
- [ ] Cleaner of browser files (history, cookies and other)

## Changelog

See [Changelog](CHANGELOG.md)

## License

MIT, see [LICENSE](LICENSE)

## Credits

- [gtkmm](https://github.com/GNOME/gtkmm) - GUI
- [nlohmann/json](https://github.com/nlohmann/json) - JSON