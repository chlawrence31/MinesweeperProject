#include <iostream>
//#include <SFML/graphics.hpp>
#include "textures.h"
#include "board.h"
#include "tile.h"
#include "random.h"
#include <fstream>
using namespace std;

void setText(sf::Text &text, float x, float y);

int main()
{
    float width;
    float height;
    float columns;
    float rows;
    float mineCount;
    char inputtedName[9] = {0,0,0,0,0,0,0,0,0};
    int characterCount = 0;
    bool gameStarted = false;
    string storedName;
    vector<string> names;
    //Loading Variables from file
    ifstream gameFile;
    gameFile.open("files/board_config.cfg", ios_base::in);
    gameFile >> columns;
    gameFile >> rows;
    gameFile >> mineCount;
    float tileCount = rows * columns;
    width = 32 * columns;
    height = (rows * 32) + 100;
    //Welcome Window
    sf::RenderWindow welcomeWindow(sf::VideoMode(width, height), "Welcome window", sf::Style::Close);
    sf::Font font;
    font.loadFromFile("files/font.ttf");
    sf::Text welcomeText("WELCOME TO MINESWEEPER!", font);
    welcomeText.setCharacterSize(24);
    welcomeText.setStyle(sf::Text::Bold);
    welcomeText.setStyle(sf::Text::Underlined);
    welcomeText.setFillColor(sf::Color::White);
    setText(welcomeText,width/2.0f, height/2.0f - 150);
    sf::Text inputPrompt("Enter your name:", font);
    inputPrompt.setCharacterSize(20);
    inputPrompt.setStyle(sf::Text::Bold);
    inputPrompt.setFillColor(sf::Color::White);
    setText(inputPrompt,width/2.0f, height/2.0f - 75);
    sf::Text inputName;
    inputName.setString("|");
    inputName.setFont(font);
    inputName.setFillColor(sf::Color::Yellow);
    inputName.setCharacterSize(18);
    setText(inputName, width/2.0f, height/2.0f - 45);
    while(welcomeWindow.isOpen())
    {
        sf::Event event;
        while(welcomeWindow.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                welcomeWindow.close();
            }
            if(event.type == sf::Event::TextEntered)
            {
                const sf::Keyboard::Key keyEntered = event.key.code;
                if(std::isalpha((char)keyEntered) && characterCount < 10)
                {
                    inputtedName[characterCount] = char(keyEntered);
                    characterCount++;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace) && characterCount > 0)
                {
                    inputtedName[characterCount - 1] = 0;
                    characterCount--;
                }
                inputName.setString(string(inputtedName) + '|');
                setText(inputName, width/2.0f, height/2.0f - 45);
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && characterCount > 0)
                {
                    inputtedName[0] = toupper((int)inputtedName[0]);
                    for(int i = 1; i < characterCount; i++)
                    {
                        inputtedName[i] = tolower(inputtedName[i]);
                    }
                    storedName = string(inputtedName);
                    names.push_back(storedName);
                    cout << storedName << endl;
                    welcomeWindow.close();
                    gameStarted = true;
                }
            }
        }
        welcomeWindow.clear(sf::Color::Blue);
        welcomeWindow.draw(welcomeText);
        welcomeWindow.draw(inputPrompt);
        welcomeWindow.draw(inputName);
        welcomeWindow.display();
    }
    //Game window
    if(gameStarted)
    {
        sf::RenderWindow gameWindow(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close);
        Board gameBoard;
        gameBoard.loadBoard(columns,rows,gameWindow);
        gameBoard.placeMines(mineCount, rows, columns, gameBoard);
        gameBoard.assignAdjacentTiles(tileCount, rows, columns, gameBoard);
        gameBoard.assignNumbers(tileCount, rows, columns, gameBoard);
        while(gameWindow.isOpen())
        {
            sf::Event event;
            sf::Mouse mouse;
            auto coordinate = mouse.getPosition(gameWindow);
            while(gameWindow.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                {
                    gameWindow.close();
                }
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    auto debugBounds = gameBoard.debugButton.getGlobalBounds();
                    auto pauseBounds = gameBoard.pauseButton.getGlobalBounds();
                    auto faceBounds = gameBoard.happyFace.getGlobalBounds();
                    auto leaderboard = gameBoard.leaderboard.getGlobalBounds();
                    if(debugBounds.contains(coordinate.x, coordinate.y) && !gameBoard.gameLost && !gameBoard.gameWon)
                    {
                        gameBoard.debugMode(columns, rows, gameWindow);
                    }
                    if(pauseBounds.contains(coordinate.x, coordinate.y) && !gameBoard.gameLost && !gameBoard.gameWon && !gameBoard.debugPressed)
                    {
                        gameBoard.pausePressed = !gameBoard.pausePressed;
                    }
                    if(leaderboard.contains(coordinate.x, coordinate.y) && !gameBoard.gameLost && !gameBoard.gameWon && !gameBoard.debugPressed)
                    {
                        gameBoard.showLeaderboard(width, height, gameBoard);
                    }
                    if(faceBounds.contains(coordinate.x, coordinate.y))
                    {
                        for(int i = 0; i < rows; i++)
                        {
                            for(int j = 0; j < columns; j++)
                            {
                                gameBoard.tiles.at(i).at(j).hasMine = false;
                                gameBoard.tiles.at(i).at(j).isRevealed = false;
                                gameBoard.tiles.at(i).at(j).hasFlag = false;
                                gameBoard.tiles.at(i).at(j).adjacentMines = 0;
                            }
                        }
                        gameBoard.debugPressed = false;
                        gameBoard.gameLost = false;
                        gameBoard.flagCount = 0;
                        gameBoard.gameWon = false;
                        gameBoard.loadBoard(columns, rows, gameWindow);
                        gameBoard.placeMines(mineCount, rows, columns, gameBoard);
                        gameBoard.assignNumbers(tileCount, rows, columns, gameBoard);
                    }
                    if(coordinate.x < (columns * 32 - 1) && coordinate.y < rows * 32 -1 && !gameBoard.gameWon)
                    {
                        gameBoard.revealTile(coordinate.y, coordinate.x, tileCount, columns, rows, gameBoard, gameWindow);
                    }
                }
                if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && !gameBoard.gameLost && !gameBoard.debugPressed && !gameBoard.gameWon)
                {
                    gameBoard.flagTile(coordinate.y, coordinate.x, tileCount, gameBoard, gameWindow);
                }
            }
            gameWindow.clear(sf::Color::White);
            gameBoard.loadButtons(columns, rows, gameWindow);
            gameBoard.mineCounter(mineCount, rows, columns, gameBoard.flagCount, gameBoard, gameWindow);
            gameBoard.checkWin(tileCount, rows, columns, mineCount, gameBoard, gameWindow);
            gameBoard.drawBoard(columns, rows, gameBoard, gameWindow);
            gameWindow.display();
        }
    }
    return 0;
}

void setText(sf::Text &text, float x, float y)
{
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}