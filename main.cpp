#include <SFML/Graphics.hpp>
using namespace std;

int main() {
    // VideoMode artýk süslü parantez {} ile vektör bekler
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML 3.0 Test");

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    // HATA ALDIÐIN YER: setPosition artýk ({x, y}) þeklinde yazýlmalý
    shape.setPosition({300.f, 200.f});

    while (window.isOpen()) {
        // SFML 3.0'da pollEvent kullanýmý da deðiþti (Opsiyonel ama önerilen)
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
