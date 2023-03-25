//
// Created by Tanmay Vemuri_L on 25-03-2023.
//
#include "generation.h"
#include <random>
#include <opencv2/opencv.hpp>
#include <omp.h>

void Generation::randomizeGeneration(int percentage) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 99);
    for (auto & i : generation) {
        for (int j = 0; j < generation.at(1).size(); j++) {
            i.at(j) = dis(gen) <= percentage ? 1 : 0;
        }
    }
}

int Generation::cellChecker(int cellRow, int cellColumn) {
    int neighbours = 0;

    for (int i = cellRow-1; i <= cellRow+1; i++) {
        for (int j = cellColumn-1; j <= cellColumn+1; j++) {
            if (i >= 0 && i < generation.size() && j >= 0 && j < generation[0].size() && !(i == cellRow && j == cellColumn)) {
                neighbours += generation[i][j];
            }
        }
    }

    if ((generation[cellRow][cellColumn] == 1 && (neighbours == 2 || neighbours == 3)) || (generation[cellRow][cellColumn] == 0 && neighbours == 3)) {
        return 1;
    } else {
        return 0;
    }
}

void Generation::evolve() {
    auto newGeneration = generation;

#pragma omp parallel for default(none) shared(newGeneration) schedule(static)
    for (int i = 0; i < generation.size(); i++) {
        for (int j = 0; j < generation.at(1).size(); j++) {
            newGeneration.at(i).at(j) = cellChecker(i,j);
        }
    }
    generation = newGeneration;
}