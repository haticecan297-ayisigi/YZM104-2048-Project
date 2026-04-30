#include <SFML/Graphics.hpp>
#include "OyunMantigi.hpp"
#include <string>
#include <iostream>
#include <optional>
using namespace std;

int main() {
    // Kutuphane ile bir oyun pencersei aciyorum.
    sf::RenderWindow pencere(sf::VideoMode({450, 450}), "2048");
    pencere.setFramerateLimit(60);  //Zaman yonetimini limit ile yapıyorum.

    OyunMantigi oyun;   //class ismi olarak oyun kullaniyorum.
    sf::Font font;      // Baska bir class turu, gorsel icin kullanilacak, ismini font diyorum.

    // Font yukleme kontrolu
    if (!font.openFromFile("arial.ttf")) {
        cout << "HATA: arial.ttf dosyasi bulunamadi veya bozuk!" <<endl;
    }
    //Ben oyun penceresini kapatana kadar acik kalmasi icin
    while (pencere.isOpen()) {
        //basilan tuslar karismamasi ve siralanmasi icin dongu
        while (const optional olay = pencere.pollEvent()) {
            if (olay->is<sf::Event::Closed>()) {   //X basinca oyun penceresini kapat bu sayededis dongudeki isopen false olur.
                pencere.close();
            }

            // Klavye girisi kontrolu
            if (const auto* basilanTus = olay->getIf<sf::Event::KeyPressed>()) {
                if (basilanTus->code == sf::Keyboard::Key::Left)       oyun.solaKaydir();
                else if (basilanTus->code == sf::Keyboard::Key::Right) oyun.sagaKaydir();
                else if (basilanTus->code == sf::Keyboard::Key::Up)    oyun.yukariKaydir();
                else if (basilanTus->code == sf::Keyboard::Key::Down)  oyun.asagiKaydir();
            }
        }

        pencere.clear(sf::Color(187, 173, 160)); // Arka plan rengi

        // 4x4 Izgarayi Cizme
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int deger = oyun.degerAl(i, j);

                // Kareyi (Kutuyu) Ciz
                sf::RectangleShape kare(sf::Vector2f({100.f, 100.f}));  // 100 piksellik satir ve sutun belirliyoruz.
                kare.setPosition({j * 110.f + 10.f, i * 110.f + 10.f});  //Penceremiz icine konumlandiriyoruz.
                kare.setFillColor(oyun.renkAl(deger));     //Karenin icinin rengini belirliyoruz
                pencere.draw(kare);    //Kare Cizime hazir.

                //Sayiyi Ciz (Eger deger 0 degilse ve font yuklendiyse) ---
                if (deger != 0) {
                    sf::Text metin(font);   //SFML de sablon (fony)zorunlu
                    metin.setString(std::to_string(deger));   //int degerleri metin yapiyoruz.
                    metin.setCharacterSize(30);   //Boyut belirliyoruz
                    metin.setFillColor(deger <= 4 ? sf::Color(119, 110, 101) : sf::Color::White);  //Sayilarin hangi renkte yazagini soyuyuruz

                    //Yaziyi ortalama
                    const sf::FloatRect metinBoyut = metin.getLocalBounds();//varsayilan boyutu aliyoruz
                    metin.setOrigin({metinBoyut.size.x / 2.0f, metinBoyut.size.y / 2.0f});   //Boyutunu yariya indiriyoruz
                    metin.setPosition({j * 110.f + 10.f + 50.f, i * 110.f + 10.f + 50.f});   //Kutunun en sol kosesinden basladigi icin 50. birime yerlestiriyoruz.

                    pencere.draw(metin);    //Sayi cizime hazir.
                }
            }
        }

        pencere.display();   //Ekran karindaki hazir olan her sey ekrana cizilme emri veriyoruz
    }

    return 0;
}
