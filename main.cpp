#include <SFML/Graphics.hpp>
#include "OyunMantigi.hpp"


int main() {
    // VideoMode artık süslü parantez {} ile vektör bekler
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML 3.0 Test");

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    // HATA ALDIĞIN YER: setPosition artık ({x, y}) şeklinde yazılmalı
    shape.setPosition({300.f, 200.f});

    while (window.isOpen()) {
        // SFML 3.0'da pollEvent kullanımı da değişti (Opsiyonel ama önerilen)
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
