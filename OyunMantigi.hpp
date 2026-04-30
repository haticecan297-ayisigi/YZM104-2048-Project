#include <vector>
#include <ctime>
#include <cstdlib>
#include "Kutu.hpp"
using namespace std;

class OyunMantigi {
private:
    Kutu tahta[4][4];   // 4x4 oyun alani
    int skor;           // Guncel skor
    bool hareketEttiMi; // Yeni sayi eklenmesi icin hareket kontrolu
    void birlestirmeIsaretleriniTemizle() {   // Bir hamlede kalmamasi icin her hamleden sonra tekrar false olmali.
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                tahta[i][j].birlestiMi = false;
    }

public:
    OyunMantigi() {
        skor = 0;
        srand(time(0)); // Rastgelelik için zamani baslat
        tahtayiSifirla();
    }

    // Oyunu baþlatmak için tahtayý temizler ve 2 sayý ekler
    void tahtayiSifirla() {
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                tahta[i][j].deger = 0;
                tahta[i][j].birlestiMi = false;
            }
        }
        rastgeleKutuEkle();
        rastgeleKutuEkle();
    }

    // Boþ bir hücreye %90 ihtimalle 2, %10 ihtimalle 4 ekler
    void rastgeleKutuEkle() {
        vector<pair<int, int>> bosHucreler;

        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                if(tahta[i][j].deger == 0) {
                    bosHucreler.push_back({i, j});
                }
            }
        }

        if(!bosHucreler.empty()) {
            int rastgeleIndeks = rand() % bosHucreler.size();
            int satir = bosHucreler[rastgeleIndeks].first;
            int sutun = bosHucreler[rastgeleIndeks].second;

            // %10 ihtimalle 4, %90 ihtimalle 2 ekle
            tahta[satir][sutun].deger = (rand() % 10 == 0) ? 4 : 2;
        }
    }
    // Sola Kaydırma Ana Fonksiyonu
    void solaKaydir() {
        hareketEttiMi = false;
        birlestirmeIsaretleriniTemizle();

        for (int i = 0; i < 4; i++) {         // Sifir olmayan bir kutu bulup onu hedef haline getiriyoruz.
            for (int j = 1; j < 4; j++) {
                if (tahta[i][j].deger != 0) {
                    int hedefSutun = j;

                    // En sola kadar boşlukları tara
                    while (hedefSutun > 0 && tahta[i][hedefSutun - 1].deger == 0) {
                        tahta[i][hedefSutun - 1].deger = tahta[i][hedefSutun].deger;
                        tahta[i][hedefSutun].deger = 0;
                        hedefSutun--;
                        hareketEttiMi = true;
                    }//Birlesebilecegi bir sayi yoksa bos olan soldaki en son kutuda kaliyor.

                    // Birleştirme kontrolü
                    if (hedefSutun > 0 &&
                        tahta[i][hedefSutun - 1].deger == tahta[i][hedefSutun].deger &&   // Bir kerede birden fazla birlesmemesi icin false olmali.
                        !tahta[i][hedefSutun - 1].birlestiMi) {

                        tahta[i][hedefSutun - 1].deger *= 2;
                        skor += tahta[i][hedefSutun - 1].deger;
                        tahta[i][hedefSutun - 1].birlestiMi = true;
                        tahta[i][hedefSutun].deger = 0;
                        hareketEttiMi = true;
                    }
                }
            }
        }
        if (hareketEttiMi) rastgeleKutuEkle();   // Her hamlede bos kutulardan birine 2 veya 4 gelmeli.
    }

    // SAGA KAYDIRMA: sagdan sola dogu kontrol et
    void sagaKaydir() {
        hareketEttiMi = false;
        birlestirmeIsaretleriniTemizle();
        for (int i = 0; i < 4; i++) {
            for (int j = 2; j >= 0; j--) { // 3. sutun sabit, 2'den 0'a
                if (tahta[i][j].deger != 0) {
                    int hedefSutun = j;
                    while (hedefSutun < 3 && tahta[i][hedefSutun + 1].deger == 0) {
                        tahta[i][hedefSutun + 1].deger = tahta[i][hedefSutun].deger;
                        tahta[i][hedefSutun].deger = 0;
                        hedefSutun++;
                        hareketEttiMi = true;
                    }
                    if (hedefSutun < 3 && tahta[i][hedefSutun + 1].deger == tahta[i][hedefSutun].deger && !tahta[i][hedefSutun + 1].birlestiMi) {
                        tahta[i][hedefSutun + 1].deger *= 2;
                        skor += tahta[i][hedefSutun + 1].deger;
                        tahta[i][hedefSutun + 1].birlestiMi = true;
                        tahta[i][hedefSutun].deger = 0;
                        hareketEttiMi = true;
                    }
                }
            }
        }
        if (hareketEttiMi) rastgeleKutuEkle();
    }

    // YUKARI KAYDIRMA: ustten asagi dogru kontrol et
    void yukariKaydir() {
        hareketEttiMi = false;
        birlestirmeIsaretleriniTemizle();
        for (int j = 0; j < 4; j++) {
            for (int i = 1; i < 4; i++) { // 0. satir sabit, 1'den 3'e
                if (tahta[i][j].deger != 0) {
                    int hedefSatir = i;
                    while (hedefSatir > 0 && tahta[hedefSatir - 1][j].deger == 0) {
                        tahta[hedefSatir - 1][j].deger = tahta[hedefSatir][j].deger;
                        tahta[hedefSatir][j].deger = 0;
                        hedefSatir--;
                        hareketEttiMi = true;
                    }
                    if (hedefSatir > 0 && tahta[hedefSatir - 1][j].deger == tahta[hedefSatir][j].deger && !tahta[hedefSatir - 1][j].birlestiMi) {
                        tahta[hedefSatir - 1][j].deger *= 2;
                        skor += tahta[hedefSatir - 1][j].deger;
                        tahta[hedefSatir - 1][j].birlestiMi = true;
                        tahta[hedefSatir][j].deger = 0;
                        hareketEttiMi = true;
                    }
                }
            }
        }
        if (hareketEttiMi) rastgeleKutuEkle();
    }

    // ASAGI KAYDIRMA: Alttan yukari dogru kontrol et
    void asagiKaydir() {
        hareketEttiMi = false;
        birlestirmeIsaretleriniTemizle();
        for (int j = 0; j < 4; j++) {
            for (int i = 2; i >= 0; i--) { // 3. satir sabit, 2'den 0'a
                if (tahta[i][j].deger != 0) {
                    int hedefSatir = i;
                    while (hedefSatir < 3 && tahta[hedefSatir + 1][j].deger == 0) {
                        tahta[hedefSatir + 1][j].deger = tahta[hedefSatir][j].deger;
                        tahta[hedefSatir][j].deger = 0;
                        hedefSatir++;
                        hareketEttiMi = true;
                    }
                    if (hedefSatir < 3 && tahta[hedefSatir + 1][j].deger == tahta[hedefSatir][j].deger && !tahta[hedefSatir + 1][j].birlestiMi) {
                        tahta[hedefSatir + 1][j].deger *= 2;
                        skor += tahta[hedefSatir + 1][j].deger;
                        tahta[hedefSatir + 1][j].birlestiMi = true;
                        tahta[hedefSatir][j].deger = 0;
                        hareketEttiMi = true;
                    }
                }
            }
        }
        if (hareketEttiMi) rastgeleKutuEkle();
    }

    // Gerekli getter fonksiyonlari (Tahtayi görsellestirmek icin)
    int degerAl(int satir, int sutun) const { return tahta[satir][sutun].deger; }
    int skorAl() const { return skor; }

    //Sayilara gore bulundugu kutunun rengi vektorel olarak degismesi icin.
    sf::Color renkAl(int deger) {
    switch (deger) {
        case 2:    return sf::Color(238, 228, 218);    //Kirli Beyaz
        case 4:    return sf::Color(237, 224, 200);    //Krem
        case 8:    return sf::Color(242, 177, 121);    //Acik Turuncu
        case 16:   return sf::Color(245, 149, 99);     //Koyu Turuncu
        case 32:   return sf::Color(246, 124, 95);     //Mercan
        case 64:   return sf::Color(246, 94, 59);      //Parlak Kirmizi
        case 128:  return sf::Color(237, 207, 114);    //Parlak Sari
        case 256:  return sf::Color(237, 204, 97);     //Altın Sarisi
        case 512:  return sf::Color(237, 200, 80);     //Gunes Sarisi
        case 1024: return sf::Color(237, 197, 63);     //Limon Sarisi
        case 2048: return sf::Color(237, 194, 46);     //Ozel Altin
        default:   return sf::Color(205, 193, 180);    // Boş kutu rengi bej
    }
}
};
