#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    int vaikaiA, vaikaiN, obuoliuPerdavimas, ismainytuObuoliu = 0;
    ifstream skaityti("gentys_duom.txt");
    skaityti >> vaikaiA >> vaikaiN;
    int obuoliuSk = 0, riesutuSk[vaikaiN];
    bool galiKeistis = true;
    for (int i = 0; i < vaikaiA; i++){ ///read from file later
        skaityti >> obuoliuPerdavimas; ///used to help putting the apples into one var
        obuoliuSk += obuoliuPerdavimas;
    }
    for (int i = 0; i < vaikaiN; i++){ ///read from file later
        skaityti >> riesutuSk[i];
    }
    skaityti.close();
    for (int i = 0; i < vaikaiN; i++){ ///checks if there are enough nuts to trade for an apple on one person per time
        while (riesutuSk[i] >= 3 && obuoliuSk > 0){
            ismainytuObuoliu++;
            obuoliuSk--;
            riesutuSk[i] -= 3;
        }
        if (i == vaikaiN-1){
            galiKeistis = false;
        }
    }
    ofstream rasyti ("gentys_rez.txt");
    rasyti << ismainytuObuoliu << endl;
    return 0;
}
