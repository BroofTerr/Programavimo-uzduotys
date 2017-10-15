#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define KUBU_KOMPLEKTE 12
struct Pamainos{
    Pamainos(): likuciuSuma(0){}
    vector<int> likutis;
    int likuciuSuma;
    vector<int> pagamintaKubu;
    int komplektu;
};

int main()
{
    ifstream skaityti ("duomenys.txt");
    ofstream rasyti ("rezultatas.txt");
    int pamainu, pradinisLikutis[KUBU_KOMPLEKTE];
    int skaicius;
    int visoKomplektu = 0;
    int pagamintaKubu[KUBU_KOMPLEKTE]; ///Naudojamas randant didziausia galimu komplektu skaiciu
    skaityti >> pamainu;
    Pamainos pamaina[pamainu];
    for (int i = 0; i < KUBU_KOMPLEKTE; i++){
        skaityti >> pradinisLikutis[i];
    }
    for (int i = 0; i < pamainu; i++){
        for (int j = 0; j < KUBU_KOMPLEKTE; j++){
            skaityti >> skaicius;
            pamaina[i].pagamintaKubu.push_back(skaicius);
            if (i == 0){
                pamaina[i].pagamintaKubu[j] += pradinisLikutis[j];
            }
            else {
                pamaina[i].pagamintaKubu[j] += pamaina[i-1].likutis[j]; ///Prideda likusi likuti nuo praeitu darbininku naujiems darbininkams
            }
            pagamintaKubu[j] = pamaina[i].pagamintaKubu[j]; ///Perduoda reiksmes i masyva, pagal kury tikrinsim didziausia padarytu komplektu skaiciu per viena pamaina
        }
        pamaina[i].komplektu = *min_element(pagamintaKubu, pagamintaKubu+KUBU_KOMPLEKTE);
        visoKomplektu += pamaina[i].komplektu;
        for (int j = 0; j < KUBU_KOMPLEKTE; j++){
            pamaina[i].likutis.push_back(pamaina[i].pagamintaKubu[j] - pamaina[i].komplektu);
            pamaina[i].likuciuSuma += pamaina[i].likutis[j];
        }
        rasyti << i+1 << ". " << pamaina[i].likuciuSuma << " " << pamaina[i].komplektu << "\n";
    }

    rasyti << "\nPo paskutines pamainos liko nesukomplektuota: \n";
    for (int j = 0; j < KUBU_KOMPLEKTE; j++){
        rasyti << pamaina[pamainu-1].likutis[j] << " ";
    }
    rasyti << "\n\nIs viso pagaminti " << visoKomplektu << " rink.";

    return 0;
}
