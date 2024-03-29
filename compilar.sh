#!/bin/bash

FILES_TO_COMPILE="Camera.cpp CameraController.cpp Cube.cpp main.cpp"

g++ -ggdb $(pkg-config --cflags glfw3) -o main $FILES_TO_COMPILE $(pkg-config --static --libs glfw3) $(pkg-config --static --libs glew)