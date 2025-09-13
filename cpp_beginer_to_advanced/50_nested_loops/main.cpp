#include <iostream>
#include <iomanip>


int main(int argc, char* argv[]) {
    
    std::size_t const ROWS = 12;
    std::size_t const COLS = 3;

    auto nested_for_loop = [&ROWS, &COLS]() {
        std::cout << "Tabular data visualization with nested for loop" << std::endl;

        for(std::size_t row = 0; row < ROWS; ++row) {
            for(std::size_t col = 0; col < COLS; ++col) {
                std::cout << "( row " << std::setw(2) << row << ", col " << std::setw(2) << col << ")";
            }
            std::cout << std::endl;
        }

        std::cout << std::endl;
    };

    auto while_loop = [&ROWS, &COLS]() {
        std::cout << "Tabular data visualization with nested while loop" << std::endl;
        std::size_t row = 0;
        std::size_t col = 0;

        while(row < ROWS) {
            while(col < COLS) {
                std::cout << "( row " << std::setw(2) << row << ", col " << std::setw(2) << col << ")";
                ++ col;
            }
            std::cout << std::endl;
            col = 0;
            ++ row;
        }
        std::cout << std::endl;
    };

    auto do_while_loop = [&ROWS, &COLS]() {
        std::cout << "Tabular data visualization with nested do while loop" << std::endl;
        std::size_t row = 0;
        std::size_t col = 0;
        do {
            do {
                std::cout << "( row " << std::setw(2) << row << ", col " << std::setw(2) << col << ")";
                ++ col;
            } while(col < COLS);
            std::cout << std::endl;
            col = 0;
            ++ row;
        } while(row < ROWS);
    };

    nested_for_loop();
    while_loop();
    do_while_loop();

    return EXIT_SUCCESS;
}