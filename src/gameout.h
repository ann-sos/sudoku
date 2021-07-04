#pragma once
#ifndef GAMEOUT_H_
#define GAMEOUT_H_

#include "game.h"
/**
* @project sudoku
* @author ann-sos
* @purpose  Gameout deals with marking tiles as clicked/inactive, refreshing window view and getting mouse coordinates. Classes game and gameout make up GUI of Sudoku app.
*           Gameout pozwala na oznaczanie poszczególnych kratek na planszy sudoku jako klikniête lub nieaktywne. Metody klasy Gameout odwœwie¿aj¹ aktualizuj¹ widok w oknie
            i pobieraj¹ koordynaty myszy. Klasy Game oraz Gameout sk³adaj¹ siê na interfejs graficzny Sudoku.
*/

class Game;
class SudokuTable;

//Struct Table corresponds to single tile in the sudoku table. Struktura Table odpowiada pojedynczej komórce na planszy sudoku.
struct Table {
    bool modifiable = false; //Set whether a tile can be modified by the user.
    int value; //Displayed value.
    int row;
    int col;
    sf::RectangleShape tile;
    friend bool is_modifiable(Table& tile);
};

//An object od PressedTile class stores information which tile is currently clicked. Objekt klasy PressedTile przechowuje informacjê, która z komórek (jeœli jakakolwiek) jest aktywna (klikniêta).
class PressedTile {
public:
    bool anything_clicked = false; //Set to false when all tiles are inactive.
    int row = 0;
    int col = 0;
    PressedTile();
};

//Gameout deals with marking tiles as clicked/inactive, refreshing window view and getting mouse coordinates. 
// Gameout pozwala na oznaczanie poszczególnych kratek na planszy sudoku jako klikniête lub nieaktywne. Metody klasy Gameout odwœwie¿aj¹ aktualizuj¹ widok w oknie i pobieraj¹ koordynaty myszy.
class GameOut {
    sf::Text text;
    sf::Font font;
    PressedTile red_tile;
public:
    friend bool calling_function(std::vector < std::vector < int > >& my_array, SudokuTable& sudoku);
    GameOut();
    void mark_pressed(Game* mg, Table& tile, bool pressed); //Mark tile as pressed.
    bool is_clicked(); //Returns true when any tile is active (based on information stored in red_tile object).
    void click(Game* mg, Table& clicked_tile); 
    void draw_tiles(Game* mg, sf::RenderWindow& window); //Redraws sudoku table.
    void set_text(Game* mg, Table& const tile, sf::RenderWindow& window, int number = -1);
    Table& clicked_tile(Game* mg, sf::Vector2i mouse_pos); //Returns reference to the tile active in the moment.
    sf::Vector2i get_pos() {
        return sf::Vector2i(red_tile.row, red_tile.col);
    }
    std::vector < std::vector < int > > collect_values(Game* mg);
};
#endif // !GAMEOUT_H_