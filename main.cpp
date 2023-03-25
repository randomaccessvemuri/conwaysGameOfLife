//
// Created by Tanmay Vemuri on 21-03-2023.
//
#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include "generation.h"
#include <boost/program_options.hpp>


void handleInput() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            exit(0);
        }
    }
}

void renderGeneration(std::vector<std::vector<int>> *generationIn, int rows, int cols, SDL_Renderer *inRenderer ) {
    SDL_SetRenderDrawColor(inRenderer, 0, 0, 0, 255);
    SDL_RenderClear(inRenderer);

    int screenWidth, screenHeight;
    SDL_GetRendererOutputSize(inRenderer, &screenWidth, &screenHeight);

    int cellSize = screenHeight / rows;

    //INTERCHANGED HERE
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (generationIn->at(i).at(j) == 1) {
                SDL_Rect cell = {i * cellSize, j * cellSize, cellSize, cellSize};
                SDL_SetRenderDrawColor(inRenderer, 255, 255, 255, 255);
                SDL_RenderFillRect(inRenderer, &cell);
            }
        }
    }

    SDL_RenderPresent(inRenderer);

}

void printGeneration(std::vector<std::vector<int>> &generationIn, int rows, int columns) {
    for (int i = 0; i < columns; i++) {
        auto currentRow = generationIn.at(i);
        for (int j = 0; j < rows; j++) {
            std::cout << currentRow.at(j) << " ";
        }
        std::cout << std::endl;
    }
}


int main(int argc, char *argv[]) {
    namespace po = boost::program_options;

    int gridRows, gridColumns, screenWidth, screenHeight;
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("rows", po::value<int>(&gridRows)->default_value(100), "set number of rows")
            ("columns", po::value<int>(&gridColumns)->default_value(100), "set number of columns")
            ("screenWidth", po::value<int>(&screenWidth)->default_value(1000), "set screen width")
            ("screenHeight", po::value<int>(&screenHeight)->default_value(1000), "set screen height");


    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }


    SDL_Init(SDL_INIT_VIDEO);
    auto gWindow = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth,
                                    screenHeight, SDL_WINDOW_SHOWN);
    auto gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    Generation generation(gridRows, gridColumns);
    int counter = 0;

    generation.randomizeGeneration(15);


    while (true) {
        handleInput();
        //printGeneration(generation.generation, gridRows, gridColumns);
        renderGeneration(&generation.generation, gridRows, gridColumns, gRenderer);
        generation.evolve();
        std::cout << "Generation Number: " <<counter << std::endl;
        counter++;
    }


}