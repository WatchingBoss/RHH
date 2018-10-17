@echo off

IF NOT EXIST ../build mkdir ..\build
pushd ..\build
cl -MT -nologo -GR- -EHa -O1 -WX -DHH_INTERNAL=1 -DHH_SLOW=1 -DHH_WIN32=1 -FC -Z7 -Fmwin32_hh.map ..\code\win32_hh.cpp  user32.lib gdi32.lib 
popd

rem -W4 -wd4201 -wd4100 wd-4189 after -WX


