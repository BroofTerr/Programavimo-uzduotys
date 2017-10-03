#include <iostream>
#include <assert.h>
#include <fstream>
using namespace std;

int main()
{
    ifstream skaityti("duomenys.txt");
    int n;
    int vsk = 0; ///Laiko savyje kiek skaiciu yra 'vienisu'
    skaityti >> n;
    assert (n%2 != 0); ///Crashina jei skaicius yra lyginis

    int sk[n];
    for (int i = 0; i < n; i++){
        skaityti >> sk[i];

        assert (sk[i] > 0 && sk[i] < 1000); ///Crashina jei skaicius nera intervale (0;1000)
    }
    cout << endl;
    for (int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++){
            if (sk[i] == sk[j] && sk[i] != 0){ ///Pakeicia porinius skaicius i 0
                sk[i] = 0;
                sk[j] = 0;
            }
        }
    }
    for (int i = 0; i < n; i++){
        if (sk[i] != 0){ /// suskaiciuoja kiek 'vienisu' skaiciu
            vsk++;
        }
    }
    ofstream rasyti ("rezultatas.txt");
    assert (vsk == 1); ///Crashina jei yra daugiau negu 1 'vienisas' skaicius
    for (int i = 0; i < n; i++){
        if (sk[i] == 0){ /// suskaiciuoja kiek 'vienisu' skaiciu
            rasyti << sk[i];
        }
    }

    return 0;
}
