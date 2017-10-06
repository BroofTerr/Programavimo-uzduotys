#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define PAV_ILGIS 16

struct Zaislai{
    Zaislai(): pagaminta(0){}
    vector<char> pavadinimas;
    int pagaminta;
};

void daugiausiaDirbta(int (&d)[7], ofstream &rasyti){ ///Parasys diena, per kuria buvo daugiausiai dirbta
    int daugDirbta = 0;
    for (int i = 0; i < 7; i++){
        if (d[i] > daugDirbta){
            daugDirbta = d[i];
        }
    }
    for (int i = 0; i < 7; i++){
        if (d[i] == daugDirbta){
            switch (i+1){
            case 1:
                rasyti << "Pirmadieni\n";
                break;
            case 2:
                rasyti << "Antradieni\n";
                break;
            case 3:
                rasyti << "Treciadieni\n";
                break;
            case 4:
                rasyti << "Ketvirtadieni\n";
                break;
            case 5:
                rasyti << "Penktadieni\n";
                break;
            case 6:
                rasyti << "Sestadieni\n";
                break;
            case 7:
                rasyti << "Sekmadieni\n";
                break;
            }
            break;
        }
    }
}

int main()
{
    ifstream skaityti("Kaziukas_duom.txt");
    ofstream rasyti("Kaziukas_rez.txt");
    int dirbtaDienu, zaisluSk;
    char raide;
    int skaicius;
    int savaitesDiena[7] = {0,0,0,0,0,0,0};
    int pagamintaViso = 0;
    skaityti >> dirbtaDienu >> zaisluSk;
    if (dirbtaDienu < 1 || dirbtaDienu > 120){
        rasyti << "Dirbta per daug arba per mazai dienu. Darbo dienu intervalas - [1;120]";
        return 1;
    }
    else if (zaisluSk < 1 || zaisluSk > 10){
        rasyti << "Sukurta per daug arba per mazai zaislu rusiu. Ju turi buti nuo 1 iki 10 imtinai.";
        return 1;
    }
    Zaislai zaislas[zaisluSk];

    for (int i = 0; i < zaisluSk; i++){
        skaityti >> noskipws;
        for (int j = 0; j <= PAV_ILGIS; j++){
            skaityti >> raide;
            zaislas[i].pavadinimas.push_back(raide);
        }
        if (zaislas[i].pavadinimas[PAV_ILGIS] != ' '){
            rasyti << i+1 << " Pavadinimas yra per ilgas! (Iki 16 zenklu)";
            return 1;
        }
    }
    skaityti >> skipws;
    for (int i = 0; i < dirbtaDienu; i++){
        skaityti >> skaicius;
        if (skaicius < 1 || skaicius > 7){
            rasyti << "Savaite turi tik 7 dienas, taigi intervalas - [1;7]";
            return 1;
        }
        savaitesDiena[skaicius-1]++;
        for (int j = 0; j < zaisluSk; j++){
            skaityti >> skaicius;
            zaislas[j].pagaminta += skaicius;
            pagamintaViso += skaicius;
        }
    }
    for (int i = 0; i < zaisluSk; i++){
        for (int r = 1; r < PAV_ILGIS; r++){
            rasyti << zaislas[i].pavadinimas[r];
        }
        rasyti << zaislas[i].pagaminta << endl;
    }
    rasyti << "Is viso: " << pagamintaViso << endl;
    daugiausiaDirbta(savaitesDiena, rasyti);
    int daugPagaminta = 0;
    for (int i = 0; i < zaisluSk; i++){
        if (zaislas[i].pagaminta > daugPagaminta){
            daugPagaminta = zaislas[i].pagaminta;
        }
    }
    for (int i = 0; i < zaisluSk; i++){
        if (zaislas[i].pagaminta == daugPagaminta){
            for (int r = 1; r < PAV_ILGIS; r++){
                rasyti << zaislas[i].pavadinimas[r];
            }
            break;
        }
    }
    return 0;
}
