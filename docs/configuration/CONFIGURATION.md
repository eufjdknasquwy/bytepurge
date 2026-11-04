# Configuration

BytePurge uses a JSON file to manage cache paths

> **Note**
> The configuration is optional. If you don't need custom caches, BytePurge works out of the box using its built-in defaults.

## Location
By default, the user configuration is located at:
`~/.config/bytepurge/user_categories.json`

If you delete this file or you do not have one, BytePurge will generate a new one with default values on the next launch

## Format
The file consists of cache entries, which have name, path, type and other options

```json
{
  "categories":
  [
    {
      "entries":
      [
          { "name": "Some cache", "path": "~/.cache/some-cache", "type": "path" },
          { "name": "Other cache", "path": "~/.cache/other-cache", "type": "command", "command": "other-cache --clean" } // NO COMMA HERE
      ]
    }
  ]
}
```
**Note**: Make sure there is no trailing comma after the last entry } in the array, otherwise the JSON parser will fail

## Entries
- **name** (optional): name that will be displayed in a table
- **desc** (optional): description for the cache
- **path** (required): cache path that will be checked for existence, and be deleted, if the type is path
- **type** (required): cache type. available types:
  1. `path` - the cache is deleted by path
  2. `command` - the cache is deleted by command
- **command** (required if type is command): command to clear the cache
- **root** (optional): `true` or `false`. if true, the command will be executed as root

## Examples

1. Example 1:
To add a cache, that will be deleted by path, you can add it like this:
```json
{ "name": "My app", "desc": "Description for this cache", "path": "~/.cache/my-app", "type": "path" }
```

2. Example 2:
To add a cache, that is deleted by command without root, you should set "type" to "command" and add the command:
```json
{ "name": "My app", "desc": "Description for this cache", "path": "~/.cache/my-app", "type": "command", "command": "myapp --clean cache", "root": false }
```

3. Example 3:
To add a cache, that is deleted by command with root, you should set "root" to true:
```json
{ "name": "My app", "desc": "Description for this cache", "path": "~/.cache/my-app", "type": "command", "command": "myapp --clean cache", "root": true }
```

Root paths cannot be deleted, root cleaning is only available for the commands
After you have added something in your user config, the cache should appear in the user category after scanning cache or relaunching the program (if the cache in the path exists)

## Safety
- Be cautious as this program executes commands through the system shell. Ensure you only copy configs from trusted sources or edit it carefully yourself, especially for commands that require root access

## Troubleshooting
- If the cache doesn't show up in your user category, check if the path is valid and that directory does indeed exist
- If a JSON parse error occurs, check for trailing commas, missing commas or missing quotation marks ("") in your config
- If a "permission denied" error occurs, that means that the cache you are cleaning needs root. If you are cleaning by path, you cannot clean it in root. If you need to delete a root-owned directory by path, you should create a command entry instead (e.g., "command": "rm -rf /var/cache/my-app"), but again, be cautious