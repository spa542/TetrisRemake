# Tetris Remake
# Author: Ryan Rosiak
<br /> <br />
## Project Description
This project is an attempt to re-create the famous block game Tetris through the command line interface. There are no special graphics. This game is purely ASCII art. I hope you 
enjoy!
<br /> <br />
## Files to pay attention to:
* main.o, TetrisGame.o - These are the compilation linker files
* main - This is the executable that should be a result
<br /> <br />
## Makefile Instructions:
Type "make" without the quotes and the program will compile everything for you. Then proceed with useing ./main in order to run the program.
<br /> <br />
## Instructions for Program:
Follow the Makefile instructions above to run the program without any manual work. If not using Makefile, then you must compile the .cpp files into .o files. (g++ -c main.cpp)
Then, you must link those with a final compilation all while labeling the output file as main.\
**You must use the tag -std=c++17 within your compilation steps.**
<br /> <br />
## Current Issues:
The game currently needs a revamp of the timing library. There needs to be better multithreading added so that the automatic falling of the blocks is much more fluid. Because of 
this bug, the game can be stalled out so that the user can have inifinite time to decide where they want to go. Also, the game needs to be able to slide blocks on top of other 
blocks before they are finally locked in and placed. 
