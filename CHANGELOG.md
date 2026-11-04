# Changelog

## Latest release (v0.6.0) - 2026-11-04

### Added
- Header bar
- App settings
- Size of caches in `--list` option and in preview
- Documentation for configuration

### Changed
- Cache deletes permanently instead of to trash (will add an option for cleaning to trash)

### Fixed
- Logging debug messages even without `--verbose` option

## Rebranding (v0.5.1) - 2026-11-02

### Added
- Icons of many resolutions such as x32, x64, x256 and others

### Changed
- Cache cleaner is now Byte Purge
- `bytepurge` command instead of `cache-cleaner`

## Stable release (v0.5.0) - 2026-11-01

### Added
- SIGINT/SIGTERM Handler
- Tray
- Notifications
- Preview before deletion
- Shows freed size in notifications and clear report
- `--trash` option to clear trash bin
- `--verbose` option to log debug messages

### Changed
- Optimized program loading and scanning cache
- Default user config now creates from a template user config

### Fixed
- `--tray` option showing empty window
- Async operations not being async (deleting should be much faster now)

## Patch (v0.4.2) - 2026-10-27

### Fixed
- Icon not being visible
- Program's style and caches not working after deleting source code

## Patch (v0.4.1) - 2026-10-25

### Fixed
- Empty categories showing up, even though they dont have available caches
- CLI version not showing system package manager, while GUI does
- Incorrect color enabling in terminal logging

## Stable release (v0.4.0) - 2026-10-25

### Added
- Clear report export to `JSON`
- Support for 95%+ Linux distributions package managers
- Button `clear trash`
- Colored logging in terminal
- Changelog
- Animations and custom style
- `cmake --install` command support
- `cache-cleaner.desktop` file
- Logging to file
- User feedback in GUI (error messages)
- AUR package (PKGBUILD)
- Appimage package

### Changed
- Improved UI: cache sorts out in tables by size descending, custom style with animations
- Improved JSON parsing: more flexible config

### Fixed
- Crashes on incorrect JSON format
- Program crashing in some other situations
- Clear report showing wrong command exit code
- Caches being cleared by paths, instead of by commands
- Not cleaning cache by commands properly
- Fixed config bugs: name/path dublicates not adding to the list properly and more