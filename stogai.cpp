#include <iostream>
#include <fstream>
using namespace std;

struct Rusis{ ///struct'as kiekvienai medienos rusiai
    int plotis;
    int aukstis;
    int plotas(){ return plotis * aukstis;}
    float liekanos;
};

int main()
{
    ifstream skaityti("duomenys.txt");
    int rusiuSkaicius;
    float minLiekanos = 1.0f;
    skaityti >> rusiuSkaicius;
    int stogoPlotis, stogoIlgis, stogoPlotas;
    Rusis matmenys[rusiuSkaicius];
    for (int i = 0; i < rusiuSkaicius; i++){
        skaityti >> matmenys[i].plotis >> matmenys[i].aukstis;
    }
    skaityti >> stogoPlotis >> stogoIlgis;
    skaityti.close();

    stogoPlotas = stogoPlotis * stogoIlgis;
    for (int i = 0; i < rusiuSkaicius; i++){
        matmenys[i].liekanos = (float)stogoPlotas/matmenys[i].plotas() - stogoPlotas/matmenys[i].plotas(); ///Apskaiciuoja kiek bus liekanu susidare padengus visa stoga
        if (matmenys[i].liekanos < minLiekanos) ///Tikrina ar tai yra maziau liekanu uz praeita skaiciu liekanu
            minLiekanos = matmenys[i].liekanos; ///Naudojama surandant atitinkancia plokste
    }
    ofstream rasyti("rezultatas.txt");
    for (int i = 0; i < rusiuSkaicius; i++){
        if (minLiekanos == matmenys[i].liekanos){
            rasyti << stogoPlotas/matmenys[i].plotas() << " "; ///Paraso kiek reikes ploksciu padengti visam stogui
            rasyti << matmenys[i].plotis << " " << matmenys[i].aukstis; ///Paraso parinktos plokstes matmenis
        }
    }
    return 0;
}
