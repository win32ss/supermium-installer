This is the repository for the Supermium installer and uninstaller.

The Supermium installer can be combined with the 7zip installer stub named 7zSD.sfx and config.txt using
``copy /b 7zSD.sfx + config.txt + supermium_setup.7z supermium_setup.exe``.

supermium_setup.7z has the following contents:
``setup.exe``
``directory containing all program contents named "Supermium"``
``NotoEmoji.ttf``

The Supermium uninstaller will normally be located in the application folder (the one that contains the executable).
When executed, it copies itelf to a temp folder. This copy is executed with the command line switch ``--payload`` 
to run the actual uninstallation operation, deleting the directory in the process.

The project files are VS2022-compatible.
