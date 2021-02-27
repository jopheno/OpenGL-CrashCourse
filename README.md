# README #

This will be an OpenGL CrashCourse that should cover from setting up the environment on Windows and MacOS using premake, all the way to rendering imported 3D models with textures with features like shadow mapping and skybox. This repository will be pretty much based on Ben Cook's tutorial that can be found in [here](https://www.udemy.com/course/graphics-with-modern-opengl/). Another really useful *OpenGL* tutorial is avaiable for free at *[The Cherno](https://www.youtube.com/channel/UCQ-W1KE9EYfdxhL6S4twUNw)*'s youtube channel. This repository will also be using [Conventional Commits 1.0.0](https://www.conventionalcommits.org/en/v1.0.0/) as its set of rules.

### How to setup? ###

* On Windows

Be sure to have Visual Studio 2019 installed and with C++ development selected.
Inside scripts folder, and Windows folder there is a *.bat* script that once executed will generate the visual studio project automagically.

* On MacOS

Be sure to have Xcode 11.X or later installed.
Using [Homebrew](https://brew.sh/) or any other repository manager, you need to install premake, just make sure you are installing the latest **v5**.
You can manually download it from [here](https://premake.github.io) and place it's binary inside your **/usr/local/bin** directory.

On the root folder of the project, you may now execute *premake5 xcode4* to generate Xcode project.

* How to clean generated projects files

You can clean all the configuration and builds using *premake5 clean* command, or using the accordingly script at scripts folder.
