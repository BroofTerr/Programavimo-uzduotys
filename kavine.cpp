#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define PAV_ILGIS 24 ///Pavadinimo ilgis

struct Patiekalas{
    vector<char> pavadinimas;
    int kaina;
};

struct Klientas{
    Klientas(): visaKaina(0){}
    vector<int> uzsakymai;
    int visaKaina;
};

int kainosSkaiciavimas(int k, int p){  ///Kliento uzsakymas ir patiekalo porcijos kaina
    return k * p;
}

int main()
{
    ifstream skaityti("duomenys.txt");
    ofstream rasyti ("rezultatas.txt");
    int patiekaluSk, klientuSk; /// (0;20] , (0;100]
    skaityti >> patiekaluSk >> klientuSk;
    char raide; ///Naudojamas skaitant pavadinima kas raide
    int skaicius; ///Naudojamas skaiciant skaicius ir juos ikeliant i uzsakymu vektoriu
    if (patiekaluSk < 0 || patiekaluSk > 20){
        rasyti << "Per daug arba per mazai patiekalu, ju turi buti nedaugiau kaip 20"; ///Tikrina ar atitinka intervala (0;20]
        return 1;
    }
    if (klientuSk < 0 || klientuSk > 100){
        rasyti << "Per daug arba per mazai klientu, ju turi buti nedaugiau kaip 100"; ///Tikrina ar atitinka intervala (0;100]
        return 1;
        }
    Patiekalas patiekalas[patiekaluSk];
    Klientas klientas[klientuSk];

    /** Nurodymai kaip skaityti pavadinimus ir tikrinti pavadinimu ilguma
        0. skaityti >> noskipws; (kad skaitytu ir tarpus)
        1. Po viena char'a nuskaityti raides i VECTORIU charu (vector<char> pavadinimas) ISKAITANT 24a raide, ji - tikrinimui
        2. push_backinti kas chara (aisku viskas skaitoma loope)
        3. skaityti >> skipws (reikalinga kad galetum perskaityti kaina), ir tada skaityt kaina
        4. tikrinti taip: if(pavadinimas[24] (paskutine raide) != ' ' (whitespace'ui) || kaina (skaicius einantis po pavadinimo) != 0 (yra pakeistas i nuly jei blogai nuskaitomas), tai tada pavadinimas per ilgas)
    */

    for (int i = 0; i < patiekaluSk; i++){
        skaityti >> noskipws;
        for (int j = 0; j <= PAV_ILGIS; j++){
            skaityti >> raide;
            patiekalas[i].pavadinimas.push_back(raide);
        }
        skaityti >> skipws;
        skaityti >> patiekalas[i].kaina;
        if (patiekalas[i].pavadinimas[24] != ' ' || patiekalas[i].kaina == 0){
            rasyti << i+1 << " Pavadinimas yra per ilgas! (Iki 24 zenklu)";
            return 1;
        }
    }

    /**for (int i = 0; i < patiekaluSk; i++){
        for (int j = 1; j < PAV_ILGIS; j++){
            cout << patiekalas[i].pavadinimas[j];
        }
        cout << " " << patiekalas[i].kaina << endl;
    }*/

    for (int i = 0; i < klientuSk; i++){
        for (int j = 0; j < patiekaluSk; j++){
            skaityti >> skaicius;
            klientas[i].uzsakymai.push_back(skaicius);
        }
    }
    skaityti.close();

    /**for (int i = 0; i < klientuSk; i++){
        for (int j = 0; j < patiekaluSk; j++){
            cout << klientas[i].uzsakymai[j] << " ";
        }
        cout << endl;
    }*/

    int brangUzsak = 0; ///Naudojamas surasti pacio brangiausio(iu) uzsakymo(u) savininka(us)
    for (int i = 0; i < klientuSk; i++){
        for (int j = 0; j < patiekaluSk; j++){
            klientas[i].visaKaina += kainosSkaiciavimas(klientas[i].uzsakymai[j], patiekalas[j].kaina);
        }
        if (klientas[i].visaKaina > brangUzsak){
            brangUzsak = klientas[i].visaKaina;
        }
    }

    for (int i = 0; i < klientuSk; i++){
        if (klientas[i].visaKaina == brangUzsak){
            for (int j = 0; j < patiekaluSk; j++){
                if (klientas[i].uzsakymai[j] * patiekalas[j].kaina != 0){ /// Jeigu buvo toks uzsakymas
                    for (int r = 1; r < PAV_ILGIS; r++){
                        rasyti << patiekalas[j].pavadinimas[r];
                    }
                    rasyti << " ";
                    rasyti.width(3);
                    rasyti << right << patiekalas[j].kaina << " X " << klientas[i].uzsakymai[j] << " = ";
                    rasyti << patiekalas[j].kaina*klientas[i].uzsakymai[j] << endl;
                }
            }
            rasyti << "Is viso: " << klientas[i].visaKaina << endl;
            rasyti << endl; ///Jeigu butu daugiau neigu vienas klientas, kuriu didziausios kainos sutampa
        }
    }

    return 0;
}
