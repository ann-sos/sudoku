/**
* SUDOKU
* @author ann-sos
* @purpose Class Game (together with class GameOut) makes up GUI of Sudoku game - is responsible for displaying sudoku table and allowing user to input values by clicking on the modifiable tiles and entering/deleting numbers.
* Klasa Game wyœwietla tablicê sudoku i przyjmuje input od u¿ytkownika. Klasa Game jest sk³adow¹ projektu Sudoku.
*/
#ifndef GAME_H_
#define GAME_H_ //blokada powtórnego do³¹czenia -- include guard



#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <Windows.h>
#include "gameout.h"
#include "..\..\Saving\Saving.h"
#include "..\..\SudokuTable\Project1\SudokuTable.h"
class GameOut; //deklaracja zapowiadajaca
struct Table;
class SudokuTable;



bool calling_function(std::vector < std::vector < int > > &my_array, SudokuTable& sudoku);


//Class Game constructs GUI with use of SFML library.
class Game {
    friend GameOut;
    friend std::ostream& operator<< (std::ostream& out, Table& tile);
private:
   
    
protected:
    int tile_x;
    int tile_y;
    int window_x;
    int window_y;
    int vec_size;   //Information about the size of sudoku table.
    std::vector < std::vector < Table > > sudoku_table; //A matrix of Table objects (each correcponding to single tile).
public:
    Game(int window_x, int window_y, std::vector < std::vector < int > > my_array);
    virtual ~Game();
    void initialize_table(std::vector < std::vector < int > > my_array); //A methods that reads given matrix of integers into sudoku_table object as values and sets them as unmodifiable.
    virtual void set_lines(); //Draws lines grouping tiles into blocks (for example 9x9 sudoku consists of 9 3x3 blocks)
    sf::RenderWindow window;
    sf::RenderWindow& window_setup(); 
    virtual void update_table(int row, int col, int number, SudokuTable& sudoku); //Checks if user input is allowed and then modifies visible value.
    void prompt(Table tile, int num);  //Displays a prompt - correct value that should be entered into marked tile. Num for prompt() is returned by one of the SudokuTable's methods. 
    int get_size();
    Table& const get_tile(int index_a, int index_b);
};



class Sudoku6: public Game
{
private:
    
    
public:
    Sudoku6(int window_x, int window_y, std::vector < std::vector < int > > my_array);
    void set_lines();

};


class Sudoku9 : public Game {
private:
    

public:
    Sudoku9(int window_x, int window_y, std::vector < std::vector < int > > my_array);
    void set_lines();
};


class Sudoku16: public Game 
{
public:
    Sudoku16(int window_x, int window_y, std::vector < std::vector < int > > my_array);
    void update_table(int row, int col, int number, SudokuTable& sudoku);
    void set_lines();
    
};

#endif // !GAME.H
