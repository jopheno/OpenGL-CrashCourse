@echo off
pushd %~dp0\..\..\
call vendor\premake5\bin\premake5.exe vs2019
popd
PAUSE