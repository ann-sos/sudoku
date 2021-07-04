#include "game.h"
#include "gameout.h"

using namespace sf;
/**
* SUDOKU
* @author ann-sos
* @purpose Class Game (together with class GameOut) makes up GUI of Sudoku game - is responsible for displaying sudoku table and allowing user to input values by clicking on the modifiable tiles and entering/deleting numbers.
* Klasa Game wyœwietla tablicê sudoku i przyjmuje input od u¿ytkownika. Klasa Game jest sk³adow¹ projektu Sudoku.
*/
std::ostream& operator<< (std::ostream& out, Table& tile) {
    out << "You clicked on (" << tile.row << ", " << tile.col << ") Value: " << tile.value << " Is modifiable: " << tile.modifiable << std::endl;
    return out;
}


PressedTile::PressedTile()
{

}


//Game class constructor
//@param width and height of the window, array of integers
Game::Game(int window_x, int window_y, std::vector < std::vector < int > > my_array) {
    this->window_x = window_x;
    this->window_y = window_y;
    int vec_size = my_array.size();
    std::cout << "Vector size: " << vec_size << std::endl;
    tile_x = static_cast<float>(window_x) / vec_size;
    tile_y = static_cast<float>(window_y) / vec_size;
    sudoku_table.resize(vec_size, std::vector<Table>(vec_size));
    //last_pressed = Vector2i(-1, -1);
    initialize_table(my_array);
    
}

Game::~Game()
{
}

Sudoku6::Sudoku6(int window_x, int window_y, std::vector < std::vector < int > > my_array) : Game(window_x, window_y, my_array)
{
    std::cout << "Created Sudoku6\n";
}


Sudoku9::Sudoku9(int window_x, int window_y, std::vector < std::vector < int > > my_array) : Game(window_x, window_y, my_array)
{
    std::cout << "Created Sudoku9\n";
}

Sudoku16::Sudoku16(int window_x, int window_y, std::vector < std::vector < int > > my_array) : Game(window_x, window_y, my_array)
{
    std::cout << "Created Sudoku16\n";
}



//Checks if a tile can take input
bool is_modifiable(Table& tile) {
    if (tile.modifiable == true) {
        return true;
    }
    else {
        return false;
    }
}





/**
* Initializes an array of Table type objects. 0s are assigned bool value modifiable=true, value takes int numbers from init_array.
* @param
        init array: reference to inicializing array
        sudoku_table: reference to array of Table structures that are to be filled
        size_x, size_y: width and height of a single file
* @return doesn't return anything, sudoku_table is modified by reference
*/

void Game::initialize_table(std::vector < std::vector < int > > init_array) {
    
    for (int row = 0; row < init_array.size(); row++) {
        for (int col = 0; col < init_array.size(); col++) {
            sudoku_table[row][col].value = init_array[row][col]; //assign value            
            sudoku_table[row][col].tile.setSize(Vector2f(tile_x, tile_y)); //set size of the tile
            sudoku_table[row][col].tile.setPosition(Vector2f(col * tile_y, row * tile_x));
            sudoku_table[row][col].tile.setOutlineColor(Color::Black);
            sudoku_table[row][col].tile.setOutlineThickness(-2.5);
            sudoku_table[row][col].row = row;
            sudoku_table[row][col].col = col;
            if (init_array[row][col] == 0) {
                sudoku_table[row][col].modifiable = true;
                sudoku_table[row][col].tile.setFillColor(Color::White);
            }
            else {
                sudoku_table[row][col].modifiable = false;
                sudoku_table[row][col].tile.setFillColor(Color::Blue);
            }
        }
    }
    set_lines();
    
}

void Game::set_lines()
{
}

void Sudoku6::set_lines() {
    for (int l = 0; l < 6; l += 3) {
        Vertex line[] = { Vertex(Vector2f(l * tile_y, 0.f)), Vertex(Vector2f(l * tile_y, window_y)) };
        window.draw(line, 2, Lines);
    }
    for (int l = 0; l < 6; l += 2) {
        Vertex line[] = { Vertex(Vector2f(0.f, l * tile_x)), Vertex(Vector2f(window_x, l * tile_x)) };
        window.draw(line, 2, Lines);
    }
}

void Sudoku9::set_lines() {
    for (int l = 0; l < 9; l += 3) {
        Vertex line[] = { Vertex(Vector2f(l * tile_y, 0.f)), Vertex(Vector2f(l * tile_y, window_y)) };
        window.draw(line, 2, Lines);
    }
    for (int l = 0; l < 9; l += 3) {
        Vertex line[] = { Vertex(Vector2f(0.f, l * tile_x)), Vertex(Vector2f(window_x, l * tile_x)) };
        window.draw(line, 2, Lines);
    }
}

void Sudoku16::set_lines() {
    for (int l = 0; l < 16; l += 4) {
        Vertex line[] = { Vertex(Vector2f(l * tile_y, 0.f)), Vertex(Vector2f(l * tile_y, window_y)) };
        window.draw(line, 2, Lines);
    }
    for (int l = 0; l < 16; l += 4) {
        Vertex line[] = { Vertex(Vector2f(0.f, l * tile_x)), Vertex(Vector2f(window_x, l * tile_x)) };
        window.draw(line, 2, Lines);
    }
}
//Sets style, size and name of the window.
RenderWindow& Game::window_setup() {
    window.create(VideoMode(window_x, window_y), "Sudoku!", Style::Close | Style::Titlebar);
    window.setFramerateLimit(60);
    return window;
}

void Game::prompt(Table tile, int num) {
    Text text;
    Font font;
    if (!font.loadFromFile("verdana.ttf")) {
        throw("NIE UDALO SIE ZALADOWAC CZCIONKI");
    }
    text.setFont(font);
    text.setFillColor(Color::Green);
    text.setCharacterSize(20);

    text.setPosition(tile.tile.getPosition() + Vector2f(0.3 * tile_x, 0.25 * tile_y));
    text.setString(std::to_string(num));

    window.draw(text);
    window.display();
}


//Contains main loop.
bool calling_function(std::vector < std::vector < int > >& my_array, SudokuTable& sudoku) {
    std::cout << "Zaznacz dowolne biale pole i nacisnij P, aby otrzymac podpowiedz.\nKliknij ESC, zeby zamknac okno z gra. \nPartia nie zostanie utracona, dopoki nie zamkniesz okna konsoli lub nie zaczniesz nowej partii.\n";
    int x = my_array.size();
    char max_digit = '0';
    Game* my_game = NULL;
    if (x == 6)
    {
        my_game = new Sudoku6(400, 400, my_array);
        max_digit = '6';
    }
    if (x == 9)
    {
        my_game = new Sudoku9(600, 600, my_array);
        max_digit = '9';
    }
    if (x == 16)
    {
        my_game = new Sudoku16(800, 800, my_array);
        max_digit = '9';

    }
    GameOut UserInterface;
    RenderWindow& window = my_game->window_setup();
    
    Table tile;

    while (window.isOpen())
    {
        Event event;
        Vector2i mouse_c;
        while (window.pollEvent(event))
        {
            if (event.type == event.Closed)
                window.close();
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            {
                window.close();
            }
            if (event.type == Event::MouseButtonReleased && window.hasFocus()) {
                mouse_c = Mouse::getPosition(window);
                tile = UserInterface.clicked_tile(my_game, mouse_c);
                UserInterface.click(my_game, tile);
#ifdef _DEBUG
                std::cout << tile;
#endif // _DEBUG
            }
            if (UserInterface.is_clicked() && event.type == Event::TextEntered) {
                char entered_char{ static_cast<char>(event.text.unicode) };
                std::cout << entered_char << std::endl;
                if (entered_char == 'p' && is_modifiable(tile) && UserInterface.is_clicked()) {
                    std::cout << "p PRESEED!\n";
                    int prompt_n = sudoku.numberHint(UserInterface.get_pos().x, UserInterface.get_pos().y);
                    my_game->prompt(tile, prompt_n);
                }
                if (static_cast<int>(event.text.unicode) <= static_cast<int>(max_digit) && is_modifiable(tile) && UserInterface.is_clicked()) {
                    std::stringstream ss;
                    ss << entered_char; int entered_digit; ss >> entered_digit;
                    my_game->update_table(tile.row, tile.col, entered_digit, sudoku);
                    sudoku.table = UserInterface.collect_values(my_game);
                    if (sudoku.checkTable()) {
                        window.close();
                        //COLOR TEXT - WINDOWS ONLY
                        HANDLE  hConsole;
                        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        for (int i = 1; i < 12; i += 1) {
                            SetConsoleTextAttribute(hConsole, i);
                            std::cout << "WYGRANA!!! GRATULACJE\n";
                        }
                        //SET TO STANDARD CONSOLE COLORS
                        SetConsoleTextAttribute(hConsole, 15);
                        
                    }
                }
                
                else
                {
                    std::cout << "Click on a tile that can be modified!\n";
                }
               
            }
            
        }
        UserInterface.draw_tiles(my_game, window);
    }
    return true;
}




//changes value in sudoku_table to param number
void Game::update_table(int row, int col, int number, SudokuTable& sudoku) {
    sudoku_table[row][col].value = number;
    if (!sudoku.boolHint(row, col, sudoku_table[row][col].value)) {
        std::cout << "Wartosc " << sudoku_table[row][col].value << " w (" << row << ", " << col << ") jest niepoprawna!\n";
    }
}

void Sudoku16::update_table(int row, int col, int number, SudokuTable& sudoku) {
#ifdef _DEBUG
    std::cout << "Entered Sudoku16 update method \n";
#endif // DEBUG

    
    if (sudoku_table[row][col].value != 0) {
        std::stringstream ss;
        ss << sudoku_table[row][col].value; std::string existing_digit; ss >> existing_digit;
        std::string new_digit = std::to_string(number);
        int new_number{ 0 };
        new_number = std::stoi(existing_digit.append(new_digit));
#ifdef _DEBUG
        std::cout << existing_digit << " + " << new_digit <<" Concatenation: " << new_number << " Result: " << new_number << "\n";
#endif // _DEBUG

        if (new_number <= 16) {
            sudoku_table[row][col].value = new_number;
        }
        else sudoku_table[row][col].value = number;
    }
    else sudoku_table[row][col].value = number;
    if (!sudoku.boolHint(row, col, sudoku_table[row][col].value)) {
        std::cout << "Wartosc " << sudoku_table[row][col].value << " w (" << row << ", " << col << ") jest niepoprawna!\n";
    }
    
}


 
//Returns reference to a single tile
Table& const Game::get_tile(int index_a, int index_b) {
    return sudoku_table[index_a][index_b];
}

//Returns width of the single tile
int Game::get_size() {
    return tile_x;
}
