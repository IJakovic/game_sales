#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <list>
#include <chrono>
#include <algorithm>
#include "VideoGame.h"

using namespace std;
using namespace std::chrono;

void title() {

    cout << R"(
   _________    __  ______________
  / ____/   |  /  |/  / ____/ ___/
 / / __/ /| | / /|_/ / __/  \__ \ 
/ /_/ / ___ |/ /  / / /___ ___/ / 
\____/_/  |_/_/  /_/_____//____/  
)" << '\n';
    cout << endl;
}

string getFileName(ifstream& in) {

    
    string line;
    string putanja; //putanja foldera
    string filename = "\\SPA_PROJ_006_GAME_SALES_data.csv";
    while (getline(in,line))
    {
        stringstream ss(line);
        getline(ss, putanja);  
    }
    return putanja+filename;
}

int convert_int(string& s)
{
    stringstream converter(s);
    int n;
    converter >> n;
    converter.ignore();
    return n;
}

float convert_float(string& s)
{
    stringstream converter(s);
    float n;
    converter >> n;
    converter.ignore();
    return n;
}

void load(ifstream& dat, vector<VideoGame>& v) {

    int rank;
    string name;
    string platform;
    int year;
    string genre;
    string publisher;
    float NA_sales;
    float EU_sales;
    float JP_sales;
    float other_sales;
    float global_sales;

    string line;
    string temp;
    getline(dat, line);
    while (getline(dat, line))
    {
        //cout << line << endl;
        stringstream ss(line);
        getline(ss, temp, ',');
        rank = convert_int(temp);
        getline(ss, name, ',');
        getline(ss, platform, ',');
        getline(ss, temp, ',');
        year = convert_int(temp);
        getline(ss, genre, ',');
        getline(ss, publisher, ',');
        getline(ss, temp, ',');
        NA_sales = convert_float(temp);
        getline(ss, temp, ',');
        EU_sales = convert_float(temp);
        getline(ss, temp, ',');
        JP_sales = convert_float(temp);
        getline(ss, temp, ',');
        other_sales = convert_float(temp);
        getline(ss, temp);
        global_sales = convert_float(temp);

        v.emplace_back(rank, name, platform, year, genre, publisher, NA_sales, EU_sales, JP_sales, other_sales, global_sales);
    }
}

void print(VideoGame &vg) {
    cout << vg.top_EU_to_string() << endl;
}

void loadStack(ifstream &dat, stack<string> &s) {

    string line;
    while (getline(dat, line))
    {
        s.push(line);
    }
}

void saveStack(ofstream &on, stack<string> &s) {

    while (!s.empty())
    {
        on << s.top() << endl;
        s.pop();
    }
}

void loadQueue(ifstream& dat, queue<string>& q) {

    string line;
    while (getline(dat, line))
    {
        q.push(line);
    }
}

void saveQueue(ofstream& on, queue<string>& q) {

    while (!q.empty())
    {
        on << q.front() << endl;
        q.pop();
    }
}

bool nasao(string name) {

    for (int i = 0; i < name.size(); i++)
    {
        if (name[i] == ':')
        {
            return true;
        }
    }
    return false;
}

void printl(VideoGame &vg) {
    cout << vg.list_to_string() << endl;
}

void histogram(int a, int b, int c, int d, int e) {

    cout << "0-9\t#";
    for (int i = 0; i < a / 10; i++)
    {
        cout << "#";
    }
    cout << "\t(" << a << ")" << endl;

    cout << "10-19\t#";
    for (int i = 0; i < b / 10; i++)
    {
        cout << "#";
    }
    cout << "\t(" << b << ")" << endl;

    cout << "20-39\t#";
    for (int i = 0; i < c / 10; i++)
    {
        cout << "#";
    }
    cout << "\t(" << c << ")" << endl;

    cout << "40-49\t#";
    for (int i = 0; i < d / 10; i++)
    {
        cout << "#";
    }
    cout << "\t(" << d << ")" << endl;

    cout << "50+\t#";
    for (int i = 0; i < e / 10; i++)
    {
        cout << "#";
    }
    cout << "\t(" << e << ")" << endl;
}

void input(vector<VideoGame>& v, stack<string>& s) {

    string command;
    string iznos;
    cout << "\nUNOS NAREDBE" << endl;
    cout << "Unesite pocetnu naredbu: ";
    getline(cin, command);
    if (command != "BEGIN TRAN")
    {
        return;
    }
    do
    {
        cout << "Unesite naredbu: ";
        getline(cin, command);

        if (command == "UPDATE SALES")
        {
            cout << "Iznos: ";
            getline(cin, iznos);
            s.push(iznos);
        }
        else if (command == "ROLLBACK")
        {
            if (!s.empty())
            {
                s.pop();
            }
        }
        else if (command == "COMMIT")
        {
            return;
        }
    } while (true);
}

void output(vector<VideoGame>& v, stack<string>& s, ofstream &on) {

    int rank;
    string name;
    string platform;
    int year;
    string genre;
    string publisher;
    float NA_sales;
    float EU_sales;
    float JP_sales;
    float other_sales;
    float global_sales;

    float set_sale = 0;
    string temp;
    

    stack<string> output;
    while (!s.empty())
    {
        output.push(s.top());
        s.pop();
    }

    while (!output.empty())
    {
        temp = convert_float(output.top());
        stringstream ss(temp);
        set_sale += convert_float(temp);
        output.pop();
    }

    for (auto it = v.begin(); it != v.end(); ++it)
    {
        it->set_global_sales(it->get_global_sales() + set_sale);
        on << it->to_string() << endl;
    }
}

int main() {

	title();
    
    cout << "UNOS PUTANJE" << endl;
    cout << "Unesite putanju datoteke: ";
    string putanja;
    getline(cin, putanja);

    //Spremiti putanju u binarnu datoteku
    ofstream bin("video_games.dat", ios_base::binary);
    if (!bin)
    {
        cout << "Dogodila se greska!" << endl;
        return 1;
    }
    bin << putanja;
    bin.close();


    cout << "\nUNOS PODATAKA IZ DATOTEKE" << endl;
    ifstream in("video_games.dat");
    if (!in)
    {
        cout << "Nije  moguce otvoriti datoteku." << endl;
        return 1;
    }

    //Otovoriti datoteku iz putanje binarne datoteke
    string fileName = getFileName(in);
    ifstream dat(fileName);
    if (!dat)
    {
        cout << "Nije moguce otvoriti datoteku." << endl;
        return 1;
    }


    vector<VideoGame> v;

    //Ucitavanje datoteke u vektor
    auto begin = high_resolution_clock::now();
    load(dat, v);
    auto end = high_resolution_clock::now();
    auto ms = duration_cast<milliseconds>(end - begin);
    unsigned long long trajanje = ms.count();
    cout << "Vrijeme parsiranja u vektor: " << trajanje << "ms" << endl;

 
    cout << "\nTOP 5 IZDAVACA" << endl;

    //Koristenje "Lambda expressions"
    auto sortEU = [](VideoGame &vg1, VideoGame &vg2) -> bool
    {
        return vg1.get_EU_sales() > vg2.get_EU_sales();
    };

    //Sortiranje i ispis top 10 EU_sales
    sort(v.begin(), v.end(), sortEU);
    for_each(v.begin(), v.begin() + 10, print);


    //Ispis igre koje se pojavljuju na vise od jedne platforme
    /*for (auto it = v.begin(); it < v.end(); it++)
    {                                                               //ne znam kako da dobijem igre koje imaju vise platformi
        
    }*/

    cout << "\nKOPIRANJE DATOTEKE" << endl;
    cout << "Zelite li prepisati iz datoteke u istom ili obrnutom redoslijedu?" << endl;
    cout << "(Isto = 0 / Obrnuto = 1): ";
    bool obrni;
    cin >> obrni;
    cin.ignore();
 
    cout << "Unesite putanju foldera gdje zelite spremiti: ";
    string spremi;
    getline(cin, spremi);

    cout << "Unesite naziv datoteke: ";
    string naziv;
    getline(cin, naziv);
    string saveFile = spremi + "\\" + naziv;

    ofstream on(saveFile); //spremanje datoteke u toj putanji
    if (!on)
    {
        cout << "Dogodila se greska." << endl;
        return 1;
    }

    ifstream read(fileName); //procitati originalni file
    if (!read)
    {
        cout << "Nije moguce otvoriti datoteku." << endl;
        return 1;
    }

    if (obrni)
    {
        stack<string> s;
        loadStack(read, s);
        saveStack(on, s);
    }
    else
    {
        queue<string> q;
        loadQueue(read, q);
        saveQueue(on, q);
    }
    dat.close();
    on.close();
    in.close();
    read.close();

    
    cout << "\nOBRADA PO PLATFORMAMA" << endl;
    cout << "Unesite naziv platforme: ";
    string namePlatform;
    getline(cin, namePlatform);

    list<VideoGame> l;
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        l.emplace_back(it->get_name(), it->get_platform(), it->get_global_sales());
    }

    for (auto it = l.begin(); it != l.end();)
    {
        if (it->get_platform() == namePlatform)
        {
            if (it->get_global_sales() < 2.5)  //ja sam stavio ovoliko jer ne vidim u file-i ni jedan game pod global sale koji ima preko 250000 USD
            {                                                   //osim ako je zadatak krivo napisan ili je datoteka malo kriva??? :smiley_face:
                it = l.erase(it);
            }
            else
            {
                ++it;
            }
        }
        else
        {
            it = l.erase(it);
        }
    }
    for_each(l.rbegin(), l.rend(), printl);


    //Pronaci dvotocke u naslovu
    cout << "\nISPIS NASLOVA NA STOGU" << endl;
    stack<string> naslovi;

    ofstream write("naslovi_stoga.txt");
    if (!write)
    {
        cout << "Dogodila se greska." << endl;
        return 1;
    }

    for (auto it = v.rbegin(); it != v.rend(); ++it)
    {
        if (nasao(it->get_name()))
        {
            naslovi.push(it->get_name());
        }
        else
        {
            if (naslovi.empty())
            {
                write << "Prazan stog" << endl;
            }
            else
            {
                write << naslovi.top() << endl;
                naslovi.pop();
            }
        }
    }

    if (naslovi.empty())
    {
        cout << "Na stogu nema nista." << endl;
    }
    write.close();


    cout << "\nSTATISTIKA IGARA" << endl;
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int e = 0;

    for (auto it = v.begin(); it != v.end(); it++)
    {
        if (it->get_global_sales() < 10)
        {
            a++;
        }
        else if (it->get_global_sales() < 20)
        {
            b++;
        }
        else if (it->get_global_sales() < 30)
        {
            c++;
        }
        else if(it->get_global_sales() < 50)
        {
            d++;
        }
        else
        {
            e++;
        }
    }
    //Ispis statitiske
    histogram(a, b, c, d, e);
    

    //Simuliranje transakcija pomocu naredbi na stogu
    ofstream trans("transakcija.txt");
    if (!trans)
    {
        cout << "Dogodila se greska." << endl;
        return 1;
    }
    stack<string> s;
    input(v, s);
    output(v, s, trans);
    trans.close();

	return 0;
}