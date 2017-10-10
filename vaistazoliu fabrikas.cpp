#include <iostream>
#include <fstream>
using namespace std;


struct Darbininkai{
    int supakuota;
    int pilnuDeziu;
    int liekanu;
};

int main()
{
    ifstream skaityti("duomenys.txt");
    ofstream rasyti("rezultatas.txt");
    int darbSk, kiekisDezeje;
    int deziuIsLiekanu, visoSusikaupeLiekanu = 0, daugSupakuotaDeziu = 0; ///Didziausia reiksme;
    skaityti >> darbSk >> kiekisDezeje;
    if (darbSk < 1 || darbSk > 30){
        rasyti << "Dirba per mazai arba per daug zmoniu. Ju turi dirbti nuo 1 iki 30 imtinai";
        return 1;
    }
    else if (kiekisDezeje < 1 || kiekisDezeje > 16){
        rasyti << "Nustatyta per daug arba per mazai vaistazoliu kiekis per deze. Ju kiekis - [1;16]";
        return 1;
    }
    Darbininkai darbininkas[darbSk];
    for (int i = 0; i < darbSk; i++){
        skaityti >> darbininkas[i].supakuota;
        darbininkas[i].pilnuDeziu = darbininkas[i].supakuota/kiekisDezeje;
        darbininkas[i].liekanu = darbininkas[i].supakuota%kiekisDezeje;
        visoSusikaupeLiekanu += darbininkas[i].liekanu;
        if (darbininkas[i].pilnuDeziu > daugSupakuotaDeziu){
            daugSupakuotaDeziu = darbininkas[i].pilnuDeziu;
        }
    }
    deziuIsLiekanu = visoSusikaupeLiekanu/kiekisDezeje;

    for (int i = 0; i < darbSk; i++){
        rasyti.width(6);
        rasyti << left << darbininkas[i].pilnuDeziu << " ";
        rasyti.width(3);
        rasyti << left << darbininkas[i].liekanu << "\n";
    }
    rasyti << deziuIsLiekanu << "\n" << daugSupakuotaDeziu;

    return 0;
}
