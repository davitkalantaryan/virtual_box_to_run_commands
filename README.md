# WINDOWS virtual box preparation hints  

Our aim is to prepare windows headless virtual box. Jenkins will get from git sources, so we should share source folder with guest WINDOWS.  
The root path of host will be mounted to guest Windows, this will make possible to compile sources from any directory of host.  
The name of '/' shared folder is 'ROOT ', so to access it from guest Windows '\\vboxsvr\ROOT' should be used.  
The script for scheduled task is running script 'X:\ers\compilation_daemon.bat' on guest Windows and '/ers/compilation_daemon.bat' on host LINUX.  
Task name of scheduled task is 'ers_compilation_daemon'  
  
## How to use  
```bash  
run_on_win_guest msbuild to_compile_by_service_test.sln /t:Rebuild /p:Configuration=Debug /p:Platform=x64  
run_on_win_guest cmd /C ' devenv to_compile_by_service_test.sln /rebuild "Debug|x64" '   
run_on_win_guest cmake -G "Visual Studio 15 ARM" ..  
run_on_win_guest cmake --build .  
```  

## Demo  
variable VBOX_TEST_DIR_ROOT (in the below examples) was set during install  
``` bash   
pushd $VBOX_TEST_DIR_ROOT/virtual_box_to_run_commands/prj/test/to_compile_by_service_test_vs  
mkdir -p $VBOX_TEST_DIR_ROOT/dsys/x64 && mkdir -p $VBOX_TEST_DIR_ROOT/dsys/x86 && mkdir -p $VBOX_TEST_DIR_ROOT/dsys/arm  

run_on_win_guest msbuild /? | less  # let's check all option of msbuild
run_on_win_guest msbuild to_compile_by_service_test.sln /t:Rebuild /p:Configuration=Debug /p:Platform=x64  
run_on_win_guest msbuild to_compile_by_service_test.sln /t:Rebuild /p:Configuration=Debug /p:Platform=x86  
run_on_win_guest msbuild to_compile_by_service_test.sln /t:Rebuild /p:Configuration=Debug /p:Platform=ARM  
echo $?  
nedit $VBOX_TEST_DIR_ROOT/virtual_box_to_run_commands/src/test/main_to_compile_by_service_test.cpp&  
# put error code in the source compile then fix it  
run_on_win_guest msbuild to_compile_by_service_test.sln /t:Rebuild /p:Configuration=Debug /p:Platform=ARM  
echo $?  
run_on_win_guest msbuild to_compile_by_service_test.sln /t:Rebuild /p:Configuration=Debug /p:Platform=ARM  
cp ../../../../sys/win64/bin/to_compile_by_service_test.exe $VBOX_TEST_DIR_ROOT/dsys/x64/msbuild_to_compile_by_service_test.exe
cp ../../../../sys/win32/bin/to_compile_by_service_test.exe $VBOX_TEST_DIR_ROOT/dsys/x86/msbuild_to_compile_by_service_test.exe
cp ../../../../sys/arm_win/bin/to_compile_by_service_test.exe $VBOX_TEST_DIR_ROOT/dsys/arm/msbuild_to_compile_by_service_test.exe

run_on_win_guest cmd /C ' devenv /? ' | less  # let's check all option of devenv
run_on_win_guest cmd /C ' devenv to_compile_by_service_test.sln /rebuild "Debug|x64" '   
run_on_win_guest cmd /C ' devenv to_compile_by_service_test.sln /rebuild "Debug|x86" '    
run_on_win_guest cmd /C ' devenv to_compile_by_service_test.sln /rebuild "Debug|ARM" ' 
cp ../../../../sys/win64/bin/to_compile_by_service_test.exe $VBOX_TEST_DIR_ROOT/dsys/x64/devenv_to_compile_by_service_test.exe  
cp ../../../../sys/win32/bin/to_compile_by_service_test.exe $VBOX_TEST_DIR_ROOT/dsys/x86/devenv_to_compile_by_service_test.exe  
cp ../../../../sys/arm_win/bin/to_compile_by_service_test.exe $VBOX_TEST_DIR_ROOT/dsys/arm/devenv_to_compile_by_service_test.exe   

cmakeDir=${VBOX_TEST_DIR_ROOT}/virtual_box_to_run_commands/prj/test/to_compile_by_service_test_cmake  
cd $cmakeDir  
ls -al  
# let us check the same from Windows  
run_on_win_guest cmd /C dir 

rm -rf build && mkdir -p ${cmakeDir}/build/x64 && mkdir -p ${cmakeDir}/build/x86 && mkdir -p ${cmakeDir}/build/arm

run_on_win_guest cmake /? | less  # let's check all option of cmake on windows  
cd ${cmakeDir}/build/x64 && run_on_win_guest cmake -G "Visual Studio 15 Win64" ../.. &&   run_on_win_guest cmake --build . --config Debug  
cd ${cmakeDir}/build/x86 && run_on_win_guest cmake -G "Visual Studio 15" ../.. &&   run_on_win_guest cmake --build . --config Debug  
cd ${cmakeDir}/build/arm && run_on_win_guest cmake -G "Visual Studio 15 ARM" ../.. && run_on_win_guest cmake --build . --config Debug  
cp ${cmakeDir}/build/x64/Debug/to_compile_by_service_test.exe $VBOX_TEST_DIR_ROOT/dsys/x64/cmake_to_compile_by_service_test.exe
cp ${cmakeDir}/build/x86/Debug/to_compile_by_service_test.exe $VBOX_TEST_DIR_ROOT/dsys/x86/cmake_to_compile_by_service_test.exe
cp ${cmakeDir}/build/arm/Debug/to_compile_by_service_test.exe $VBOX_TEST_DIR_ROOT/dsys/arm/cmake_to_compile_by_service_test.exe

cd $VBOX_TEST_DIR_ROOT/dsys/x64  
ls -al # same from Windows  
run_on_win_guest cmd /C dir  
run_on_win_guest dumpbin /headers cmake_to_compile_by_service_test.exe
run_on_win_guest cmake_to_compile_by_service_test.exe  
echo $?
run_on_win_guest cmake_to_compile_by_service_test.exe  1  
echo $?  
popd  
```  
  
## some usefull links  
[wiki](https://github.com/davitkalantaryan/virtual_box_to_run_commands/wiki)  
[windows installation media download](https://www.microsoft.com/en-us/software-download/windows10)  
[prepare windows virtual box](https://en.wikibooks.org/wiki/VirtualBox/Setting_up_a_Virtual_Machine/Windows)  
[windows headless VBOX](https://stackoverflow.com/questions/19017825/how-to-run-oracle-virtualbox-vbox-in-fully-background-microsoft-windows-wi)   
[share folder with host](https://help.ubuntu.com/community/VirtualBox/SharedFolders)  
[host guet communication](https://www.tecmint.com/network-between-guest-vm-and-host-virtualbox/)  
