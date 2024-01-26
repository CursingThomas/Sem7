Attatched is our project file where the dynamic load controller is integrated.
We have chose to include it like this, since the project otherwise is very big. You can find the main loop and implementation of the code by going to line 3500 of motion.c.

To use this code directly on your computer, there needs to be a few dependencies installed.
To find a detailed guide on how to compile and install this code, please refer to: https://motion-project.github.io/motion_build.html

There are a few notices to this project:
- The makefile is automatically integrated, this made it difficult to implement the .h and .c files. In accordance with the teacher, we put the source code in the main motion.c file.
This way the code compiles and works like it should, but it should be properly included using .c and .h files.
- The linker might throw errors based on how your system is setup. IF it does, include the -lm linker flag. This is needed for the math library.