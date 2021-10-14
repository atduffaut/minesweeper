#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include "Board.h"
#include "Tile.h"
#include "TextMan.h"
#include "Random.h"
using namespace std;



int numAdjacent(vector<Tile*> adjacent) {
    int count = 0;
    for (int i = 0; i < adjacent.size(); i++) {
        if (adjacent[i]->mine) {
            count++;
        }
    }
    return count;
}

void Reveal(Tile* selection) {
    if (selection->number == 0 && !selection->mine) {
        for (int i = 0; i < selection->adjacent.size(); i++) {
            if (!selection->adjacent[i]->mine && !selection->adjacent[i]->flag) {
                selection->adjacent[i]->revealed = true;
            }
        }
    }
    for (int i = 0; i < selection->adjacent.size(); i++) {
        if (selection->adjacent[i]->number == 0 && !selection->adjacent[i]->center && !selection->adjacent[i]->flag) {
            selection->adjacent[i]->center = true;
            Reveal(selection->adjacent[i]);
        }
    }
}



int main()
{
    //Read data from config.cfg
    ifstream inFile("boards/config.cfg");
    string temp;
    int collumns;
    int rows;
    int mines;
    int leftClickCount = 0;
    int rightClickCount = 0;
    int mineCount = 0;
    int digit;
    int tens;
    bool negative = false;
    bool win = false;
    bool lose = false;
    bool debugOn = false;
    bool clickable = true;
    bool randomized = false;
    bool mineOn = false;
    getline(inFile, temp);
    Board board = Board();
    Tile tile = Tile();
    vector<Tile> tiles;
    collumns = stoi(temp);
    getline(inFile, temp);
    rows = stoi(temp);
    getline(inFile, temp);
    mines = stoi(temp);
    inFile.close();

    //set board values
    board.SetWidth(collumns);
    board.SetHeight(rows);
    board.SetMines(mines);
    board.SetTiles(collumns, rows);


    //this is the window in the correct size of whatever the config.cfg file would be
    sf::RenderWindow window(sf::VideoMode(board.GetWidth(), board.GetHeight()), "Minesweeper");

    //now we need to create the sprites for all the things we need to draw
    sf::Sprite tile_hidden(TextMan::GetTexture("tile_hidden"));
    sf::Sprite tile_revealed(TextMan::GetTexture("tile_revealed"));
    sf::Sprite flag(TextMan::GetTexture("flag"));
    sf::Sprite mine(TextMan::GetTexture("mine"));
    sf::Sprite debug(TextMan::GetTexture("debug"));
    sf::Sprite face_happy(TextMan::GetTexture("face_happy"));
    sf::Sprite face_lose(TextMan::GetTexture("face_lose"));
    sf::Sprite face_win(TextMan::GetTexture("face_win"));
    sf::Sprite number_1(TextMan::GetTexture("number_1"));
    sf::Sprite number_2(TextMan::GetTexture("number_2"));
    sf::Sprite number_3(TextMan::GetTexture("number_3"));
    sf::Sprite number_4(TextMan::GetTexture("number_4"));
    sf::Sprite number_5(TextMan::GetTexture("number_5"));
    sf::Sprite number_6(TextMan::GetTexture("number_6"));
    sf::Sprite number_7(TextMan::GetTexture("number_7"));
    sf::Sprite number_8(TextMan::GetTexture("number_8"));
    sf::Sprite test_1(TextMan::GetTexture("test_1"));
    sf::Sprite test_2(TextMan::GetTexture("test_2"));
    sf::Sprite test_3(TextMan::GetTexture("test_3"));
    sf::Sprite digits(TextMan::GetTexture("digits"));
    // the digits sprite cannot be drawn as is, it needs to be manipulated to show the desired digits





    //this is used for making a vector of all the tiles
    for (int i = 0; i < collumns; i++) {
        for (int j = 0; j < rows; j++) {
            tiles.push_back(tile);
        }
    }

    //we need to create a randomized assortment of mines among the tiles


    //need to determine the amount of bombs around each tile now
    //this uses adjacent tile vector to store the pointers

    for (int i = 0; i < tiles.size(); i++) {
        if (i == 0) {
            tiles[i].adjacent.push_back(&tiles[i + 1]);
            tiles[i].adjacent.push_back(&tiles[i + rows]);
            tiles[i].adjacent.push_back(&tiles[i + rows + 1]);
        }
        else if (i == rows - 1) {
            tiles[i].adjacent.push_back(&tiles[i - 1]);
            tiles[i].adjacent.push_back(&tiles[i + rows]);
            tiles[i].adjacent.push_back(&tiles[i + rows - 1]);
        }
        else if (i == (collumns - 1) * rows) {
            tiles[i].adjacent.push_back(&tiles[i + 1]);
            tiles[i].adjacent.push_back(&tiles[i - rows]);
            tiles[i].adjacent.push_back(&tiles[i - rows + 1]);
        }
        else if (i == rows * collumns - 1) {
            tiles[i].adjacent.push_back(&tiles[i - 1]);
            tiles[i].adjacent.push_back(&tiles[i - rows]);
            tiles[i].adjacent.push_back(&tiles[i - rows - 1]);
        }
        else if (i / rows == 0) {
            tiles[i].adjacent.push_back(&tiles[i + 1]);
            tiles[i].adjacent.push_back(&tiles[i + rows]);
            tiles[i].adjacent.push_back(&tiles[i + rows + 1]);
            tiles[i].adjacent.push_back(&tiles[i - 1]);
            tiles[i].adjacent.push_back(&tiles[i + rows - 1]);
        }
        else if (i % rows == 0) {
            tiles[i].adjacent.push_back(&tiles[i + 1]);
            tiles[i].adjacent.push_back(&tiles[i + rows]);
            tiles[i].adjacent.push_back(&tiles[i + rows + 1]);
            tiles[i].adjacent.push_back(&tiles[i - rows]);
            tiles[i].adjacent.push_back(&tiles[i - rows + 1]);
        }
        else if (i % rows == rows - 1) {
            tiles[i].adjacent.push_back(&tiles[i - 1]);
            tiles[i].adjacent.push_back(&tiles[i - rows]);
            tiles[i].adjacent.push_back(&tiles[i - rows - 1]);
            tiles[i].adjacent.push_back(&tiles[i + rows]);
            tiles[i].adjacent.push_back(&tiles[i + rows - 1]);
        }
        else if (i / rows == collumns - 1) {
            tiles[i].adjacent.push_back(&tiles[i - 1]);
            tiles[i].adjacent.push_back(&tiles[i + 1]);
            tiles[i].adjacent.push_back(&tiles[i - rows]);
            tiles[i].adjacent.push_back(&tiles[i - rows - 1]);
            tiles[i].adjacent.push_back(&tiles[i - rows + 1]);
        }
        else {
            tiles[i].adjacent.push_back(&tiles[i + 1]);
            tiles[i].adjacent.push_back(&tiles[i - 1]);
            tiles[i].adjacent.push_back(&tiles[i + rows]);
            tiles[i].adjacent.push_back(&tiles[i - rows]);
            tiles[i].adjacent.push_back(&tiles[i + rows - 1]);
            tiles[i].adjacent.push_back(&tiles[i + rows + 1]);
            tiles[i].adjacent.push_back(&tiles[i - rows - 1]);
            tiles[i].adjacent.push_back(&tiles[i - rows + 1]);
        }
    }




    //load the three test boards to be used
    string line;



    while (window.isOpen()) {
        sf::Event event;
        digit = mines - rightClickCount;
        if (digit < 0) {
            negative = true;
        }
        else {
            negative = false;
        }
        leftClickCount = 0;

        //randomize the board once
        while (mineCount != mines && !randomized) {
            int rand = Random::Number(0, collumns * rows - 1);
            if (!tiles[rand].mine) {
                tiles[rand].mine = true;
                mineCount++;
            }
        }
        randomized = true;

        //find the number of each tile that doesn't have a mine
        for (int i = 0; i < tiles.size(); i++) {
            if (!tiles[i].mine) {
                tiles[i].number = numAdjacent(tiles[i].adjacent);
            }
        }


        //this whole for loop is for drawing stuff to the board
        for (int i = 0; i < collumns; i++) {
            for (int j = 0; j < rows; j++) {
                if (!tiles[rows * i + j].revealed) {
                    tile_hidden.setPosition(i * 32, j * 32);
                    window.draw(tile_hidden);

                }
                if (tiles[rows * i + j].flag) {
                    flag.setPosition(i * 32, j * 32);
                    window.draw(flag);
                }
                if (tiles[rows * i + j].revealed) {
                    tile_revealed.setPosition(i * 32, j * 32);
                    window.draw(tile_revealed);
                }
                if (tiles[rows * i + j].mine && debugOn || mineOn) {
                    mine.setPosition(i * 32, j * 32);
                    window.draw(mine);
                }
                if (!tiles[rows * i + j].mine && tiles[rows * i + j].number != 0 && tiles[rows * i + j].revealed) {
                    if (tiles[rows * i + j].number == 1) {
                        number_1.setPosition(i * 32, j * 32);
                        window.draw(number_1);
                    }
                    else if (tiles[rows * i + j].number == 2) {
                        number_2.setPosition(i * 32, j * 32);
                        window.draw(number_2);
                    }
                    else if (tiles[rows * i + j].number == 3) {
                        number_3.setPosition(i * 32, j * 32);
                        window.draw(number_3);
                    }
                    else if (tiles[rows * i + j].number == 4) {
                        number_4.setPosition(i * 32, j * 32);
                        window.draw(number_4);
                    }
                    else if (tiles[rows * i + j].number == 5) {
                        number_5.setPosition(i * 32, j * 32);
                        window.draw(number_5);
                    }
                    else if (tiles[rows * i + j].number == 6) {
                        number_6.setPosition(i * 32, j * 32);
                        window.draw(number_6);
                    }
                    else if (tiles[rows * i + j].number == 7) {
                        number_7.setPosition(i * 32, j * 32);
                        window.draw(number_7);
                    }
                    else if (tiles[rows * i + j].number == 8) {
                        number_8.setPosition(i * 32, j * 32);
                        window.draw(number_8);
                    }
                }
                if (!win && !lose) {
                    face_happy.setPosition(collumns * 16 - 32, rows * 32);
                    window.draw(face_happy);
                }
                if (win) {
                    face_win.setPosition(collumns * 16 - 32, rows * 32);
                    window.draw(face_win);
                }
                if (lose) {
                    face_lose.setPosition(collumns * 16 - 32, rows * 32);
                    window.draw(face_lose);
                }
                debug.setPosition(collumns * 16 + 96, rows * 32);
                window.draw(debug);
                test_1.setPosition(collumns * 16 + 160, rows * 32);
                window.draw(test_1);
                test_2.setPosition(collumns * 16 + 224, rows * 32);
                window.draw(test_2);
                test_3.setPosition(collumns * 16 + 288, rows * 32);
                window.draw(test_3);

                //here I will draw the correct mine counter sprite to the board
                if (!negative) {
                    digits.setTextureRect(sf::IntRect(0, 0, 21, 32));
                    digits.setPosition(0, rows * 32);
                    window.draw(digits);
                    digits.setTextureRect(sf::IntRect(21 * (digit / 100), 0, 21, 32));
                    digits.setPosition(21, rows * 32);
                    window.draw(digits);
                    tens = digit % 100;
                    digits.setTextureRect(sf::IntRect(21 * (tens / 10), 0, 21, 32));
                    digits.setPosition(42, rows * 32);
                    window.draw(digits);
                    digits.setTextureRect(sf::IntRect(21 * (tens % 10), 0, 21, 32));
                    digits.setPosition(63, rows * 32);
                    window.draw(digits);
                }
                else {
                    digits.setTextureRect(sf::IntRect(21 * 10, 0, 21, 32));
                    digits.setPosition(0, rows * 32);
                    window.draw(digits);
                    digits.setTextureRect(sf::IntRect(21 * (-1) * (digit / 100), 0, 21, 32));
                    digits.setPosition(21, rows * 32);
                    window.draw(digits);
                    tens = digit % 100;
                    digits.setTextureRect(sf::IntRect(21 * (-1) * (tens / 10), 0, 21, 32));
                    digits.setPosition(42, rows * 32);
                    window.draw(digits);
                    digits.setTextureRect(sf::IntRect(21 * (-1) * (tens % 10), 0, 21, 32));
                    digits.setPosition(63, rows * 32);
                    window.draw(digits);
                }
            }
        }



        //this while loop handles all mouse events
        while (window.pollEvent(event)) {

            //this will close the window if the red x is selected
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                //this is where we should place a flag in the center of a tile
                if (event.mouseButton.button == sf::Mouse::Right) {
                    int mouseCollumn = event.mouseButton.x / 32;
                    int mouseRow = event.mouseButton.y / 32;
                    if (clickable && tiles[rows * mouseCollumn + mouseRow].flag) {
                        tiles[rows * mouseCollumn + mouseRow].flag = false;
                        rightClickCount--;
                    }
                    else if (clickable && mouseRow < rows && !tiles[rows * mouseCollumn + mouseRow].revealed) {
                        rightClickCount++;
                        tiles[rows * mouseCollumn + mouseRow].flag = true;
                    }
                }
                //this is where we should reveal the hidden tile (sets tile to revealed)
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int mouseCollumn = event.mouseButton.x / 32;
                    int mouseRow = event.mouseButton.y / 32;
                    if (clickable && mouseRow < rows && !tiles[rows * mouseCollumn + mouseRow].flag && !tiles[rows * mouseCollumn + mouseRow].revealed) {

                        tiles[rows * mouseCollumn + mouseRow].revealed = true;
                        tiles[rows * mouseCollumn + mouseRow].center = true;

                        //if the number is 0, we want to check all the adjacent tiles and see what their number would be as well
                        if (tiles[rows * mouseCollumn + mouseRow].number == 0) {
                            Reveal(&tiles[rows * mouseCollumn + mouseRow]);
                        }

                        //make sure to keep the correct count of leftClickCount
                        for (int i = 0; i < tiles.size(); i++) {
                            if (tiles[i].revealed) {
                                leftClickCount++;
                            }
                        }
                    }
                    //work on losing condition here
                    if (tiles[rows * mouseCollumn + mouseRow].revealed && tiles[rows * mouseCollumn + mouseRow].mine) {
                        //this means the game is lost because you clicked on a mine
                        clickable = false;
                        mineOn = true;
                        lose = true;
                        for (int i = 0; i < tiles.size(); i++) {
                            if (tiles[i].mine) {
                                tiles[i].revealed = true;

                            }
                        }
                    }

                    //work on winning condition here
                    if (board.GetTiles() - leftClickCount == mines) {
                        win = true;
                        clickable = false;

                        for (int i = 0; i < tiles.size(); i++) {
                            if (tiles[i].mine && !tiles[i].flag) {
                                tiles[i].flag = true;
                                rightClickCount++;
                            }
                        }
                    }



                    //this loads test boards 1,2, and 3 depending on where the mouse is clicked
                    if (event.mouseButton.x > collumns * 16 + 160 && event.mouseButton.x < collumns * 16 + 224 && event.mouseButton.y > rows * 32 && event.mouseButton.y < rows * 32 + 64) {

                        randomized = true;
                        clickable = true;
                        win = false;
                        lose = false;
                        negative = false;
                        leftClickCount = 0;
                        rightClickCount = 0;
                        mineCount = 0;
                        mines = 0;

                        for (int i = 0; i < tiles.size(); i++) {
                            tiles[i].mine = false;
                            tiles[i].revealed = false;
                            tiles[i].flag = false;
                            tiles[i].number = 0;
                            tiles[i].center = false;
                        }

                        inFile.open("boards/testboard1.brd");
                        for (int i = 0; i < rows; i++) {
                            getline(inFile, line);
                            for (int j = 0; j < line.size(); j++) {
                                if (line.at(j) == '1') {
                                    tiles[rows * j + i].mine = true;
                                    mines++;
                                }
                            }
                        }
                        inFile.close();
                    }
                    if (event.mouseButton.x > collumns * 16 + 224 && event.mouseButton.x < collumns * 16 + 288 && event.mouseButton.y > rows * 32 && event.mouseButton.y < rows * 32 + 64) {
                        randomized = true;
                        clickable = true;
                        win = false;
                        lose = false;
                        negative = false;
                        leftClickCount = 0;
                        rightClickCount = 0;
                        mineCount = 0;
                        mines = 0;

                        for (int i = 0; i < tiles.size(); i++) {
                            tiles[i].mine = false;
                            tiles[i].revealed = false;
                            tiles[i].flag = false;
                            tiles[i].number = 0;
                            tiles[i].center = false;
                        }

                        inFile.open("boards/testboard2.brd");
                        for (int i = 0; i < rows; i++) {
                            getline(inFile, line);
                            for (int j = 0; j < line.size(); j++) {
                                if (line.at(j) == '1') {
                                    tiles[rows * j + i].mine = true;
                                    mines++;
                                }
                            }
                        }
                        inFile.close();
                    }
                    if (event.mouseButton.x > collumns * 16 + 288 && event.mouseButton.x < collumns * 16 + 352 && event.mouseButton.y > rows * 32 && event.mouseButton.y < rows * 32 + 64) {
                        randomized = true;
                        clickable = true;
                        win = false;
                        lose = false;
                        negative = false;
                        leftClickCount = 0;
                        rightClickCount = 0;
                        mineCount = 0;
                        mines = 0;

                        for (int i = 0; i < tiles.size(); i++) {
                            tiles[i].mine = false;
                            tiles[i].revealed = false;
                            tiles[i].flag = false;
                            tiles[i].number = 0;
                            tiles[i].center = false;
                        }

                        inFile.open("boards/testboard3.brd");
                        for (int i = 0; i < rows; i++) {
                            getline(inFile, line);
                            for (int j = 0; j < line.size(); j++) {
                                if (line.at(j) == '1') {
                                    tiles[rows * j + i].mine = true;
                                    mines++;
                                }
                            }
                        }
                        inFile.close();
                    }
                    //reveal all the mines if debug is selected
                    if (clickable && event.mouseButton.x > collumns * 16 + 96 && event.mouseButton.x < collumns * 16 + 160 && event.mouseButton.y > rows * 32 && event.mouseButton.y < rows * 32 + 64) {
                        if (!debugOn) {
                            debugOn = true;
                        }
                        else if (debugOn) {
                            debugOn = false;
                        }
                    }

                    //reset the game by clicking middle button
                    if (event.mouseButton.x > collumns * 16 - 32 && event.mouseButton.x < collumns * 16 + 32 && event.mouseButton.y > rows * 32 && event.mouseButton.y < rows * 32 + 64) {
                        randomized = false;
                        clickable = true;
                        win = false;
                        lose = false;
                        negative = false;
                        leftClickCount = 0;
                        rightClickCount = 0;
                        mineCount = 0;
                        mines = board.GetMines();

                        for (int i = 0; i < tiles.size(); i++) {
                            tiles[i].mine = false;
                            tiles[i].revealed = false;
                            tiles[i].flag = false;
                            tiles[i].number = 0;
                            tiles[i].center = false;
                        }
                    }
                }
            }
        }



        window.display();
    }







    TextMan::Clear();
}