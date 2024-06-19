@echo off
g++ -o %1 %1.cpp glad.c stb_image.cpp -lglfw3 -lopengl32
%1