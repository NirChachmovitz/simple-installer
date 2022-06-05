# Simple Installer

Simple Installer is a C++ product that mimics the action of the Windows Installer,
and supports several transacted operations, such as:

- Copying existing files (all formats are supported) to a target directory
- Editing and creating registry keys 

The installer is intended to run on Windows platforms, although the transition to a Linux environment requires not too much.

A logger is also included to log each action made.


## Running

```console
> SimpleInstaller.exe <configuration_path>
```

The configuration path is linked a json file, contains all the data needed to run.


## Configuration

The configuration to the installer is a json file, which contains a list of tasks - rollbackable operations.
Each of the tasks can be either a `FileInstallerTask` or a `RegistryInstallerTask`.
One day, be sure that more tasks will be joined :)


### Configuration Example

Assume you wish to install a not so innocent executable, together with its configuration file, 
and make sure it runs persistently each startup.

Therefore, the configuration file should be as following:

```json
{
  "tasks": 
  [
    {
      "type": "FileInstallerTask",
      "source_file_path": "C:\\a\\b\\c\\innocent.exe",
      "target_directory_path": "C:\\tmp"
    },
	{
      "type": "FileInstallerTask",
      "source_file_path": "C:\\d\\e\\f\\configuration.json",
      "target_directory_path": "C:\\conf"
    },
	{
	  "type": "RegistryInstallerTask",
	  "registry_key_path": "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
	  "registry_value_name": "innocent",
	  "registry_value": "C:\\tmp\\innocent.exe"
	}
  ]
}
```

## Flow

- Validating the arguments
- Parsing the configuration
- Installing the files & registry keys, in a trusacted way
	- In case of a rollback, all will be returned to previous state (either the previous data, or the file will be deleted if didn't exist)
	- Installer class contains a stack of all the operations made in the order they made, so the rollback is assured to be safe
	- Same goes for tree of directories which did not exist
- Finish :)
