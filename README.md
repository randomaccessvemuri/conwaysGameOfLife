# Conways Game of Life:

The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970. It is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves. It is Turing complete and can simulate a universal constructor or any other Turing machine.
A CUDA implementation of Conways game of life


To view a demo, compile using CMake and then run the output binary with the following arguments (as an example):

 ```shell
 conwayGOL --rows 250 --columns 250 --screenWidth 1080 --screenHeight 1080 --percentage 10
 ```

That will give something like this:

![Demo]("./resources/example.gif")
