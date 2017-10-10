#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

#define VARDO_ILGIS 16

struct Dalyvis{
    Dalyvis(): visoTasku(0){}
    vector<char> vardasPav;
    vector<int> surinktaTasku;
    int visoTasku;
};

int main()
{
    ifstream skaityti ("duomenys.txt");
    ofstream rasyti ("rezultatas.txt");
    int dalyviuSk, uzduociu, minTasku;
    int perejoEtapa = 0;
    skaityti >> dalyviuSk >> uzduociu >> minTasku;
    if (dalyviuSk < 4 || dalyviuSk > 100){
        rasyti << "Dalyvauja per mazai arba per daug dalyviu! Ju turi buti nuo 4 iki 100 imtinai.";
        return 1;
    }
    else if (uzduociu < 1 || uzduociu > 10){
        rasyti << "Olimpiadoje per mazai arba per daug uzduociu! Ju turi buti nuo 1 iki 10 imtinai.";
        return 1;
    }
    if (minTasku < 10 || minTasku > 150){
        rasyti << "Nustatytas per zemas arba per aukstas minimaliu tasku, perejimui i kita etapa, skaicius";
        return 1;
    }
    Dalyvis dalyvis[dalyviuSk];
    int skaicius;
    char raide;
    for (int i = 0; i < dalyviuSk; i++){
        skaityti >> noskipws;
        for(int r = 0; r <= VARDO_ILGIS+1; r++){
            skaityti >> raide;
            dalyvis[i].vardasPav.push_back(raide);
        }
        ///Patikrinti del ilgio
        if (dalyvis[i].vardasPav[VARDO_ILGIS+1] != ' '){
            rasyti << i+1 << " Dalyvio vardas ir pavarde yra per ilga! Iki 16 simboliu.";
            return 1;
        }
        skaityti >> skipws;
        for (int j = 0; j < uzduociu; j++){
            skaicius = -1; ///Naudojama patikrinti ar yra ivelta raide kaskur tarp skaiciu
            skaityti >> skaicius;
            dalyvis[i].surinktaTasku.push_back(skaicius);
            dalyvis[i].visoTasku += skaicius;
            if (skaicius == -1){
                rasyti << "Kazkur yra isivelusi raide ar kitoks ne skaitinis zenklas tarp skaiciu duomenyse!";
                return 1;

            }
        }
        if (dalyvis[i].visoTasku >= minTasku){
            perejoEtapa++;
        }
    }
    int taskai[dalyviuSk];
    for (int i = 0; i < dalyviuSk; i++){
        taskai[i] = dalyvis[i].visoTasku;
    }
    sort(taskai, taskai+dalyviuSk, greater<int>());
    for (int i = 0; i < dalyviuSk; i++){
        for (int j = 0; j < dalyviuSk; j++){
            if (dalyvis[j].visoTasku == taskai[i]){
                for (int r = 1; r < VARDO_ILGIS+1; r++){
                    rasyti << dalyvis[j].vardasPav[r];
                }
                rasyti.width(5);
                rasyti << taskai[i] << endl;
                dalyvis[j].visoTasku = -1; /// Reikalingas, kad nesusifeilintu programa, jeigu dalyviai turi vienoda skaiciu tasku
            }
        }

        if (i == 2){ ///Atskiria 3 geriausius
            rasyti.width(22);
            rasyti.fill('-');
            rasyti << " " << endl;
            rasyti.fill(' ');
        }
        if (i == perejoEtapa-1){ ///Atskiria nepatekusius i kita etapa
            rasyti.width(22);
            rasyti.fill('=');
            rasyti << " " << endl;
            rasyti.fill(' ');
        }
    }
    rasyti << perejoEtapa;

    return 0;
}
