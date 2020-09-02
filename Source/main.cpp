#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> vector_4,vector_6,vector_8,vector_10,vector_18,vector_20;

void crear_vectores(int tamanho, int dimension){
	srand(time(NULL));
	int numero_aleatorio;
	for(int i = 0; i<dimension; i++){
		for(int j = 0; j<tamanho; j++){
			numero_aleatorio = 1 + rand() % (101 - 1);  ///numeros entre 1-100
		}
	}
}

int distancia_euclidiana(int n){
	return 0;
}

int main(int argc, char *argv[]) {
	cout<<"Bienvenido a Estructuras de Datos Avanzadas"<<endl;
	cout<<"Primer Trabajo"<<endl;
	return 0;
}

