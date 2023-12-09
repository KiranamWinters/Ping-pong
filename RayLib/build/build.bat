@echo off



cl -I ../include -Wall ../src/main.c ../lib/raylib.lib winmm.lib opengl32.lib gdi32.lib
 
echo --------------------BUILD_COMPLETE-------------------
