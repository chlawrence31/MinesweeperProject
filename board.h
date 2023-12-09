//
// Created by chlaw on 4/12/2023.
//

#pragma once
//#include <SFML/Graphics.hpp>
#include <string>
#include <chrono>
#include <vector>
#include <cmath>
#include <iostream>
#include "tile.h"
#include "textures.h"
#include "random.h"
#include <fstream>
using namespace std;

class Board
{
public:
    sf::Sprite debugButton;
    sf::Sprite pauseButton;
    sf::Sprite happyFace;
    sf::Sprite leaderboard;
    bool debugPressed = false;
    bool pausePressed = false;
    bool gameWon = false;
    bool gameLost = false;
    int flagCount;
    vector<vector<Tile>> tiles;
    void loadSprite(float tilePositionX, float tilePositionY, Tile tempTile, sf::RenderWindow &window);
    void loadButtons(float columns, float rows, sf::RenderWindow &window);
    void loadBoard(float columns, float rows, sf::RenderWindow &window);
    void drawBoard(float columns, float rows, Board &gameBoard, sf::RenderWindow &window);
    void runTimer(int rows, int columns, int time, Board &gameBoard, sf::RenderWindow &window);
    void mineCounter(int mineCount, int rows, int columns, int flagCount, Board &gameBoard, sf::RenderWindow &window);
    void placeMines(int mineCount, int rows, int columns, Board &gameBoard);
    void debugMode(float columns, float rows, sf::RenderWindow &window);
    void revealTile(int positionX, int positionY, int tileCount, int columns, int rows, Board &gameBoard, sf::RenderWindow &window);
    void assignAdjacentTiles(int tileCount, int rows, int columns, Board &gameBoard);
    void flagTile(int positonX, int positionY, int tileCount, Board &gameBoard, sf::RenderWindow &window);
    void assignNumbers(int tileCount, int rows, int columns, Board &gameBoard);
    void checkWin(int tileCount, int rows, int columns, int mineCount, Board &gameBoard, sf::RenderWindow &window);
    void recursiveRevealTile(Tile &tile);
    void showLeaderboard(int width, int height, Board &gameBoard);
    void setText(sf::Text &text, float x, float y);
};