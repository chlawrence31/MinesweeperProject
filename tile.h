#pragma once
//#include <SFML/Graphics.hpp>
#include "textures.h"
#include <string>
using namespace std;

class Tile
        {
        public:
            float positionX;
            float positionY;
            int adjacentMines = 0;
            Tile()
            {

            }
           Tile(float positionX, float positionY, float row, float column)
           {
               this->positionX = positionX;
               this->positionY = positionY;
               hasMine = false;
               isRevealed = false;
               adjacentMines = 0;
            }
            bool isRevealed = false;
            bool hasMine = false;
            bool hasFlag = false;
            vector<Tile*> adjacentTiles;
        };
