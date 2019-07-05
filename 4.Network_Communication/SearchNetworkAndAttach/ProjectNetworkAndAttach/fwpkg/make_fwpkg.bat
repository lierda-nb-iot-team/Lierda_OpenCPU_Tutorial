
@echo off
echo Lierda Science Technology Group Co.,Ltd
echo nbiot_support@lierda.com


set p1=%cd%
cd ..
set p=%cd%

del /f %p1%\fwpkg_new\DEMO_new.fwpkg


rem is x86 or x64?
if /i %PROCESSOR_IDENTIFIER:~0,3%==x86 (
set p2=C:\Program Files\Neul\UpdatePackage
) else (
set p2="C:\Program Files (x86)\Neul\UpdatePackage"
)

cd /d %p2%
@echo on
UpdatePackage.exe UpdateApplicationA -f -m %p%\build_scons\arm\Hi2115\reference\application_core\manifest.txt --in %p1%\SourceFirmware.fwpkg -o %p1%\fwpkg_new\DEMO_new.fwpkg
@echo off
echo.
echo 固件打包完成
pause
exit

