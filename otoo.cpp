#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>

using namespace std;

struct Urun {
    int id;
    char ad[50];
    double fiyat;
};

void menu();
void urunEkle();
void menuListele();
void urunAra();
void urunSil();

int main() {
    menu();
    return 0;
}

void menu() {
    int secim;
    do {
        cout << "\n==========================================" << endl;
        cout << "      ISUBU FAST FOOD OTOMASYONU         " << endl;
        cout << "==========================================" << endl;
        cout << " [1] -> Yeni Urun Ekle" << endl;
        cout << " [2] -> Menuyu Goruntule" << endl;
        cout << " [3] -> Urun Ara (ID ile)" << endl;
        cout << " [4] -> Urun Sil" << endl;
        cout << " [0] -> Programdan Cikis" << endl;
        cout << "------------------------------------------" << endl;
        cout << "Seciminiz: ";
        cin >> secim;

        switch (secim) {
            case 1: urunEkle(); break;
            case 2: menuListele(); break;
            case 3: urunAra(); break;
            case 4: urunSil(); break;
            case 0: cout << "\nProgram kapatiliyor. Iyi gunler!" << endl; break;
            default: cout << "\n!!! Hatali secim yaptiniz, tekrar deneyin." << endl;
        }
    } while (secim != 0);
}

void urunEkle() {
    Urun yeniUrun;
    ofstream dosya("menu.dat", ios::app | ios::binary);

    cout << "\n>>> YENI URUN KAYIT EKRANI <<<" << endl;
    cout << "------------------------------" << endl;
    cout << "Urun ID     : "; cin >> yeniUrun.id;
    cout << "Urun Adi    : "; cin.ignore(); cin.getline(yeniUrun.ad, 50);
    cout << "Birim Fiyat : "; cin >> yeniUrun.fiyat;

    dosya.write((char*)&yeniUrun, sizeof(Urun));
    dosya.close();
    cout << "\n*** Kayit Basariyla Dosyaya Islendi ***" << endl;
}

void menuListele() {
    Urun yedek;
    ifstream dosya("menu.dat", ios::binary);

    if (!dosya) {
        cout << "\n[!] HATA: Veri dosyasi bulunamadi!" << endl;
        return;
    }

    cout << "\n==================================================" << endl;
    cout << "             GUNCEL YEMEK LISTESI                " << endl;
    cout << "==================================================" << endl;
    cout << left << setw(8) << "ID" << setw(25) << "URUN ADI" << setw(10) << "FIYAT" << endl;
    cout << "--------------------------------------------------" << endl;
    
    while (dosya.read((char*)&yedek, sizeof(Urun))) {
        cout << left << setw(8) << yedek.id 
             << setw(25) << yedek.ad 
             << fixed << setprecision(2) << yedek.fiyat << " TL" << endl;
    }
    cout << "--------------------------------------------------" << endl;
    dosya.close();
}

void urunAra() {
    Urun yedek;
    int arananId;
    bool bulundu = false;
    ifstream dosya("menu.dat", ios::binary);

    cout << "\n>>> URUN ARAMA <<<" << endl;
    cout << "Aranacak ID: "; cin >> arananId;

    while (dosya.read((char*)&yedek, sizeof(Urun))) {
        if (yedek.id == arananId) {
            cout << "\n--- Kayit Bulundu ---" << endl;
            cout << "Urun: " << yedek.ad << "\nFiyat: " << yedek.fiyat << " TL" << endl;
            cout << "---------------------" << endl;
            bulundu = true;
            break;
        }
    }
    if (!bulundu) cout << "\n[!] Aradiginiz ID'ye ait urun bulunamadi." << endl;
    dosya.close();
}

void urunSil() {
    Urun yedek;
    int silinecekId;
    bool bulundu = false;
    
    ifstream dosya("menu.dat", ios::binary);
    ofstream geciciDosya("gecici.dat", ios::binary);

    cout << "\n>>> URUN SILME ISLEMI <<<" << endl;
    cout << "Silinecek Urun ID: "; cin >> silinecekId;

    while (dosya.read((char*)&yedek, sizeof(Urun))) {
        if (yedek.id != silinecekId) {
            geciciDosya.write((char*)&yedek, sizeof(Urun));
        } else {
            bulundu = true;
        }
    }

    dosya.close();
    geciciDosya.close();

    remove("menu.dat");
    rename("gecici.dat", "menu.dat");

    if (bulundu) cout << "\n*** Urun basariyla sistemden silindi. ***" << endl;
    else cout << "\n[!] Silinmek istenen ID bulunamadi!" << endl;
}
