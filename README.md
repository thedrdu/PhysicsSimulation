# Physics Simulation - Circular Buffer

### Note: You are on the circular-buffer branch, which uses a slightly different implementation. Performance may vary!

This is a physics simulation written in C, where users can place circles and watch as they move under the forces of each others' gravity. Users can hold down the mouse button to increase the size of the circle to be created, and move their cursor to determine its initial velocity and direction. Once they release the mouse, the circle will then be placed.


## Prerequisites

This program will only work on UNIX-like architectures. Additionally, the program has the prerequisites of the `SDL2` and `SDL2_gfx` packages.  Make sure you have them installed on your Linux or MacOS system before attempting to build and run this program.


## Build Instructions

To build the program, run the make build command at the base level of the project. The executable will be placed in the bin folder.

`make build`


## Running the Program

To run the program, navigate to the bin folder and run the executable:

```
cd bin
./simulation
```