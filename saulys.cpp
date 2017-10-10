#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

#define VARDO_ILGIS 20
#define SOVIMU_SKAICIUS 10

struct Dalyvis{
    Dalyvis(): sautaKartu(0), visoTasku(0){}
    vector<char> vardasPav;
    vector<int> taskai;
    int sautaKartu;
    int visoTasku;
    float vidurkis;
};

int main()
{
    int dalyviuSk;
    ifstream skaityti("duom.txt");
    ofstream rasyti("rez.txt");
    skaityti >> dalyviuSk;
    if (dalyviuSk < 5 || dalyviuSk > 10){
        rasyti << "Dalyvauja per mazai arba per daug sauliu! Ju turi dalyvauti nuo 5 iki 10 imtinai.";
        return 1;
    }
    Dalyvis dalyvis[dalyviuSk];
    char raide; int skaicius;
    float taskai[dalyviuSk];
    for (int i = 0; i < dalyviuSk; i++){
        skaityti >> noskipws;
        for (int r = 0; r <= VARDO_ILGIS+1; r++){
            skaityti >> raide;
            dalyvis[i].vardasPav.push_back(raide);
        }
        if (dalyvis[i].vardasPav[VARDO_ILGIS+1] != ' '){
            rasyti << i+1 << " Saulio vardas ir pavarde yra per ilgi! iki 20 simboliu.";
            return 1;
        }
        skaityti >> skipws;
        for (int j = 0; j < SOVIMU_SKAICIUS; j++){
            skaicius = -1;
            skaityti >> skaicius;
            dalyvis[i].taskai.push_back(skaicius);
            if (skaicius == -1){
                rasyti << "Kazkur tarp skaiciu yra iterptas ne skaitinis zenklas!";
                return 1;
            }
            if (skaicius != 0){
                dalyvis[i].sautaKartu++;
            }
            dalyvis[i].visoTasku += skaicius;
        }
        if (dalyvis[i].sautaKartu == 0){
            dalyvis[i].vidurkis = 0.f;
        }
        else {
            dalyvis[i].vidurkis = (float)dalyvis[i].visoTasku/dalyvis[i].sautaKartu;
        }
        taskai[i] = dalyvis[i].vidurkis;
    }
    sort(taskai, taskai+dalyviuSk, greater<float>());
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < dalyviuSk; j++){
            if (dalyvis[j].vidurkis == taskai[i]){
                for (int r = 1 ; r < VARDO_ILGIS+1; r++){
                    rasyti << dalyvis[j].vardasPav[r];
                }
                dalyvis[j].vidurkis = 0.f;
                rasyti << fixed << setprecision(2) << taskai[i] << endl;
            }
        }
    }

    return 0;
}
