//
// Created by Tanmay Vemuri on 21-03-2023.
//
#include <vector>

#define GRID_COLUMNS 100
#define GRID_ROWS 100

bool cellChecker(std::vector <std::vector<bool>> &generationIn, cellRow, cellColumn) {
    int neighbours = generationIn[cellColumn + 1][cellRow] //right
                     + generationIn[cellColumn + 1][cellRow + 1] //top right
                     + generationIn[cellColumn + 1][cellRow - 1] //bottom right
                     + generationIn[cellColumn - 1][cellRow] //left
                     + generationIn[cellColumn - 1][cellRow + 1] //top left
                     + generationIn[cellColumn - 1][cellRow - 1] //bottom left
                     + generationIn[cellColumn][cellRow + 1] //above
                     + generationIn[cellColumn][cellRow - 1]; //below

    //Underpopuation      Overpopulation
    if (neighbours < 2 || neighbours > 3 || ) {
        return false;
    }

}


int main() {
    std::vector <std::vector<bool>> generationCurrent;
    std::vector <std::vector<bool>> generationPrevious;

    while (true) {
        for (int i = 0; i < GRID_COLUMNS; i++) {
            for (int j = 0; j < GRID_ROWS) {

            }
        }
    }


}