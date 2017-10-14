#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Reisas{
    Reisas(): keleiviu(0), balansas(0){}
    int keleiviu; ///Visu ilipusiu suma
    vector<int> balansas; ///prideda jei keleivis ilipa, atima, jei islipa
};

struct Stotele{
    Stotele(): ilipo(0), islipo(0){}
    string pavadinimas;
    int ilipo;
    int islipo;
};

int main()
{
    ifstream skaityti ("auto_duom.txt");
    ofstream rasyti ("auto_rez.txt");
    int stoteliu, reisu;
    int skaicius;
    int stotDaugIlipe = 0, stotDaugIslipe = 0;
    int reisDaugIlipe = 0; ///Naudojamas surandant kuriuose reisuose ilipo daugiausiai zmoniu
    int didzBalansas = 0; ///Laiko autobuse vienu metu esanciu zmoniu skaiciu
    skaityti >> reisu >> stoteliu;
    Stotele stotis[stoteliu];
    Reisas reisas[reisu];

    for (int i = 0; i < stoteliu; i++){
        skaityti >> stotis[i].pavadinimas;
    }
    for (int i = 0; i < reisu; i++){
        for (int j = 0; j < stoteliu; j++){
            skaityti >> skaicius;
            stotis[j].ilipo += skaicius; ///Skaiciuojami zmones ilipe is tam tikru stoteliu
            reisas[i].keleiviu += skaicius; ///skaiciuojama kiek isviso zmoniu ilipo i autika per reisa
            reisas[i].balansas.push_back(skaicius); ///Skaiciuojamas zmoniu ilipusiu ir islipusiu balansas, su vektoriais truputy sudetingiau,
            if (j != 0){                            ///nes reikia sekanciai veiktoriaus vietai prideti senesnes vietos skaiciu
                reisas[i].balansas[j] += reisas[i].balansas[j-1];
            }
            skaityti >> skaicius;
            stotis[j].islipo += skaicius; ///Skaiciuojami zmones islipe i tam tikras stoteles
            reisas[i].balansas[j] -= skaicius;
            if (reisas[i].balansas[j] > didzBalansas){
                didzBalansas = reisas[i].balansas[j];
            }
        }
        if (reisas[i].keleiviu > reisDaugIlipe){
            reisDaugIlipe = reisas[i].keleiviu;
        }
    }

    for (int i = 0; i < stoteliu; i++){
        if (stotis[i].ilipo > stotDaugIlipe){
            stotDaugIlipe = stotis[i].ilipo;
        }
        if (stotis[i].islipo > stotDaugIslipe){
            stotDaugIslipe = stotis[i].islipo;
        }
    }
    rasyti << "Daugiausia keleiviu: " << reisDaugIlipe << endl;
    for (int i = 0; i < reisu; i++){
        if (reisas[i].keleiviu == reisDaugIlipe){
            rasyti << i+1 << " ";
        }
    }
    rasyti << "\n\n";
    rasyti << didzBalansas << "\n";
    for (int i = 0; i < reisu; i++){
        for (int j = 0; j < stoteliu; j++){
            if (reisas[i].balansas[j] == didzBalansas){
                rasyti << i+1 << " " << stotis[j].pavadinimas << endl;
            }
        }
    }
    rasyti << "\n";
    rasyti << "Daugiausia ilipo per pamaina: " << stotDaugIlipe << ", stotelese:" << endl;
    for (int i = 0; i < stoteliu; i++){
        if (stotis[i].ilipo == stotDaugIlipe){
            rasyti << "\t" << stotis[i].pavadinimas << endl;
        }
    }
    rasyti << "\n";
    rasyti << "Daugiausia islipo per pamaina: " << stotDaugIslipe << ", stotelese:" << endl;
    for (int i = 0; i < stoteliu; i++){
        if (stotis[i].islipo == stotDaugIslipe){
            rasyti << "\t" << stotis[i].pavadinimas << endl;
        }
    }
    rasyti << "\n";
    rasyti << "Pasibaigus pamainai islipo: " << reisas[reisu-1].balansas[stoteliu-1];
    return 0;
}
