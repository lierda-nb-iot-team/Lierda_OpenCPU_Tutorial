::===============================================================================
:: @brief    Run a command in the buildtools environment
:: Copyright (c) 2018 Huawei Technologies Co. Ltd
::===============================================================================
@ECHO OFF

IF "%BUILDTOOLS%" == "" SET BUILDTOOLS=..\buildtools

IF NOT EXIST %BUILDTOOLS% GOTO :FALLBACK

IF "%BUILDENV%" == "" SET BUILDENV=buildenv\config\default

ECHO %~0: BUILDENV=%BUILDENV% BUILDTOOLS=%BUILDTOOLS%

buildenv\setenv.cmd %*

EXIT /B %ERRORLEVEL%

:FALLBACK
    ECHO %~0: Buildtools not found: Falling back to local build environment.
    ECHO To use buildtools put at "%BUILDTOOLS%" or set the BUILDTOOLS environment variable to them.
    TYPE buildenv\getbuildtools.txt
    %*
    EXIT /B %ERRORLEVEL%
