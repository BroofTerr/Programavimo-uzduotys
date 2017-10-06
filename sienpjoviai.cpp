#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define VARDO_ILGIS 16

struct Darbininkas{
    Darbininkas(): visasUzdarbisLt(0), visasUzdarbisCt(0), darbas(0){}
    vector<char> vardas;
    int darbas; ///Kiek per diena turi dirbti
    int ltUzAra; ///Kiek gauna litu, centu uz ara
    int ctUzAra;
    int visasUzdarbisLt;
    int visasUzdarbisCt;
};

void uzdarbioSkaiciavimas(Darbininkas &d){
    d.visasUzdarbisLt = d.ltUzAra * d.darbas;
    d.visasUzdarbisLt += (d.ctUzAra * d.darbas)/100;
    d.visasUzdarbisCt = (d.ctUzAra * d.darbas)%100;
}

int main()
{
    ifstream skaityti("duomenys.txt");
    ofstream rasyti("rezultatas.txt");
    int asmenuSk, darbDienSk;
    char raide; ///Reikalinga nuskaitant varda
    int skaicius; ///Reikalingas skaitant darbo kruvi arais
    skaityti >> asmenuSk >> darbDienSk;
    if (asmenuSk < 1 || asmenuSk > 15){
        rasyti << "Dirba per daug arba per mazai zmoniu, ju turi dirbti nuo 1 iki 15 imtinai.";
        return 1;
    }
    else if (darbDienSk < 1 || darbDienSk > 20){
        rasyti << "Dirba per daug arba per mazai dienu. Jie turi dirbti nuo 1 iki 20 dienu imtinai.";
    }
    Darbininkas darbininkas[asmenuSk];

    for (int i = 0; i < asmenuSk; i++){
        skaityti >> noskipws;
        for (int j = 0; j <= VARDO_ILGIS; j++){
            skaityti >> raide;
            darbininkas[i].vardas.push_back(raide);
        }
        skaityti >> skipws;
        skaityti >> darbininkas[i].ltUzAra;
        skaityti >> darbininkas[i].ctUzAra;
        if (darbininkas[i].vardas[16] != ' ' || darbininkas[i].ltUzAra == 0){
            rasyti << i+1 << " Pavadinimas yra per ilgas! (Iki 16 zenklu)";
            return 1;
        }
    }
    for (int i = 0; i < darbDienSk; i++){
        for (int j = 0; j < asmenuSk; j++){
            skaityti >> skaicius;
            darbininkas[j].darbas += skaicius;
        }
    }
    skaityti.close();

    int isVisoUzdirbtaLt = 0;
    int isVisoUzdirbtaCt = 0;
    for (int i = 0; i < asmenuSk; i++){
        uzdarbioSkaiciavimas(darbininkas[i]);
        isVisoUzdirbtaLt += darbininkas[i].visasUzdarbisLt;
        isVisoUzdirbtaCt += darbininkas[i].visasUzdarbisCt;
        if (isVisoUzdirbtaCt >= 100){
            isVisoUzdirbtaLt += isVisoUzdirbtaCt/100;
            isVisoUzdirbtaCt = isVisoUzdirbtaCt%100;
        }
        for (int j = 1; j < VARDO_ILGIS; j++){
            rasyti << darbininkas[i].vardas[j];
        }
        rasyti.width(3);
        rasyti << right << darbininkas[i].visasUzdarbisLt << " Lt ";
        rasyti.width(2);
        rasyti << right << darbininkas[i].visasUzdarbisCt << " ct\n";
    }
    rasyti << "Is viso: " << isVisoUzdirbtaLt << " Lt " << isVisoUzdirbtaCt << "ct";

    return 0;
}
