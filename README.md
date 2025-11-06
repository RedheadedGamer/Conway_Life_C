# Conway_Life_C
Conways game of life in C

## Project details
This is a c program that emulates a [Conways Game of life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) simulation in terminal based on user "drawn" input. It is written for unix systems only as the c libraries only allow that. There is very little error catching at the moment however this will be fixed in future versions and it is planned to make this work on windows systems as well.

## Usage
### Makefile
This project makes use of a Makefile so these tqo commands are implemented hopwever it is still very simple:
```
make
```
^ if done in **src** directory it builds the executable to **build** directory
```
make clean
```
just cleans the build directory.

### Running
```
build/life
```
Running the executable without arguments makes a board of size 8*x*8
```
build/life y x
```
Running the executable with two arguments makes a board of size y*x*x

## Evidence:


https://github.com/user-attachments/assets/f2082320-9770-4e32-bcca-78d2ccc2a43b

