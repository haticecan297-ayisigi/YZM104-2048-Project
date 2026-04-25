#ifndef kutu_hpp
#define kutu_hpp

struct Kutu {
    int deger;          // Sayi degeri (2, 4, 8...)
    bool birlestiMi;    // Bir hamlede birden fazla birlesmeyi engellemek icin kontrol

    // Varsayilan kurucu
    Kutu() : deger(0), birlestiMi(false) {}
};

#endif
