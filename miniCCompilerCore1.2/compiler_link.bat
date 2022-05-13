@echo off
cd ..\
E:
cd E:\masm32\tmp
del tmp.*
copy /y "%~d0%~p0\analysis\object.asm" tmp.asm
build_1.bat "%~d0%~p0\analysis\miniC.exe"
echo 生成可执行文件
pause
