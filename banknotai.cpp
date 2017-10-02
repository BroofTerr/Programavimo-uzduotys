#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct Bankas{
    Bankas(): priimta({0,0,0,0,0,0,0,0}), isduota({0,0,0,0,0,0,0,0}), visoPriimta(0), visoIsduota(0){}
    int banknotai[9];          ///1Lt, 2Lt, 5Lt, 10Lt, 20Lt, 50Lt, 100Lt, 200Lt, 500Lt
    int priimta[9];
    int isduota[9];
    int visoPriimta;
    int visoIsduota;
} bankas;

void Priimta(Bankas &bankas, int pinigas){
    switch(pinigas){
    case 1:
        bankas.banknotai[0]++;
        bankas.priimta[0]++;
        bankas.visoPriimta += pinigas;
        break;
    case 2:
        bankas.banknotai[1]++;
        bankas.priimta[1]++;
        bankas.visoPriimta += pinigas;
        break;
    case 5:
        bankas.banknotai[2]++;
        bankas.priimta[2]++;
        bankas.visoPriimta += pinigas;
        break;
    case 10:
        bankas.banknotai[3]++;
        bankas.priimta[3]++;
        bankas.visoPriimta += pinigas;
        break;
    case 20:
        bankas.banknotai[4]++;
        bankas.priimta[4]++;
        bankas.visoPriimta += pinigas;
        break;
    case 50:
        bankas.banknotai[5]++;
        bankas.priimta[5]++;
        bankas.visoPriimta += pinigas;
        break;
    case 100:
        bankas.banknotai[6]++;
        bankas.priimta[6]++;
        bankas.visoPriimta += pinigas;
        break;
    case 200:
        bankas.banknotai[7]++;
        bankas.priimta[7]++;
        bankas.visoPriimta += pinigas;
        break;
    case 500:
        bankas.banknotai[8]++;
        bankas.priimta[8]++;
        bankas.visoPriimta += pinigas;
        break;
    }
}

void Isduota(Bankas &bankas, int pinigas){
    switch(pinigas){
    case -1:
        bankas.banknotai[0]--;
        bankas.isduota[0]++;
        bankas.visoIsduota += -pinigas;
        break;
    case -2:
        if (bankas.banknotai[1] != 0){
            bankas.banknotai[1]--;
            bankas.isduota[1]++;
            bankas.visoIsduota += -pinigas;
        }
        else { ///Jeigu nebera 2Lt banknotu, tai iskeiciama i 2 1Lt banknotus, ir tas pats principas kituose case'uose
            Isduota(bankas, -1);
            Isduota(bankas, -1);
        }
        break;
    case -5:
        if (bankas.banknotai[2] != 0){
            bankas.banknotai[2]--;
            bankas.isduota[2]++;
            bankas.visoIsduota += -pinigas;
        }
        else {
            Isduota(bankas, -2);
            Isduota(bankas, -2);
            Isduota(bankas, -1);
        }
        break;
    case -10:
        if (bankas.banknotai[3] != 0){
            bankas.banknotai[3]--;
            bankas.isduota[3]++;
            bankas.visoIsduota += -pinigas;
        }
        else {
            Isduota(bankas, -5);
            Isduota(bankas, -5);
        }
        break;
    case -20:
        if (bankas.banknotai[4] != 0){
            bankas.banknotai[4]--;
            bankas.isduota[4]++;
            bankas.visoIsduota += -pinigas;
        }
        else {
            Isduota(bankas, -10);
            Isduota(bankas, -10);
        }
        break;
    case -50:
        if (bankas.banknotai[5] != 0){
            bankas.banknotai[5]--;
            bankas.isduota[5]++;
            bankas.visoIsduota += -pinigas;
        }
        else {
            Isduota(bankas, -20);
            Isduota(bankas, -20);
            Isduota(bankas, -10);
        }
        break;
    case -100:
        if (bankas.banknotai[6] != 0){
            bankas.banknotai[6]--;
            bankas.isduota[6]++;
            bankas.visoIsduota += -pinigas;
        }
        else {
            Isduota(bankas, -50);
            Isduota(bankas, -50);
        }
        break;
    case -200:
        if (bankas.banknotai[7] != 0){
            bankas.banknotai[7]--;
            bankas.isduota[7]++;
            bankas.visoIsduota += -pinigas;
        }
        else {
            Isduota(bankas, -100);
            Isduota(bankas, -100);
        }
        break;
    case -500:
        if (bankas.banknotai[8] != 0) {
            bankas.banknotai[8]--;
            bankas.isduota[8]++;
            bankas.visoIsduota += -pinigas;
        }
        else {
            Isduota(bankas, -200);
            Isduota(bankas, -200);
            Isduota(bankas, -100);
        }
        break;
    }
}

void spausdintiPriimtus(Bankas bankas, ofstream &rasyti){
    rasyti << "Priimta:\n";
    rasyti << "-------------------" << endl;
    int banknotai[9] = {1, 2, 5, 10, 20, 50, 100, 200, 500};
    for (int i = 0; i < 9; i++){
        if (bankas.priimta[i] != 0){
            rasyti.width(3);
            rasyti << right << banknotai[i] << " x ";
            rasyti.width(2);
            rasyti << right << bankas.priimta[i] << " = ";
            rasyti.width(5);
            rasyti << right << banknotai[i] * bankas.priimta[i] << " Lt\n";
        }
    }
    rasyti << "-------------------" << endl;
    rasyti << "Is viso:";
    rasyti.width(8);
    rasyti << right << bankas.visoPriimta << " Lt\n\n";
}

void spausdintiIsduotus(Bankas bankas, ofstream &rasyti){
    rasyti << "Isduota:\n";
    rasyti << "-------------------" << endl;
    int banknotai[9] = {1, 2, 5, 10, 20, 50, 100, 200, 500};
    for (int i = 0; i < 9; i++){
        if (bankas.isduota[i] != 0){
            rasyti.width(3);
            rasyti << right << banknotai[i] << " x ";
            rasyti.width(2);
            rasyti << right << bankas.isduota[i] << " = ";
            rasyti.width(5);
            rasyti << right << banknotai[i] * bankas.isduota[i] << " Lt\n";
        }
    }
    rasyti << "-------------------" << endl;
    rasyti << "Is viso:";
    rasyti.width(8);
    rasyti << right << bankas.visoIsduota << " Lt\n";
}

int main()
{
    ifstream skaityti("duomenys.txt");
    ofstream rasyti("rezultatas.txt");
    int veiksmuSkaicius; ///Kiek kartu banknotu gauta, isduota, keista
    int pinigas; ///Kaupiama veiksmo reiksme ir pagal ja nustatoma - ar isduotas banknotas, ar gautas
    for (int i = 0; i < 9; i++){
        skaityti >> bankas.banknotai[i];
    }
    skaityti >> veiksmuSkaicius;

    for (int i = 0; i < veiksmuSkaicius; i++){ ///Banknotu kontrole
        skaityti >> pinigas;
        if (pinigas > 0){    ///Priimtas banknotas
            Priimta(bankas, pinigas);
        }
        else {               ///Isduotas banknotas
            Isduota(bankas, pinigas);
        }
    }

    spausdintiPriimtus(bankas, rasyti);     /// PATAISYTI KAD ISSPAUZDINTU NORMALIAI
    spausdintiIsduotus(bankas, rasyti);
    rasyti << "-------------------" << endl;
    rasyti << "Balansas:";

    int balansas = bankas.visoPriimta - bankas.visoIsduota; /// Nustato kiek reikia atitraukti skaiciaus rasymo pradzia nuo desines
    stringstream skaiciausIlgis;
    if (balansas > 0){
        skaiciausIlgis << balansas;
        rasyti.width(7-skaiciausIlgis.str().length());
        rasyti << right << "+" << balansas << " Lt";
    }
    else {
        skaiciausIlgis << -balansas;
        rasyti.width(7-skaiciausIlgis.str().length());
        rasyti << right << "-" << -1*balansas << " Lt";
    }
    return 0;
}
