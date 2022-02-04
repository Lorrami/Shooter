#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    std::cout << "Hello, World!" << std::endl;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "sdf");

    while(window.isOpen()){
        window.clear();

        window.display();
    }

    return 0;
}
