#include <iostream>
#include <fstream>

using namespace std;

/// Pagal apskaiciavimus, geresnis kompiuteris pavyzdyje butu 4-tas, o ne 2-as. Nezinau ar pas mane klaida ar ne.
/// Jeigu pakeistume galios atimti i sudeti santykio skaiciavime, rezultate gautume 2-a kompiuteri

struct Kompiuteris{
    Kompiuteris(): Imone(""), Santykis(0.0f), Netenkinimai(0){}
    string Imone;
    double Daznis;
    int RAM;
    float HDD;
    float Galia;
    int Kaina;
    float Garantija;
    float Santykis;
    int Netenkinimai; ///Laikomas reikalavimu nepatenkinimu skaicius
};

///Kainos ir kokybes santykio funkcija
float kainosKokybesSantykis (Kompiuteris kompiuteris){
    return (kompiuteris.Kaina/(kompiuteris.Daznis+kompiuteris.RAM+kompiuteris.HDD/1000-kompiuteris.Galia/1000+kompiuteris.Garantija/20)); ///Gaunami blogi skaiciai
}

///Parametru tikrinimo funkcija (grazina netenkinanciu salygas skaiciu, t.y. grazins 0, jei kompiuteris tenkina visus kriterijus)
int reikalavimuTikrinimas (Kompiuteris kompiuteris, Kompiuteris norimas){
    int netenkina = 0;
    if (kompiuteris.Daznis < norimas.Daznis){netenkina++;}
    if (kompiuteris.RAM < norimas.RAM){netenkina++;}
    if (kompiuteris.HDD < norimas.HDD){netenkina++;}
    if (kompiuteris.Galia > norimas.Galia){netenkina++;}
    if (kompiuteris.Kaina > norimas.Kaina){netenkina++;}
    if (kompiuteris.Garantija < norimas.Garantija){netenkina++;}
    return netenkina;
}

void perkamasKompiuteris(Kompiuteris kompiuteris, Kompiuteris norimas){
    ofstream rasyti("rezultatai.txt");
    rasyti << "Pirksime is parduotuves " << kompiuteris.Imone << endl;
    rasyti.width(41);
    rasyti.fill('-');
    rasyti << "" << endl;
    rasyti.fill(' ');
    rasyti.width(26);
    rasyti << left << "Taktinis daznis GHz ";
    rasyti.width(5);
    rasyti << right << kompiuteris.Daznis;
    if (kompiuteris.Daznis < norimas.Daznis){rasyti << " netenkina\n";}
    else {rasyti << " tenkina\n";}
    rasyti.width(26);
    rasyti << left << "RAM dydis GB ";
    rasyti.width(5);
    rasyti << right << kompiuteris.RAM;
    if (kompiuteris.RAM < norimas.RAM){rasyti << " netenkina\n";}
    else {rasyti << " tenkina\n";}
    rasyti.width(26);
    rasyti << left << "Standziojo disko dydis GB ";
    rasyti.width(5);
    rasyti << right << kompiuteris.HDD;
    if (kompiuteris.HDD < norimas.HDD){rasyti << " netenkina\n";}
    else {rasyti << " tenkina\n";}
    rasyti.width(26);
    rasyti << left << "Elektrine galia W ";
    rasyti.width(5);
    rasyti << right << kompiuteris.Galia;
    if (kompiuteris.Galia > norimas.Galia){rasyti << " netenkina\n";}
    else {rasyti << " tenkina\n";}
    rasyti.width(26);
    rasyti << left << "Kaina Lt ";
    rasyti.width(5);
    rasyti << right << kompiuteris.Kaina;
    if (kompiuteris.Kaina > norimas.Kaina){rasyti << " netenkina\n";}
    else {rasyti << " tenkina\n";}
    rasyti.width(26);
    rasyti << left << "Garantija men. ";
    rasyti.width(5);
    rasyti << right << kompiuteris.Garantija;
    if (kompiuteris.Garantija < norimas.Garantija){rasyti << " netenkina\n";}
    else {rasyti << " tenkina\n";}
}

int main()
{
    ifstream skaityti("duomenys.txt");
    float maziausiasSantykis = 10000.0f; ///Naudojamas randant ta puiku kompiuteri
    Kompiuteris norimas;
    skaityti >> norimas.Daznis; skaityti >> norimas.RAM; skaityti >> norimas.HDD; skaityti >> norimas.Galia; skaityti >> norimas.Kaina; skaityti >> norimas.Garantija; ///Nuskaito visus 6 norimo kompiuterio duomenis
    int kompSkaicius;
    skaityti >> kompSkaicius;
    ///-----------------------------------------
    ofstream rasyti("rezultatai.txt");
    if (kompSkaicius > 0 && kompSkaicius < 101){}
    else {rasyti << "Per daug arba nera pasiulytu kompiuteriu"; return 1;} ///Tikrina pasiulymu skaiciu (turi priklausyti intervalui (0;101) )
    ///-----------------------------------------
    Kompiuteris kompiuteriai[kompSkaicius];
    for (int i = 0; i < kompSkaicius; i++){
        skaityti >> kompiuteriai[i].Imone;
        if (kompiuteriai[i].Imone.length() > 10) {rasyti << i+1 << " Kompiuteriu imones pavadinimas per ilgas"; return 1;} ///Tikrina istaigos pavadinimo ilgi (turi buti nedaugiau, kaip 10 simboliu, iskaitant kabutes)
        skaityti >> kompiuteriai[i].Daznis;
        skaityti >> kompiuteriai[i].RAM;
        skaityti >> kompiuteriai[i].HDD;
        skaityti >> kompiuteriai[i].Galia;
        skaityti >> kompiuteriai[i].Kaina;
        skaityti >> kompiuteriai[i].Garantija;
        kompiuteriai[i].Santykis = kainosKokybesSantykis(kompiuteriai[i]);
        kompiuteriai[i].Netenkinimai = reikalavimuTikrinimas(kompiuteriai[i], norimas);
    }
    skaityti.close();
    ///-----------------------------------------
    for (int i = 0; i < kompSkaicius; i++){  ///Atrenkamas tinkamiausias kompiuteris
        if (kompiuteriai[i].Netenkinimai <= 1){
            if (maziausiasSantykis > kompiuteriai[i].Santykis){
                maziausiasSantykis = kompiuteriai[i].Santykis;
            }
        }
    }
    ///-----------------------------------------
    for (int i = 0; i < kompSkaicius; i++){
        if (kompiuteriai[i].Santykis == maziausiasSantykis){ ///Jeigu yra pasiulytas tinkamas kompiuteris
            perkamasKompiuteris(kompiuteriai[i], norimas);
            return 0;
        }
    }
    rasyti << "Ne viena parduotuve nepateike tinkamo pasiulymo" << endl; ///Jeigu nera pasiulyto tinkamo kompiuterio

    return 0;
}
