# WINDOWS virtual box preparation hints  

Our aim is to prepare windows headless virtual box. Jenkins will get from git sources, so we should share source folder with guest WINDOWS.  
The root path of host will be mounted to guest Windows, this will make possible to compile sources from any directory of host.  
The name of '/' shared folder is 'ROOT ', so to access it from guest Windows '\\vboxsvr\ROOT' should be used.  
The script for scheduled task is running script 'X:\ers\compilation_daemon.bat' on guest Windows and '/ers/compilation_daemon.bat' on host LINUX.  
Task name of scheduled task is 'ers_compilation_daemon'  
  
## How to use  
```bash
run_on_host 192.168.56.101 msbuild to_compile_by_service_test.sln /t:Rebuild /p:Configuration=Debug;Platform=x64  
run_on_host 192.168.56.101 devenv to_compile_by_service_test.sln /rebuild "Debug|x64"  
run_on_host 192.168.56.101 cmake -G "Visual Studio 15 ARM" ..  
run_on_host 192.168.56.101 cmake --build .  
```
  
## some usefull links  
[wiki](https://github.com/davitkalantaryan/virtual_box_to_run_commands/wiki)  
[windows installation media download](https://www.microsoft.com/en-us/software-download/windows10)  
[prepare windows virtual box](https://en.wikibooks.org/wiki/VirtualBox/Setting_up_a_Virtual_Machine/Windows)  
[windows headless VBOX](https://stackoverflow.com/questions/19017825/how-to-run-oracle-virtualbox-vbox-in-fully-background-microsoft-windows-wi)   
[share folder with host](https://help.ubuntu.com/community/VirtualBox/SharedFolders)  
[host guet communication](https://www.tecmint.com/network-between-guest-vm-and-host-virtualbox/)  
