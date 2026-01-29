# HammerIdFix

A Metamod plugin that fixes hammerids not applying on entities outside of tools.

## Original Author

**Poggu** - [https://poggu.me/](https://poggu.me/)

This fork simply adds a configuration file to make it easier to update offsets without having to recompile the plugin.

## Configuration

The plugin automatically creates a configuration file at `game/csgo/addons/configs/hammerid_fix/config.ini` on first load.

You can modify the offsets in this file:

```ini
"Config"
{
	"offsetlinux"		"117"
	"offsetwindow"		"118"
}
```

If the configuration file doesn't exist, it will be automatically created with default values.