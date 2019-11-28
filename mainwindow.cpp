#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString te = ui->textEdit->toPlainText();
    ui->textSalida->setText(te);
    ofstream arch;
    arch.open("C:\\Users\\owena\\Downloads\\labmavis.txt", ios::out);//Aqui reemplacen la ruta del archivo de su proyecto
    if(arch.fail()){
       cout<<"Hubo un problema al guardar el archivo :("<<endl;
    }
    //for(int i = 0; i < texto.size(); i++) {
       //arch<<texto[i]<<endl;
    string data = te.toUtf8().constData();
       arch<<data;
    //}
        arch.close();

        string texto;
        vector<vector<int>> matriz;
        int j = 0;
        int sum = 0;
        int x;
        int p = 0, a, b, c, d;
        ifstream inFile;
        inFile.open("C:\\Users\\owena\\Downloads\\labmavis.txt", ios::in);
        if (!inFile) {
            cout << "El archivo no pudo ser encontrado :(";
            exit(1);
        }
        cout<<"Mapa:"<<endl;
        while (!inFile.eof()) {
            //vector<int> linea;
            getline(inFile, texto);
            //cout << texto << endl;
            //cout << texto.length() << endl;
            matriz.push_back(vector<int>());
            for (int i = 0; i < texto.length(); i++) {
                //cout <<setw(4) <<setfill(' ')<<texto[i];
                if (texto[i] - 48 == 0) {
                    matriz[j].push_back(-1);
                    cout <<setw(4) <<setfill(' ')<<texto[i];
                }
                else if(texto[i] - 48 == 1) {
                    matriz[j].push_back(-2);
                    cout <<setw(4) <<setfill(' ')<<texto[i];
                }
                else if(texto[i] == 'F') {
                    matriz[j].push_back(-1);
                    c = i;
                    d = j;
                    cout <<setw(4) <<setfill(' ')<<texto[i];
                }
                else if(texto[i] == 'X') {
                    matriz[j].push_back(0);
                    a = i;
                    b = j;
                    cout <<setw(4) <<setfill(' ')<<texto[i];
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
        matriz[d][c] = -4;
        for (int k = p - 1; k > 0; k--) {
            if ((c+1 < matriz[0].size()) && matriz[d][c + 1] == k) {
                matriz[d][c + 1] = -5;
                c++;
            }
            else if ((c - 1 >= 0) && matriz[d][c - 1] == k) {
                matriz[d][c - 1] = -5;
                c--;
            }
            else if ((d + 1 < matriz.size()) && matriz[d + 1][c] == k) {
                matriz[d + 1][c] = -5;
                d++;
            }
            else if ((d - 1 >= 0) && matriz[d - 1][c] == k) {
                matriz[d - 1][c] = -5;
                d--;
            }
        }
        string datafinal = "";
        for (int y = 0; y < matriz.size(); y++) {
            for (int x = 0; x < matriz[y].size(); x++){
                if(matriz[y][x] == -5){
                    cout <<setw(4) <<setfill(' ')<<'.';
                    datafinal += '_';
                }
                else if(matriz[y][x] == -2){
                    cout <<setw(4) <<setfill(' ')<<1;
                    datafinal += '1';
                }
                else if(matriz[y][x] == 0){
                    cout <<setw(4) <<setfill(' ')<<'X';
                    datafinal += 'X';
                }
                else if(matriz[y][x] == -4){
                    cout <<setw(4) <<setfill(' ')<<'F';
                    datafinal += 'F';
                }
                else{
                    cout <<setw(4) <<setfill(' ')<<0;
                    datafinal += '0';
                }
                datafinal += ' ';
            }

            cout << endl;
            datafinal += '\n';
        }
        /*for (int y = 0; y < matriz.size(); y++) {
                        for (int x = 0; x < matriz[y].size(); x++){
                            cout <<setw(4) <<setfill(' ')<<matriz[y][x];
                            datafinal += strmatriz[y][x];
                        }
                        cout << endl;
                        datafinal += '\n';
                    }*/
        QString str = QString::fromUtf8(datafinal.c_str());
        ui->textSalida->setText(str);
        cout<<"La ruta mide: "<<p<<endl;
        cout<<"StreetLab Team 2019 \251";
}
