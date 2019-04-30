::===============================================================================
:: @brief    Set up a clean environment according to buildtools configuration
:: Copyright (c) 2018 Huawei Technologies Co. Ltd
::===============================================================================
@ECHO OFF

CALL :ABSPATH %BUILDTOOLS%

SET PATH=
FOR /F "tokens=1" %%P IN (%BUILDENV%\PYTHONPATH) ^
DO CALL :ADDPATH %%P || EXIT /B 1
SET PYTHONPATH=%PATH%

SET PATH=
FOR /F "tokens=1" %%P IN (%BUILDENV%\PATH) ^
DO CALL :ADDPATH %%P || EXIT /B 1

FOR /F "tokens=1* delims==" %%A IN ('SET') DO CALL :CLEARVAR %%A %BUILDENV%\inheritvars

ECHO ENV:
SET
ECHO EXECUTING: %*

%*

EXIT /B %ERRORLEVEL%

:ABSPATH
    SET BUILDTOOLS=%~dpfn1
    EXIT /B

:ADDPATH
    SET TOOL=%1
    IF "%TOOL:~0,1%" == "#" (
        EXIT /B
    )
    IF NOT EXIST "%BUILDTOOLS%\%TOOL%" (
        ECHO ERROR: %~nf0: missing tool path "%BUILDTOOLS%\%TOOL%"
        ECHO Update the tools at %BUILDTOOLS%.
        EXIT /B 1
    )
    IF "%PATH%" NEQ "" SET PATH=%PATH%;
    SET PATH=%PATH%%BUILDTOOLS%\%TOOL%
    EXIT /B

:CLEARVAR
    FOR /F "tokens=1" %%P IN (%2) DO IF /I "%1" == "%%P" EXIT /B
    SET %1=
