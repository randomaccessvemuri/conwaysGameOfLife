//
// Created by Tanmay Vemuri on 21-03-2023.
//
#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include <random>


#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 1080

#define GRID_ROWS 500
#define GRID_COLUMNS 500

#define CELL_SIZE (SCREEN_WIDTH/GRID_ROWS)

void handleInput(){
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0){
        if(e.type == SDL_QUIT){
            exit(0);
        }
    }
}

void randomizeGeneration(std::vector<std::vector<int>> &generationIn, int percentage) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 99);
    for (int i = 0; i < GRID_COLUMNS; i++) {
        for (int j = 0; j < GRID_ROWS; j++) {
            generationIn.at(i).at(j) = dis(gen) < percentage ? 1 : 0;
        }
    }
}

int cellChecker(std::vector<std::vector<int>> &generationIn, int cellRow, int cellColumn) {
    int neighbours = 0;


    if (cellRow != 0 && cellRow != GRID_COLUMNS - 1) {
        neighbours += generationIn.at(cellRow - 1).at(cellColumn)
                      + generationIn.at(cellRow + 1).at(cellColumn);
    }

    if (cellColumn != 0 && cellColumn != GRID_ROWS - 1) {
        neighbours += generationIn.at(cellRow).at(cellColumn - 1)
                      + generationIn.at(cellRow).at(cellColumn + 1);
    }

    if (cellColumn != 0 && cellColumn != GRID_COLUMNS - 1 && cellRow != 0 && cellRow != GRID_ROWS - 1) {
        neighbours += generationIn.at(cellRow - 1).at(cellColumn - 1)
                      + generationIn.at(cellRow - 1).at(cellColumn + 1)
                      + generationIn.at(cellRow + 1).at(cellColumn - 1)
                      + generationIn.at(cellRow + 1).at(cellColumn + 1);
    }

    //if cell is alive, check if it will continue to be alive
    if ((generationIn[cellColumn][cellRow] == 1 && (neighbours == 2 || neighbours == 3)) ||
        (generationIn[cellColumn][cellRow] == 0 && neighbours == 3)) //check for reproduction
    { return 1; }
    else { return 0; }

}


void renderGeneration(std::vector<std::vector<int>> &generationIn, SDL_Renderer *inRenderer) {
    SDL_SetRenderDrawColor(inRenderer, 0, 0, 0, 255);
    SDL_RenderClear(inRenderer);

    for (int i = 0; i < GRID_COLUMNS; i++) {
        for (int j = 0; j < GRID_ROWS; j++) {
            if (generationIn.at(i).at(j) == 1) {
                SDL_Rect cell = {i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE, CELL_SIZE};
                SDL_SetRenderDrawColor(inRenderer, 255, 0, 0, 255);
                SDL_RenderFillRect(inRenderer, &cell);
            }
        }
    }

    SDL_RenderPresent(inRenderer);

}

void printGeneration(std::vector<std::vector<int>> &generationIn) {
    for (int i = 0; i < GRID_COLUMNS; i++) {
        auto currentRow = generationIn.at(i);
        for (int j = 0; j < GRID_ROWS; j++) {
            std::cout << currentRow.at(j) << " ";
        }
        std::cout << std::endl;
    }
}


int main() {
    SDL_Init(SDL_INIT_VIDEO);
    auto gWindow = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                    SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    auto gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    std::vector<std::vector<int>> generationCurrent(GRID_COLUMNS, std::vector<int>(GRID_ROWS, 0));
    std::vector<std::vector<int>> generationPrevious(GRID_COLUMNS, std::vector<int>(GRID_ROWS, 0));
    int counter = 0;

    randomizeGeneration(generationCurrent, 100);
    renderGeneration(generationCurrent, gRenderer);
    printGeneration(generationCurrent);

    generationPrevious = generationCurrent;


    while (true) {
        handleInput();

        for (int i = 0; i < GRID_COLUMNS; i++) {
            for (int j = 0; j < GRID_ROWS; j++) {
                generationCurrent.at(i).at(j) = cellChecker(generationPrevious, i, j);
            }

        }

        renderGeneration(generationCurrent, gRenderer);

        //The previous generation is finished for evaluation so current will be taken as new previous
        generationPrevious = generationCurrent;
    }


}