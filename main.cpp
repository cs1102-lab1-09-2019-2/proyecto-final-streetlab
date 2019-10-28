#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    cout<<" ad88888ba                                                         88                       88           \n"
          "d8\"     \"8b    ,d                                           ,d     88                       88           \n"
          "Y8,            88                                           88     88                       88           \n"
          "`Y8aaaaa,    MM88MMM  8b,dPPYba,   ,adPPYba,   ,adPPYba,  MM88MMM  88           ,adPPYYba,  88,dPPYba,   \n"
          "  `\"\"\"\"\"8b,    88     88P'   \"Y8  a8P_____88  a8P_____88    88     88           \"\"     `Y8  88P'    \"8a  \n"
          "        `8b    88     88          8PP\"\"\"\"\"\"\"  8PP\"\"\"\"\"\"\"    88     88           ,adPPPPP88  88       d8  \n"
          "Y8a     a8P    88,    88          \"8b,   ,aa  \"8b,   ,aa    88,    88           88,    ,88  88b,   ,a8\"  \n"
          " \"Y88888P\"     \"Y888  88           `\"Ybbd8\"'   `\"Ybbd8\"'    \"Y888  88888888888  `\"8bbdP\"Y8  8Y\"Ybbd8\"' "<<endl<<endl;
    string texto;
    vector<vector<int>> matriz;
    int j = 0;
    int sum = 0;
    int x;
    int p = 0, a, b, c, d;
    ifstream inFile;
    inFile.open("labmavis.txt", ios::in);
    if (!inFile) {
        cout << "El archivo no se encontro :(";
        exit(1); // terminate with error
    }
    cout<<"Mapa:"<<endl;
    while (!inFile.eof()) {
        //vector<int> linea;
        getline(inFile, texto);
        //cout << texto << endl;
        //cout << texto.length() << endl;
        matriz.push_back(vector<int>());
        for (int i = 0; i < texto.length(); i++) {
            cout <<setw(4) <<setfill(' ')<<texto[i];
            if (texto[i] - 48 == 0)
                matriz[j].push_back(-1);
            else if(texto[i] - 48 == 1)
                matriz[j].push_back(-2);
            else if(texto[i] == 'F') {
                matriz[j].push_back(-1);
                c = i;
                d = j;
            }
            else if(texto[i] == 'X') {
                matriz[j].push_back(0);
                a = i;
                b = j;
            }
        }
        cout<<endl;
        j++;
    }
    inFile.close();

    do{
        for (int y = 0; y < matriz.size(); y++) {
            for (int x = 0; x < matriz[y].size(); x++) {
                if (matriz[y][x] == p) {
                    if ((x+1 < matriz[0].size()) && matriz[y][x + 1] == -1)
                        matriz[y][x + 1] = p+1;
                    if ((x - 1 >= 0) && matriz[y][x - 1] == -1)
                        matriz[y][x - 1] = p+1;
                    if ((y + 1 < matriz.size()) && matriz[y + 1][x] == -1)
                        matriz[y + 1][x] = p+1;
                    if ((y - 1 >= 0) && matriz[y - 1][x] == -1)
                        matriz[y - 1][x] = p+1;
                }
            }
        }
        p++;
        ///////
        /*for (int y = 0; y < matriz.size(); y++) {
            for (int x = 0; x < matriz[y].size(); x++){
                cout <<setw(4) <<setfill(' ')<<matriz[y][x];
            }
            cout << endl;
        }
        cout << endl;*/
    }while(matriz[d][c] == -1);
    cout<<endl<<"Mapa con ruta:"<<endl;
    for (int k = p - 1; k > 0; k--) {
        if ((c+1 < matriz[0].size()) && matriz[d][c + 1] == k) {
            matriz[d][c + 1] = 1;
            c++;
        }
        else if ((c - 1 >= 0) && matriz[d][c - 1] == k) {
            matriz[d][c - 1] = 1;
            c--;
        }
        else if ((d + 1 < matriz.size()) && matriz[d + 1][c] == k) {
            matriz[d + 1][c] = 1;
            d++;
        }
        else if ((d - 1 >= 0) && matriz[d - 1][c] == k) {
            matriz[d - 1][c] = 1;
            d--;
        }
    }
    for (int y = 0; y < matriz.size(); y++) {
        for (int x = 0; x < matriz[y].size(); x++){
            if(matriz[y][x] == 1)
                cout <<setw(4) <<setfill(' ')<<'.';
            else if(matriz[y][x] == -2)
                cout <<setw(4) <<setfill(' ')<<1;
            else if(matriz[y][x] == 0)
                cout <<setw(4) <<setfill(' ')<<'X';
            else if(matriz[y][x] == p)
                cout <<setw(4) <<setfill(' ')<<'F';
            else
                cout <<setw(4) <<setfill(' ')<<0;
        }
        cout << endl;
    }
    cout<<"La ruta mide: "<<p<<endl;
    cout<<"StreetLab Team 2019 \251";
}
