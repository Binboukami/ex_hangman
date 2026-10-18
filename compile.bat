@echo off

if not exist "%cd%\build" (
  mkdir "%cd%\build"
)

gcc main.c -o build/main.exe

@echo Output file 'main.exe' successfully  written to ".\build"