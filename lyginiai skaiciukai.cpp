#include <iostream>
#include <fstream>
using namespace std;

int rastiLyginiusSkaicius (int skaicius, int *dLS){
    int lyginiuSkaiciu = 0;
    while (skaicius != 0){
        if ((skaicius % 10) % 2 == 0 && skaicius % 10 != 0) ///Jeigu skaiciaus vienas skaiciukas yra lyginis, tai...
            lyginiuSkaiciu++;
        skaicius /= 10;
    }
    if (lyginiuSkaiciu > *dLS) ///Pakeis skaiciaus reiksme jeigu jinai yra didesne
        *dLS = lyginiuSkaiciu;
    return lyginiuSkaiciu;
}


int main()
{
    ifstream skaityti("duomenys.txt");
    int n; /// Laiko savyje kiek bus skaiciu
    int daugLygSkaic = 0; ///Laiko savyje didziausia lyginiuSkaiciu skaiciuje reiksme
    skaityti >> n;
    int skaiciai[n], lygSkaic[n]; /// lygSkaic kaups savyje informacija apie kiek kiekvienas skaicius turi lyginiu skaiciu savyje
    for (int i = 0; i < n; i++){
        skaityti >> skaiciai[i];
        lygSkaic[i] = rastiLyginiusSkaicius(skaiciai[i], &daugLygSkaic);
    }
    skaityti.close();
    ofstream rasyti("rezultatas.txt");
    for (int i = 0; i < n; i++){
        if (lygSkaic[i] == daugLygSkaic)
            rasyti << skaiciai[i] << endl;
    }

    return 0;
}
