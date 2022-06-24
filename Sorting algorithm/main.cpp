#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <array>
constexpr static long long  elements{ (1200 - 920) + 19};
int si = 900;
bool sort = false;
template<typename T>
T randrange(T b, T e)
{
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> distr(b, e);
    return distr(gen);
}
template<typename T>
void elem_swap(std::array<T, elements>& b , int begin_index , int end_index) {
    auto be = b[begin_index];
    b[begin_index] = b[end_index];
    b[end_index] = be;
}
int main()
{ 
    sf::Font font;
    if (!font.loadFromFile("Arial 2.ttf"))
        std::cout << "Failed!\n"; 

    sf::Text instructions;
    instructions.setFont(font);
    instructions.setString("Press Q to sort and press R to randomize \nPress Tab To exit");
    sf::RenderWindow window(sf::VideoMode(1200, 920), "SFML works!");
    std::array<sf::RectangleShape, elements> rect;
    float spacing = 0;
    for(float ls = 0 ; ls  < rect.size(); ls++)
        rect[ls].setSize(sf::Vector2f(2, -randrange(20, si)));
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                for(float sd = 0; sd < rect.size(); sd++)
                    rect[sd].setSize(sf::Vector2f(2, -randrange(20, si)));
                sort = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                sort = true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
                window.close();
        }
        window.clear();
        size_t js{0}, ib{0};
        int size{};
        for (int io = 0; io < rect.size(); io++)
        {
            size++;
            if (sort) {
                auto a = js, b = js + 1;
                if (rect[a].getSize().y < rect[b].getSize().y) {
                    elem_swap(rect, a, b);
                }
                if (ib < rect.size()) {
                    js = js + 1;
                    if (js >= rect.size() - ib - 1)
                    {
                        js = js - 1;
                        ib = ib + 1;
                    }
                }
            }
            rect[io].setPosition(spacing, 920 - io - -size);
            window.draw(rect[io]);
            spacing += 4;
        }
        spacing = 0;
        window.draw(instructions);
        window.display();
    }
    return 0;
}
