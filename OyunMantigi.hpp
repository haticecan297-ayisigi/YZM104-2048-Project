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

    // Gerekli getter fonksiyonlarý (Tahtayý görselleþtirmek için)
    int degerAl(int satir, int sutun) const { return tahta[satir][sutun].deger; }
    int skorAl() const { return skor; }
};
