# README #

This is a project that uses OpenGL and SFML as well as the GLEW and GLM libraries. It is mainly showcasing the ability to draw a cube in 3D and be able to manipulate said cube turning it into a game
CubeSouls is a simple game where waves of cubes fly towards the player cube. The players objective is to avoid the oncoming cubes via arrow keys or A/D keys. 


### What is this repository for? ###

* Lab 11 Experiment with a Cube Texturing All Sides Textured

### How do I get set up? ###

* Clone repository
* Ensure `SFML_SDK` environment variable exits
* Ensure SFML Version SFML 2.3.2 Visual C++ 14 (2015) - 32-bit is installed 
http://www.sfml-dev.org/files/SFML-2.3.2-windows-vc14-32-bit.zip "SFML-2.3.2-windows-vc14-32-bit.zip"
* Download extensions wrangler GLEW from http://glew.sourceforge.net/index.html and obtain Binaries for  Windows 32-bit and 64-bit
	* FreeGLUT can be used as an alternative to GLEW http://freeglut.sourceforge.net 
* Set environment variable for GLEW
	* Follow this guide https://support.microsoft.com/en-us/kb/310519
	* Alternatively `SET GLEW_SDK="C:\Users\#####\glew-1.13.0-win32\glew-1.13.0"`
* To check environment variable is set correctly open a command prompt and type `echo %GLEW_SDK%` the path to glew sdk should be show.
* Download GLM Math Library from https://github.com/g-truc/glm/tags
* Set environment variable for GLM
	* Follow this guide https://support.microsoft.com/en-us/kb/310519
	* Alternatively `SET GLM_SDK="C:\Users\#####\glm-0.9.7.2\glm\glm"`
* Select a project default target `x86` when running executable
* If the project builds but does not `xcopy` the required dll's try moving your project to a directory you have full access to, see http://tinyurl.com/SFMLStarter for a guide on post build events.

### Who do I talk to? ###

* sybek96@interia.pl