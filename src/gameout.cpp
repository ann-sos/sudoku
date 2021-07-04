#include "gameout.h"
#include "game.h"

using namespace sf;
/**
* @project sudoku
* @author ann-sos
* @purpose  Gameout deals with marking tiles as clicked/inactive, refreshing window view and getting mouse coordinates. Classes game and gameout make up GUI of Sudoku app.
*           Gameout pozwala na oznaczanie poszczególnych kratek na planszy sudoku jako klikniête lub nieaktywne. Metody klasy Gameout odwœwie¿aj¹ aktualizuj¹ widok w oknie
            i pobieraj¹ koordynaty myszy. Klasy Game oraz Gameout sk³adaj¹ siê na interfejs graficzny Sudoku.
*/

GameOut::GameOut()
{

}

std::vector < std::vector < int > > GameOut::collect_values(Game* mg) {
    std::vector < std::vector < int > > values_table;
    values_table.resize(mg->sudoku_table.size(), std::vector<int>(mg->sudoku_table.size()));
    for (int row = 0; row < mg->sudoku_table.size(); row++) {
        for (int col = 0; col < mg->sudoku_table.size(); col++) {
            values_table[row][col] = mg->sudoku_table[row][col].value;
        }
    }
    return values_table;
}

/*Marks selected tile as active/inactive depending on its state.*/
void GameOut::click(Game* mg, Table& clicked_tile) {
    if (clicked_tile.modifiable) {
        if (red_tile.anything_clicked)
        {

            if (red_tile.row == clicked_tile.row && red_tile.col == clicked_tile.col)
            {
                //clicked on marked tile so it will be unchecked
                mark_pressed(mg, clicked_tile, false);
            }
            else {
                //another tile will me marked
                mark_pressed(mg, clicked_tile, false);
                mark_pressed(mg, clicked_tile, true);

            }
        }
        else
        {

            //nothing was pressed, mark_clicked new tile
            mark_pressed(mg, clicked_tile, true);
        }

    }
    else {
        mark_pressed(mg, clicked_tile, false);
    }

}





//Displays copy of the tile as red. sudoku_table is not modified.
void GameOut::mark_pressed(Game* mg, Table& tile, bool pressed) {
    //if pressed==true it will be marked red, otherwise white (unchecking tile)
    if (pressed) {
        mg->sudoku_table[tile.row][tile.col].tile.setFillColor(Color::Red);
        red_tile.anything_clicked = true;
        red_tile.row = tile.row;
        red_tile.col = tile.col;
    }
    else {
        mg->sudoku_table[red_tile.row][red_tile.col].tile.setFillColor(Color::White);
        red_tile.anything_clicked = false;
    }

}

bool GameOut::is_clicked()
{
    if (red_tile.anything_clicked) return true;
    else  return false;
}


//Returns a copy of a tile that was selected based on cursor coordinates.
Table& GameOut::clicked_tile(Game* mg, Vector2i mouse_pos) {
    int col = mouse_pos.x / mg->tile_x;
    int row = mouse_pos.y / mg->tile_y;
    Table& tile = mg->sudoku_table[row][col];

    return tile;
}




//Draws on the screen RectangleShape objects stored in sudoku_table array.
//@param window
void GameOut::draw_tiles(Game* mg, RenderWindow& window) {
    window.clear(Color::Black);
    for (auto& const row : mg->sudoku_table) {
        for (auto& const element : row) {
            window.draw(element.tile);
            if (element.value != 0) {
                set_text(mg, element, window, element.value);
            }
        }
    }
    mg->set_lines();
    window.display();
}





/*Prints number in the middle of the tile.*/
void GameOut::set_text(Game* mg, Table& tile, RenderWindow& window, int number)
{
    Text text;
    Font font;
    if (!font.loadFromFile("verdana.ttf")) {
        throw("NIE UDALO SIE ZALADOWAC CZCIONKI");
    }
    text.setFont(font);
    text.setFillColor(Color::Black);
    text.setCharacterSize(20);

    text.setPosition(tile.tile.getPosition() + Vector2f(0.3 * mg->tile_x, 0.25 * mg->tile_y));
    text.setString(std::to_string(number));

    window.draw(text);
}


