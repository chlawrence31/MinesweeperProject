//
// Created by chlaw on 4/12/2023.
//

#include "board.h"

void Board::loadBoard(float columns, float rows, sf::RenderWindow &window)
{
    float tileCount = rows * columns;
    for(int j = 0; j < rows; j++)
    {
        vector<Tile> row;
        for(int h = 0; h < columns; h++)
        {
            Tile newTile(h * 32, j * 32, h, j);
            row.push_back(newTile);
        }
        tiles.push_back(row);
    }
}

void Board::loadSprite(float tilePositionX, float tilePositionY, Tile tempTile, sf::RenderWindow &window)
{
    if(tempTile.isRevealed)
    {
        sf::Sprite revealedTile;
        revealedTile.setTexture(TextureManager::GetTexture("tile_revealed"));
        revealedTile.setPosition(float(tilePositionX), float(tilePositionY));
        window.draw(revealedTile);
        if(tempTile.hasMine)
        {
            sf::Sprite mine;
            mine.setTexture(TextureManager::GetTexture("mine"));
            mine.setPosition(tilePositionX, tilePositionY);
            window.draw(mine);
        }
        else if(tempTile.adjacentMines == 1)
        {
            sf::Sprite one;
            one.setTexture(TextureManager::GetTexture("number_1"));
            one.setPosition(tilePositionX, tilePositionY);
            window.draw(one);
        }
        else if(tempTile.adjacentMines == 2)
        {
            sf::Sprite two;
            two.setTexture(TextureManager::GetTexture("number_2"));
            two.setPosition(tilePositionX, tilePositionY);
            window.draw(two);
        }
        else if(tempTile.adjacentMines == 3)
        {
            sf::Sprite three;
            three.setTexture(TextureManager::GetTexture("number_3"));
            three.setPosition(tilePositionX, tilePositionY);
            window.draw(three);
        }
        else if(tempTile.adjacentMines == 4)
        {
            sf::Sprite four;
            four.setTexture(TextureManager::GetTexture("number_4"));
            four.setPosition(tilePositionX, tilePositionY);
            window.draw(four);
        }
        else if(tempTile.adjacentMines == 5)
        {
            sf::Sprite five;
            five.setTexture(TextureManager::GetTexture("number_5"));
            five.setPosition(tilePositionX, tilePositionY);
            window.draw(five);
        }
        else if(tempTile.adjacentMines == 6)
        {
            sf::Sprite six;
            six.setTexture(TextureManager::GetTexture("number_6"));
            six.setPosition(tilePositionX, tilePositionY);
            window.draw(six);
        }
        else if(tempTile.adjacentMines == 7)
        {
            sf::Sprite seven;
            seven.setTexture(TextureManager::GetTexture("number_7"));
            seven.setPosition(tilePositionX, tilePositionY);
            window.draw(seven);
        }
        else if(tempTile.adjacentMines == 8)
        {
            sf::Sprite eight;
            eight.setTexture(TextureManager::GetTexture("number_8"));
            eight.setPosition(tilePositionX, tilePositionY);
            window.draw(eight);
        }
    }
    else if(!tempTile.isRevealed)
    {
        sf::Sprite unrevealedTile;
        unrevealedTile.setTexture(TextureManager::GetTexture("tile_hidden"));
        unrevealedTile.setPosition((float)(tilePositionX), (float)(tilePositionY));
        window.draw(unrevealedTile);
        if(tempTile.hasFlag)
        {
            sf::Sprite flag;
            flag.setTexture(TextureManager::GetTexture("flag"));
            flag.setPosition(tilePositionX,tilePositionY);
            window.draw(flag);
        }
    }
}

void Board::debugMode(float columns, float rows, sf::RenderWindow &window)
{
    if(!debugPressed)
    {
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < columns; j++)
            {
                if(tiles.at(i).at(j).hasMine)
                {
                    tiles.at(i).at(j).isRevealed = true;
                }
            }
        }
        debugPressed = true;
    }
    else if(debugPressed)
    {
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < columns; j++)
            {
                if(tiles.at(i).at(j).hasMine)
                {
                    tiles.at(i).at(j).isRevealed = false;
                }
            }
        }
        debugPressed = false;
    }
}

void Board::placeMines(int mineCount, int rows, int columns, Board &gameBoard)
{
    for(int h = 0; h < mineCount; h++)
    {
        int x = Random::Int(0, rows - 1);
        int y = Random::Int(0, columns - 1);
        if(gameBoard.tiles.at(x).at(y).hasMine)
        {
            h--;
        }
        else
        {
            gameBoard.tiles.at(x).at(y).hasMine = true;
        }
    }
}

void Board::drawBoard(float columns, float rows, Board &gameBoard, sf::RenderWindow &window)
{
    int tileCount = columns * rows;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            loadSprite(gameBoard.tiles.at(i).at(j).positionX, gameBoard.tiles.at(i).at(j).positionY, gameBoard.tiles.at(i).at(j), window);
        }
    }
}

void Board::loadButtons(float columns, float rows, sf::RenderWindow &window)
{
    if(gameLost)
    {
        sf::Sprite sadFace;
        sadFace.setTexture(TextureManager::GetTexture("face_lose"));
        sadFace.setPosition(((columns / 2.0f) * 32) - 32, 32 * ((rows) + 0.5f));
        window.draw(sadFace);
    }
    else if(gameWon)
    {
        sf::Sprite winFace;
        winFace.setTexture(TextureManager::GetTexture("face_win"));
        winFace.setPosition(((columns / 2.0f) * 32) - 32, 32 * ((rows) + 0.5f));
        window.draw(winFace);
    }
    else
    {
        happyFace.setTexture(TextureManager::GetTexture("face_happy"));
        happyFace.setPosition(((columns / 2.0f) * 32) - 32, 32 * ((rows) + 0.5f));
        window.draw(happyFace);
    }
    debugButton.setTexture(TextureManager::GetTexture("debug"));
    debugButton.setPosition(((columns) * 32) - 304, 32 * ((rows) + 0.5f));
    window.draw(debugButton);
    if(!pausePressed)
    {
        pauseButton.setTexture(TextureManager::GetTexture("pause"));
        pauseButton.setPosition(((columns) * 32) - 240, 32 * ((rows) + 0.5f));
        window.draw(pauseButton);
    }
    else if(pausePressed)
    {
        sf::Sprite playButton;
        playButton.setTexture(TextureManager::GetTexture("play"));
        playButton.setPosition(((columns) * 32) - 240, 32 * ((rows) + 0.5f));
        window.draw(playButton);
    }
    leaderboard.setTexture(TextureManager::GetTexture("leaderboard"));
    leaderboard.setPosition(((columns) * 32) - 176, 32 * ((rows) + 0.5f));
    window.draw(leaderboard);
}

void Board::revealTile(int positionX, int positionY, int tileCount, int columns, int rows, Board &gameBoard, sf::RenderWindow &window)
{
    float x = positionX / 32;
    float y = positionY / 32;
    if(!debugPressed)
    {
        if(tiles.at(x).at(y).hasMine)
        {
            gameBoard.gameLost = true;
            debugMode(columns, rows, window);
        }
        recursiveRevealTile(gameBoard.tiles.at(x).at(y));
    }
}

void Board::assignAdjacentTiles(int tileCount, int rows, int columns, Board &gameBoard)
{
    int count = 0;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            //Top Left Corner
            if(i == 0 && j == 0)
            {
                gameBoard.tiles.at(0).at(0).adjacentTiles.push_back(&gameBoard.tiles.at(i).at(j + 1));
                gameBoard.tiles.at(0).at(0).adjacentTiles.push_back(&gameBoard.tiles.at(i + 1).at(j));
                gameBoard.tiles.at(0).at(0).adjacentTiles.push_back(&gameBoard.tiles.at(i + 1).at(j + 1));
            }
            //Top Right Corner
            else if(i == 0 && j == columns - 1)
            {
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i).at(j - 1));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i + 1).at(j - 1));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i + 1).at(j));
            }
            //Bottom Left Corner
            else if(j == 0 && i == rows - 1)
            {
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i).at(j + 1));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i - 1).at(j));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i - 1).at(j + 1));
            }
            //Bottom Right Corner
            else if(i == rows - 1 && j == columns - 1)
            {
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i - 1).at(j - 1));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i - 1).at(j));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i).at(j - 1));
            }
            //Left Side
            else if(j == 0 && i != 0 && i != rows - 1)
            {
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i - 1).at(j));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i + 1).at(j));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i - 1).at(j + 1));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i).at(j + 1));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i + 1).at(j + 1));
            }
            //Right Side
            else if(j == columns - 1 && i != 0 && i != rows - 1)
            {
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i - 1).at(j - 1));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i - 1).at(j));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i).at(j - 1));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i + 1).at(j));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i + 1).at(j - 1));
            }
            //Top Row
            else if(i == 0 && j != 0 && j != columns - 1)
            {
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i ).at(j - 1));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i + 1).at(j - 1));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i + 1).at(j));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i + 1).at(j + 1));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i).at(j + 1));
            }
            //Bottom Row
            else if(i == rows - 1 && j != 0 && j != columns - 1)
            {
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i - 1).at(j - 1));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i).at(j - 1));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i - 1).at(j));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i).at(j + 1));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i - 1).at(j + 1));
            }
            else if(i != rows -1 && i != 0 && j != columns - 1 && j != 0)
            {
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i - 1).at(j + 1));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i).at(j + 1));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i + 1).at(j + 1));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i - 1).at(j));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i + 1).at(j));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i - 1).at(j - 1));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i).at(j - 1));
                gameBoard.tiles.at(i).at(j).adjacentTiles.push_back(&gameBoard.tiles.at(i + 1).at(j - 1));
            }
        }
    }
}

void Board::assignNumbers(int tileCount, int rows, int columns, Board &gameBoard)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            if(!gameBoard.tiles.at(i).at(j).hasMine)
            {
                for(int h = 0; h < gameBoard.tiles.at(i).at(j).adjacentTiles.size(); h++)
                {
                    if(gameBoard.tiles.at(i).at(j).adjacentTiles.at(h)->hasMine)
                    {
                        gameBoard.tiles.at(i).at(j).adjacentMines++;
                    }
                }
            }
        }
    }
}

void Board::flagTile(int positonX, int positionY, int tileCount, Board &gameBoard, sf::RenderWindow &window)
{
    if(!debugPressed)
    {
        float x = positonX / 32;
        float y = positionY /32;
        if(tiles.at(x).at(y).hasFlag)
        {
            tiles.at(x).at(y).hasFlag = false;
            flagCount--;
        }
        else
        {
            tiles.at(x).at(y).hasFlag = true;
            flagCount++;
        }
    }
}

void Board::mineCounter(int mineCount, int rows, int columns, int flagCount, Board &gameBoard, sf::RenderWindow &window)
{
    sf::Sprite onesDigit;
    onesDigit.setTexture(TextureManager::GetTexture("digits"));
    sf::Sprite tensDigit;
    tensDigit.setTexture(TextureManager::GetTexture("digits"));
    sf::Sprite hundredsDigit;
    hundredsDigit.setTexture(TextureManager::GetTexture("digits"));
    int ones;
    int tens;
    int hundreds;
    if(gameBoard.gameWon)
    {
        ones = 0;
        tens = 0;
        hundreds = 0;
        onesDigit.setTextureRect(sf::IntRect(21 * ones, 0, 21, 32));
        onesDigit.setPosition(54, 32 * (rows + 0.5f) + 16);
        window.draw(onesDigit);
        tensDigit.setTextureRect(sf::IntRect(21 * tens, 0, 21, 32));
        tensDigit.setPosition(33, 32 * (rows + 0.5f) + 16);
        window.draw(tensDigit);
        hundredsDigit.setTextureRect(sf::IntRect(21 * hundreds, 0, 21, 32));
        hundredsDigit.setPosition(12, 32 * (rows + 0.5f) + 16);
        window.draw(hundredsDigit);
    }
    else if(mineCount - flagCount >= 0)
    {
        ones = (mineCount  - flagCount) % 10;
        tens = (mineCount - flagCount) / 10;
        if(tens >= 10)
        {
            tens = tens % 10;
        }
        hundreds = (mineCount - flagCount) / 100;
        onesDigit.setTextureRect(sf::IntRect(21 * ones, 0, 21, 32));
        onesDigit.setPosition(54, 32 * (rows + 0.5f) + 16);
        window.draw(onesDigit);
        tensDigit.setTextureRect(sf::IntRect(21 * tens, 0, 21, 32));
        tensDigit.setPosition(33, 32 * (rows + 0.5f) + 16);
        window.draw(tensDigit);
        hundredsDigit.setTextureRect(sf::IntRect(21 * hundreds, 0, 21, 32));
        hundredsDigit.setPosition(12, 32 * (rows + 0.5f) + 16);
        window.draw(hundredsDigit);
    }
    else
    {
        ones = ((mineCount  - flagCount) % 10) * -1;
        tens = ((mineCount - flagCount) / 10) * -1;
        if(tens >= 10)
        {
            tens = tens % 10;
        }
        hundreds = 10;
        onesDigit.setTextureRect(sf::IntRect(21 * ones, 0, 21, 32));
        onesDigit.setPosition(54, 32 * (rows + 0.5f) + 16);
        window.draw(onesDigit);
        tensDigit.setTextureRect(sf::IntRect(21 * tens, 0, 21, 32));
        tensDigit.setPosition(33, 32 * (rows + 0.5f) + 16);
        window.draw(tensDigit);
        hundredsDigit.setTextureRect(sf::IntRect(21 * hundreds, 0, 21, 32));
        hundredsDigit.setPosition(12, 32 * (rows + 0.5f) + 16);
        window.draw(hundredsDigit);
    }
}

void Board::runTimer(int rows, int columns, int time, Board &gameBoard, sf::RenderWindow &window)
{
    sf::Sprite onesDigit;
    onesDigit.setTexture(TextureManager::GetTexture("digits"));
    sf::Sprite tensDigit;
    tensDigit.setTexture(TextureManager::GetTexture("digits"));
    sf::Sprite hundredsDigit;
    hundredsDigit.setTexture(TextureManager::GetTexture("digits"));
    sf::Sprite thousandsDigit;
    thousandsDigit.setTexture(TextureManager::GetTexture("digits"));
//    auto timer = chrono::steady_clock::now();
//    chrono::steady_clock::time_point gameTime;
//    chrono::steady_clock::time_point pauseTime;
//    int ones = (int)timer % 10;
//    int tens = timer / 10;
//    int hundreds = timer / 100;
//    onesDigit.setTextureRect(sf::IntRect(21 * ones, 0, 21, 32));
//    onesDigit.setPosition((columns * 32) - 54, 32 * (rows + 0.5f) + 16);
//    window.draw(onesDigit);
//    tensDigit.setTextureRect(sf::IntRect(21 * tens, 0, 21, 32));
//    tensDigit.setPosition((columns * 32) - 33, 32 * (rows + 0.5f) + 16);
//    window.draw(tensDigit);
//    hundredsDigit.setTextureRect(sf::IntRect(21 * hundreds, 0, 21, 32));
//    hundredsDigit.setPosition(12, 32 * (rows + 0.5f) + 16);
//    window.draw(hundredsDigit);
}

void Board::checkWin(int tileCount, int rows, int columns, int mineCount, Board &gameBoard, sf::RenderWindow &window)
{
    int winCount;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            if(gameBoard.tiles.at(i).at(j).isRevealed)
            {
                winCount++;
            }
        }
    }
    if(winCount == tileCount - mineCount)
    {
        gameBoard.gameWon = true;
    }
    if(gameWon)
    {

        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < columns; j++)
            {
                if(gameBoard.tiles.at(i).at(j).hasMine)
                {
                    gameBoard.tiles.at(i).at(j).hasFlag = true;
                }
            }
        }
    }
}

void Board::recursiveRevealTile(Tile &tile)
{
    if(tile.hasFlag || tile.isRevealed)
    {
        return;
    }

    tile.isRevealed = true;

    if(tile.hasMine)
    {
        return;
    }
    if(tile.adjacentMines == 0)
    {
        for(int i = 0; i < tile.adjacentTiles.size(); i++)
        {
            recursiveRevealTile(*tile.adjacentTiles.at(i));
        }
    }
}


void Board::setText(sf::Text &text, float x, float y)
{
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

void Board::showLeaderboard(int width, int height, Board &gameBoard)
{
    width = width / 2;
    height = height / 2;
    sf::RenderWindow leaderBoardWindow(sf::VideoMode(width, height), "Minesweeper", sf::Style::Close);
    sf::Font font;
    font.loadFromFile("files/font.ttf");
    sf::Text leaderboardText("LEADERBOARD", font);
    leaderboardText.setCharacterSize(20);
    leaderboardText.setFillColor(sf::Color::White);
    leaderboardText.setStyle(sf::Text::Bold);
    leaderboardText.setStyle(sf::Text::Underlined);
    setText(leaderboardText,width/2.0f, height/2.0f - 125);
    ifstream leaderboardFile;
    leaderboardFile.open("files/leaderboard.txt", ios_base::in);
    string name1;
    string time1;
    string name2;
    string time2;
    string name3;
    string time3;
    string name4;
    string time4;
    string name5;
    string time5;
    getline(leaderboardFile,time1, ',');
    getline(leaderboardFile, name1);
    getline(leaderboardFile,time2, ',');
    getline(leaderboardFile, name2);
    getline(leaderboardFile,time3, ',');
    getline(leaderboardFile, name3);
    getline(leaderboardFile,time4, ',');
    getline(leaderboardFile, name4);
    getline(leaderboardFile,time5, ',');
    getline(leaderboardFile, name5);
    string leaderBoardString = "1. " "\t" + time1 + "\t" + name1 + "\n" + "\n"
            + "2. " "\t" + time2 + "\t" + name2 + "\n" + "\n" +
            "3. " "\t" + time3 + "\t" + name3 + "\n" + "\n" +
            "4. " "\t" + time4 + "\t" + name4 + "\n" + "\n" +
            "5. " "\t" + time5 + "\t" + name5 + "\n";
    sf::Text leaderboardResults(leaderBoardString, font);
    leaderboardResults.setFillColor(sf::Color::White);
    leaderboardResults.setStyle(sf::Text::Bold);
    leaderboardResults.setCharacterSize(18);
    setText(leaderboardResults, width / 2.0f, height / 2.0f + 20);
    while(leaderBoardWindow.isOpen())
    {
        sf::Event event;
        while(leaderBoardWindow.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                leaderBoardWindow.close();
            }
        }
        leaderBoardWindow.clear(sf::Color::Blue);
        leaderBoardWindow.draw(leaderboardText);
        leaderBoardWindow.draw(leaderboardResults);
        leaderBoardWindow.display();
    }

}








