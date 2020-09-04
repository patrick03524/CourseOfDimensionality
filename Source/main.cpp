#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>
using namespace std;
#define T 25000
#define D 20

unsigned long inicio, fin, t;
///vector<vector<int>> vector_4,vector_6,vector_8,vector_10,vector_18,vector_20;
vector<vector<int>> vector_iwi;

void crear_vectores(int tamanho, int dimension){
	srand(time(NULL));
	int numero_aleatorio;
	for(int i = 0; i<tamanho; i++){
		vector<int> temp;
		for(int j = 0; j<dimension; j++){
			numero_aleatorio = 1 + rand() % (101 - 1);  ///numeros entre 1-100
			temp.push_back(numero_aleatorio);
		}
		vector_iwi.push_back(temp);
	}
}

void print_Vector(int tamanho, int dimension){
	for(int i = 0; i<tamanho; i++){
		for(int j = 0; j<dimension; j++){
			cout<<vector_iwi[i][j]<<" ";
		}
		cout<<endl;
	}
}

int distancia_euclidiana(int tamanho, int dimension){
	for(int i = 0; i<tamanho; i++){
		for(int j = i+1; j<tamanho; j++){
			double karma = 0;
			for(int k = 0; k<dimension; k++){
				karma +=pow((vector_iwi[j][k])-(vector_iwi[i][k]),2);
				///cout<<"x2-x1 al cuadrado: "<<karma<<endl;
			}
			karma = sqrt(karma);
			///cout<<"Distancia Euclidiana:"<<karma<<" entre los vectores "<<i<<" y "<<j<<endl;
			karma = 0;
		}
	}
	return 0;
}

int main(int argc, char *argv[]) {
	cout<<"Bienvenido a Estructuras de Datos Avanzadas"<<endl;
	cout<<"Primer Trabajo"<<endl;
	const int tamanho1 = 10000, dimension1 = 4;
	///const int tamanho1 = 10000, tamanho2 = 15000, tamanho3 = 20000, tamanho=25000;
	///const int dimension1 = 4, dimension2 = 6, dimension3 = 8, dimension4 = 10, dimension5 = 18, dimension6 = 20;
	///const int tamanho[4] = {10000,15000,20000,25000};
	///const int dimension[6] = {4,6,8,10,18,20};
	///Total de 24 vectores.
	///crear_vectores(tamanho[0], dimension[0]);
	crear_vectores(tamanho1,dimension1);
	///print_Vector(tamanho1,dimension1);
	inicio = clock();
	distancia_euclidiana(tamanho1,dimension1);
	fin = clock();
	double t = (double(fin - inicio) / CLOCKS_PER_SEC);
	cout << "Tiempo: " << t << " seg" << endl;
	return 0;
}

