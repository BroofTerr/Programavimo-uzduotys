#include <iostream>
#include <fstream>

using namespace std;

struct Temperatura{
    int vidTemp;
    int vidSleg;
} lygTemp;

void tenkinaSalyga(Temperatura &lygTemp, Temperatura &temp, int &tenkinanciu){
    if (temp.vidTemp > lygTemp.vidTemp && temp.vidSleg <= lygTemp.vidSleg)
        tenkinanciu++;
}

int main()
{
    ifstream skaityti("orai_duom.txt");
    ofstream rasyti("orai_rez.txt");
    int tempKriterijai, slegKriterijai, n;
    int tenkinanciu = 0;
    skaityti >> lygTemp.vidTemp;
    skaityti >> lygTemp.vidSleg;
    skaityti >> n;
    Temperatura temp[n];
    for (int i = 0; i < n; i++){
        skaityti >> temp[i].vidTemp;
        skaityti >> temp[i].vidSleg;
    }
    skaityti.close();
    for(int i = 0; i < n; i++){
        tenkinaSalyga(lygTemp, temp[i], tenkinanciu);
    }
    rasyti << tenkinanciu;

    return 0;
}
