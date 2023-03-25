//
// Created by Tanmay Vemuri_L on 25-03-2023.
//

#ifndef CONWAYSGAMEOFLIFE_GENERATION_H
#define CONWAYSGAMEOFLIFE_GENERATION_H

#include <vector>
#include <string>

class Generation {
public:
    std::vector<std::vector<int>> generation;

    Generation(int rows,int columns){
        generation = std::vector<std::vector<int>>(rows, std::vector<int>(columns));
    };

    void randomizeGeneration(int percentage);
    void evolve();
    int cellChecker(int cellRow, int cellColumn);

};

#endif //CONWAYSGAMEOFLIFE_GENERATION_H
