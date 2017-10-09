#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Dalyvis {
    Dalyvis(): taskai(0){}
    int kelintasDalyvis;
    string saukinys;
    string vardas;
    int uzmegstiRysiai;
    vector<int> kelintasRysys;
    vector<string> uzmegstoRysioSaukinys;
    vector<string> uzmegstoRysioVardas;
    vector<int> uzmegstoRysioKelintasRysys;
    int taskai;
};

int main()
{
    ifstream skaityti("duomenys.txt");
    ofstream rasyti("rezultatas.txt");
    int dalyviuSk;
    string zodis;
    int skaicius;

    skaityti >> dalyviuSk;
    if (dalyviuSk < 1 || dalyviuSk > 20){
        rasyti << "Per mazai arba per daug dalyviu, ju turi buti iki 20.";
        return 1;
    }
    Dalyvis dalyvis[dalyviuSk];
    for (int i = 0; i < dalyviuSk; i++){
        dalyvis[i].kelintasDalyvis = i+1;
        skaityti >> dalyvis[i].saukinys >> dalyvis[i].vardas >> dalyvis[i].uzmegstiRysiai;
        if (dalyvis[i].uzmegstiRysiai < 1 || dalyvis[i].uzmegstiRysiai > 100){
            rasyti << i+1 << " Dalyvis uzmezge per mazai arba per daug rysiu, ju turi buti maziau nei 100.";
            return 1;
        }
        for (int j = 0; j < dalyvis[i].uzmegstiRysiai; j++){
            ///rasyti << "x";
            skaityti >> skaicius;
            dalyvis[i].kelintasRysys.push_back(skaicius);
            skaityti >> zodis;
            dalyvis[i].uzmegstoRysioSaukinys.push_back(zodis);
            skaityti >> zodis;
            dalyvis[i].uzmegstoRysioVardas.push_back(zodis);
            skaityti >> skaicius;
            dalyvis[i].uzmegstoRysioKelintasRysys.push_back(skaicius);
            if (dalyvis[i].uzmegstoRysioSaukinys[j].size() > 5){
                rasyti << "Dalyvio saukinys per ilgas arba per trumpas. Turi buti 5 simboliu ilgumo";
                return 1;
            }
            else if (dalyvis[i].uzmegstoRysioVardas[j].size() > 19 || dalyvis[i].uzmegstoRysioVardas[j].size() < 1){
                rasyti << "Dalyvio vardas per ilgas arba per trumpas. Turi buti nuo 1 iki 20 raidziu";
                return 1;
            }
        }
    }

    ///Tikrinimai
    /// 1 taskas duodamas jei uzmegsto rysio savininkas turi toki pati salies iniciala kaip
    /// skambintojas arba jam tai nera pirmas skambutis
    /// 5 taskai skiriami jei uzmegsto rysio savininkas yra is kitos salies arba tai yra jo pirmas skambutis
    for (int i = 0; i < dalyviuSk; i++){
        for (int j = 0; j < dalyvis[i].uzmegstiRysiai; j++){
            if (dalyvis[i].uzmegstoRysioKelintasRysys[j] == 1){ ///Jei uzmegsto rysio savininkui tai pirmas skambutis
                if (dalyvis[i].saukinys[0] == dalyvis[i].uzmegstoRysioSaukinys[j][0] && dalyvis[i].saukinys[1] == dalyvis[i].uzmegstoRysioSaukinys[j][1]){ ///Jei uzmegsto rysio savininkas is tos pacios salies
                    dalyvis[i].taskai++;
                }
                else{ ///Jei zmogus svetimsalis
                    dalyvis[i].taskai += 5;
                }
            }
            else if (dalyvis[i].uzmegstoRysioKelintasRysys[j] != 1){ ///Jei tai nera pirmas skambutis uzmegsto rysio savininkui
                if (dalyvis[i].saukinys[0] == dalyvis[i].uzmegstoRysioSaukinys[j][0] && dalyvis[i].saukinys[1] == dalyvis[i].uzmegstoRysioSaukinys[j][1]){ ///Jei uzmegsto rysio savininkas is tos pacios salies
                    dalyvis[i].taskai++;
                }
                else{ ///Jei zmogus svetimsalis
                    dalyvis[i].taskai += 5;
                }
            }
        }
    }
    int taskai[dalyviuSk];
    for (int i = 0; i < dalyviuSk; i++){
        taskai[i] = dalyvis[i].taskai;
    }
    sort(taskai,taskai+dalyviuSk);
    reverse(taskai, taskai+dalyviuSk);
    for (int i = 0; i < dalyviuSk; i++){
        for (int j = 0; j < dalyviuSk; j++){
            if (dalyvis[j].taskai == taskai[i]){
            rasyti << dalyvis[j].kelintasDalyvis << " " << dalyvis[j].saukinys << " " << dalyvis[j].vardas << " " << dalyvis[j].taskai << endl;
            break;
            }
        }
    }

    return 0;
}
