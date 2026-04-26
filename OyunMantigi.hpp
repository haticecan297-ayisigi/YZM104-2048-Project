#include <vector>
#include <ctime>
#include <cstdlib>
#include "Kutu.hpp"
using namespace std;

class OyunMantigi {
private:
    Kutu tahta[4][4];   // 4x4 oyun alaný
    int skor;           // Güncel skor
    bool hareketEttiMi; // Yeni sayý eklenmesi için hareket kontrolü
    void birlestirmeIsaretleriniTemizle() {   // Bir hamlede kalmamasi icin her hamleden sonra tekrar false olmali.
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                tahta[i][j].birlestiMi = false;
    }

public:
    OyunMantigi() {
        skor = 0;
        srand(time(0)); // Rastgelelik için zamaný baþlat
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

        for (int i = 0; i < 4; i++) {         // Sıfır olmayan bir kutu bulup onu hedef haline getiriyoruz.
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

    // Gerekli getter fonksiyonlarý (Tahtayý görselleþtirmek için)
    int degerAl(int satir, int sutun) const { return tahta[satir][sutun].deger; }
    int skorAl() const { return skor; }
};
