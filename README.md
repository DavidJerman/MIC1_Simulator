# MIC-1 Micro-Architecture Simulator

## About
This program will simulate the working of a hypothetical computer defined in the book by Andrew S. Tannenbaum, Structured Computer Organization, 3rd Edition.
It will be written in C++ and will be a graphical program, I have not decided on the GUI framework yet - it might be Qt or something more simple.
You can find the basic information about the hypothetical computer in the book, but the simulator is not limited to the computer described in the book or on the following website: https://www.tjhsst.edu/~dhyatt/arch/mic1.html.
The program is still work in progress, and I will work on the project as I have time, probably after the midterm exams in february.
For now, I have just created the repository and added the basic files.

## The plan
This is just a simple plan that I am making for myself, it is not set in stone and I might change it as I go along.
- [x] Create the repository
- [ ] Class for the memory
- [ ] Class for the registers
- [ ] Class for the ALU
- [ ] Class for the clock
- [ ] Class for the control unit
Each class should probably have a latch, which is released when the clock is high.
