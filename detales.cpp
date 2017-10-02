#include <iostream>
#include <fstream>

using namespace std;

struct Detales{
    char detalesPav[24] = "";
    int detalesKiekis;
    int detalePanaudota = 0;
};

int main()
{
    ifstream skaityti("duomenys.txt");
    ofstream rasyti("rezultatas.txt");
    rasyti << "Automobiliu taisykla \"Voztuvas\"\n";
    rasyti << "Detaliu apyvarta\n\n";
    int detaliuSk;
    int detalesNr; ///Naudojamas pasirenkant detale is saraso
    int detalesApyvarta; ///Naudojamas tikrinant ar detale naudojama ar ne
    int daugPanaudota; ///Naudojamas ieskant dazniausiai panaudotos detales
    int mazLikutis; ///Naudojamas ieskant detales su maziausiu likuciu
    skaityti >> detaliuSk;
    if (detaliuSk <= 0 || detaliuSk > 100) {rasyti << "Ivesta per daug arba per mazai detaliu. Detaliu intervalas - (0;101)"; return 1;}
    Detales detale[detaliuSk];
    for (int i = 0; i < detaliuSk; i++){
        skaityti.read(detale[i].detalesPav, 23);
        skaityti >> detale[i].detalesKiekis;
        //rasyti << detale[i].detalesPav << " " << detale[i].detalesKiekis;
    }

    int detaliuPokytis; ///Kiek buvo atlikta keitimo veiksmu
    skaityti >> detaliuPokytis;
    if (detaliuPokytis < 0 || detaliuPokytis > 1000) {rasyti << "Ivesta per daug arba per mazai detaliu pokyciu. Pokyciu intervalas - (0;1001)"; return 1;}

    for (int i = 0; i < detaliuPokytis; i++){ /// Kontroliuoja apyvarta
        skaityti >> detalesNr >> detalesApyvarta;
        if (detalesApyvarta >= 0){
            detale[detalesNr-1].detalesKiekis += detalesApyvarta;
        }
        else{
            detale[detalesNr-1].detalesKiekis += detalesApyvarta;
            detale[detalesNr-1].detalePanaudota -= detalesApyvarta;
        }
    }
    skaityti.close();
    daugPanaudota = detale[0].detalePanaudota; ///Duodam pirmos detales reiksme, kuri bus naudojama palyginimams (nesvarbu kurios detales reiksme naudosim jeigu tokia detale egzistuos, t.y. nebus uz masyvo ribu)
    mazLikutis = detale[0].detalesKiekis; ///Duodam pirmos detales reiksme, kuri bus naudojama palyginimams (nesvarbu kurios detales reiksme naudosim jeigu tokia detale egzistuos, t.y. nebus uz masyvo ribu)
    for (int i = 0; i < detaliuSk; i++){   ///Randamos daugiausiai panaudotu detalu reiksme ir maziausio detaliu likuciu reiksme
        if (detale[i].detalePanaudota > daugPanaudota)
            daugPanaudota = detale[i].detalePanaudota;
        if (detale[i].detalesKiekis < mazLikutis)
            mazLikutis = detale[i].detalesKiekis;
    }

    rasyti << "Daugiausia panaudotos\n";
    rasyti << "--------------------------";
    for (int i = 0; i < detaliuSk; i++){ ///Paraso daugiausiai panaudotas detales
        if (detale[i].detalePanaudota == daugPanaudota)
            rasyti << detale[i].detalesPav << " " << detale[i].detalePanaudota;
    }
    rasyti << endl << endl;
    rasyti << "Nepanaudotos\n";
    rasyti << "--------------------------";
    for (int i = 0; i < detaliuSk; i++){
        if (detale[i].detalePanaudota == 0)
            rasyti << detale[i].detalesPav << " " << detale[i].detalesKiekis;
    }
    rasyti << endl << endl;
    rasyti << "Maziausias likutis\n";
    rasyti << "--------------------------";
    for (int i = 0; i < detaliuSk; i++){
        if (detale[i].detalesKiekis == mazLikutis)
            rasyti << detale[i].detalesPav << " " << detale[i].detalesKiekis;
    }

    return 0;
}
