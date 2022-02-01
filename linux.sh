#!/bin/bash

clear

# If the glfw library hasn't been built
if [ ! -f "vendor/glfw/src/libglfw3.a" ]
then
	cd vendor/glfw
	cmake .
	make
	cd ../../
fi

gcc \
-g -Wall \
-Ivendor/glfw/include -Ivendor/glad/include -Ivendor \
src/*.c src/*/*.c vendor/glad/src/glad.c vendor/tidwall/hashmap.c vendor/glfw/src/libglfw3.a \
-lm -ldl -lpthread -lGL

./a.out