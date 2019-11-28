#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Mapa {
public:
	ifstream inFile;
	vector<vector<int>> matriz;
	int j = 0;
	int sum = 0;
	int x;
	int p = 0, a, b, c, d;

	void imprimirMapa() {
		std::cout << "Mapa:" << endl;
		while (!inFile.eof()) {
			//vector<int> linea;
			getline(inFile, texto);
			//cout << texto << endl;
			//cout << texto.length() << endl;
			matriz.push_back(vector<int>());
			for (int i = 0; i < texto.length(); i++) {
				cout << setw(4) << setfill(' ') << texto[i];
				if (texto[i] - 48 == 0)
					matriz[j].push_back(-1);
				else if (texto[i] - 48 == 1)
					matriz[j].push_back(-2);
				else if (texto[i] == 'F') {
					matriz[j].push_back(-1);
					c = i;
					d = j;
				}
				else if (texto[i] == 'X') {
					matriz[j].push_back(0);
					a = i;
					b = j;
				}
			}
			cout << endl;
			j++;
		}
	}
}
void calcularRuta() {
	do {
		for (int y = 0; y < matriz.size(); y++) {
			for (int x = 0; x < matriz[y].size(); x++) {
				if (matriz[y][x] == p) {
					if ((x + 1 < matriz[0].size()) && matriz[y][x + 1] == -1)
						matriz[y][x + 1] = p + 1;
					if ((x - 1 >= 0) && matriz[y][x - 1] == -1)
						matriz[y][x - 1] = p + 1;
					if ((y + 1 < matriz.size()) && matriz[y + 1][x] == -1)
						matriz[y + 1][x] = p + 1;
					if ((y - 1 >= 0) && matriz[y - 1][x] == -1)
						matriz[y - 1][x] = p + 1;
				}
			}
		}
		p++;
		///////
		for (int y = 0; y < matriz.size(); y++) {
			for (int x = 0; x < matriz[y].size(); x++) {
				cout << setw(4) << setfill(' ') << matriz[y][x];
			}
			cout << endl;
		}
		cout << endl;
	} while (matriz[d][c] == -1);
	cout << endl << "Mapa con ruta:" << endl;
	matriz[d][c] = -4;
	for (int k = p - 1; k > 0; k--) {
		if ((c + 1 < matriz[0].size()) && matriz[d][c + 1] == k) {
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

	for (int y = 0; y < matriz.size(); y++) {
		for (int x = 0; x < matriz[y].size(); x++) {
			if (matriz[y][x] == -5)
				cout << setw(4) << setfill(' ') << '.';
			else if (matriz[y][x] == -2)
				cout << setw(4) << setfill(' ') << 1;
			else if (matriz[y][x] == 0)
				cout << setw(4) << setfill(' ') << 'X';
			else if (matriz[y][x] == -4)
				cout << setw(4) << setfill(' ') << 'F';
			else
				cout << setw(4) << setfill(' ') << 0;
		}
		cout << endl;
	}
}
void mostrarResultado() {
	cout << "La ruta mide: " << p << endl;
	cout << "StreetLab Team 2019 \251";
}
~Mapa() {}
}

class Archivo {
private:
	string ruta;
public:
	archivo() {}
	void setRuta() {
		string _ruta;
		cout << "Ingrese la ruta donde se encuentra el archivo. La sintaxis es: [Ejemplo]" << endl;
		cout << "C:\\Users\\nombre_del_usuario\\Downloads\\mapa.txt" << endl;
		cin >> _ruta;
		ruta = _ruta;
	}

	void abrirMapa() {
		inFile.open("C:\\Users\\Javier Chavez\\Downloads\\labmavis.txt", ios::in);
		if (!inFile) {
			cout << "El archivo no pudo ser encontrado :(";
			exit(1);
		}
	}

	void cerrarMapa() {
		inFile.close();
	}
	~Archivo() {}
}

int main() {
	Archivo archivo;
	Mapa mapa;

	archivo.setRuta();
	archivo.abrirMapa();
	mapa.imprimirMapa();
	mapa.calcularRuta();
	mapa.mostrarResultado();
	archivo.cerrarMapa();
} 
