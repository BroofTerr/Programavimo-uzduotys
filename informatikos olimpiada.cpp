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
    int dalyviuSk, uzduociu, minTasku;
    Dalyvis dalyvis[dalyviuSk];
    int skaicius;
    char raide;
    for (int i = 0; i < dalyviuSk; i++){
        for(int r = 0; r <= VARDO_ILGIS; r++){
            skaityti >> raide;
            dalyvis[i].vardasPav.push_back(raide);
        }
        ///Patikrinti del ilgio
        for (int j = 0; j < uzduociu; j++){
            skaityti >> skaicius;
            dalyvis[i].surinktaTasku.push_back(skaicius);
            dalyvis[i].visoTasku += skaicius;
        }
    }
    return 0;
}
