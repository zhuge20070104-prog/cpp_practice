#include <iostream>
#include <thread>
#include "SFML/Graphics.hpp"
#include <atomic>
#include <vector>
#include <functional>
#include <chrono>
#include <algorithm>
#include <memory>


std::vector<int> grid;

std::vector<std::unique_ptr<sf::Shape>> shapes;

bool is_running = true;

void update_grid(int x, int y) {
    while(is_running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        grid[y * 2 + x] = rand() % 4;
    }
}

int main(int argc, char* argv[]) {
    grid.reserve(4);
    std::fill(grid.begin(), grid.end(), 0);

    for(int x=0; x<2; ++x) {
        for(int y=0; y<2; ++y) {
            shapes.push_back(std::make_unique<sf::CircleShape>(100.0f));
        }
    }

    std::vector<std::thread> threads;
    for(int x=0; x<2; ++x) {
        for(int y=0; y<2; ++y) {
            threads.push_back(std::thread(update_grid, x, y));
        }
    }

    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML with C++ Threads");

    while(window.isOpen() && is_running) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
                is_running = false;
            }
        }

        window.clear();
        for(int x=0; x<2; ++x) {
            for(int y=0; y<2; ++y) {
                shapes[y * 2 + x]->setPosition(x*200, y*200);
                if(0 == grid[y * 2 + x]) {
                    shapes[y * 2 + x]->setFillColor(sf::Color::Red);
                } else if(1 == grid[y * 2 + x]) {
                    shapes[y * 2 + x]->setFillColor(sf::Color::Green);
                } else if(2 == grid[y * 2 + x]) {
                    shapes[y * 2 + x]->setFillColor(sf::Color::Blue);
                } else if(3 == grid[y * 2 + x]) {
                    shapes[y * 2 + x]->setFillColor(sf::Color::White);
                }
            }
        }

        for(auto& shape: shapes) {
            window.draw(*shape);
        }
        window.display();
    }

    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
    return EXIT_SUCCESS;    
}