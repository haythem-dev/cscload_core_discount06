@echo off

set ext_dir=%CD%\..\ext

rmdir %ext_dir%\pplib\include\pplib
mklink /J %ext_dir%\pplib\include\pplib %ext_dir%\pplib\include
