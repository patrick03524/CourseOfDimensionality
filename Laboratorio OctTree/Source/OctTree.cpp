// OctTree.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
using namespace std;

#define tamanho 8
#define min 1	///Minimo 1 px

template<class T>
class Punto {
public:
	T x, y, z;
	Punto(T a, T b, T c) {
		x = a;
		y = b;
		z = c;
	}
	Punto(Punto<T>* pt) {
		x = pt.x;
		y = pt.y;
		z = pt.z;
	}
};

template<class T>
class Nodo {
public:
	Punto<T>* coords;
	bool color;						//0 si es negro(Todos sus hijos están ocupados) y 1 si no es negro (Aún hay espacio para más nodos
	Punto<T> bounding_box[2];
	Nodo<T>* hijos[8];				//Cada Nodo tendra 8 Hijos
	Nodo(Punto<T> a, Punto<T> b) {
		bounding_box[0] = a;
		bounding_box[1] = b;
		for (int i = 0; i < 8; ++i) {
			hijos[i] = nullptr;
		}
		color = 0;
		coords = new Punto<T>(a);		//Nodo no Hoja
		if (b.x - a.x <= min && b.y - a.y <= min && b.z - a.z <= min) {
			color = 1;
			coords = nullptr;
			cout << "Nodo Negro Hoja Inicializado" << endl;
		}
	}
};

template<class T>
class OctTree {
public:
	Nodo<T>* root;
	T m_x, m_y, m_z;
	OctTree(Punto<T> Min_Pt, Punto<T> Max_Pt) {
		root = new Nodo<T>(Min_Pt, Max_Pt);
		m_x = (Max_Pt.x + Min_Pt.x) / 2;
		m_y = (Max_Pt.y + Min_Pt.y) / 2;
		m_z = (Max_Pt.z + Min_Pt.z) / 2;
	}
	bool find(Nodo<T> * &t, Punto<T> val, int &index) {
		T val_x = val.x;
		T val_y = val.y;
		T val_z = val.z;
		if (val_x < root->bounding_box[0].x || val_x > root->bounding_box[1].x ||
			val_y < root->bounding_box[0].y || val_y > root->bounding_box[1].y ||			
			val_z < root->bounding_box[0].z || val_z > root->bounding_box[1].z) {
			cout << "Out of Range" << endl;		//En el caso si queremos insertar un Punto que no este dentro del dominio de todos los puntos
			return 0;							//Aunque esto no debería de cumplirse si se extraen todos los puntos de un archivo .obj
		}
		t = root;
		index = -1;
		if (val_x <= m_x) {
			if (val_y <= m_y) {
				if (val_z <= m_z) {
					index = 0;
				}
				else {
					index = 4;
				}
			}
			else {
				if (val_z <= m_z) {
					index = 3;
				}
				else {
					index = 7;
				}
			}
		}
		else {
			if (val_y <= m_y) {
				if (val_z <= m_z) {
					index = 1;
				}
				else {
					index = 5;
				}
			}
			else {
				if (val_z <= m_z) {
					index = 2;
				}
				else {
					index = 6;
				}
			}
		}
		if (t->hijos[index] == nullptr) {
			return 0;
		}
		for (; t; t = t->hijos[index]) {
			if (t->hijos[index] && t->color == 0 && t->coords && t->coords->x == val_x && t->coords->y == val_y && t->coords->z == val_z) {
				return 1;
			}
		}
		return 0;
		/*
		Zonas
		Ejemplo: (0,0,0) - (4,4,4)
		root -> [(0,0,0),(4,4,4)]
		a0 ->[(0,2,0),(2,4,2)] -> 0
		a1 ->[(2,2,0),(4,4,2)] -> 1
		a2 ->[(0,0,0),(2,2,2)] -> 2
		a3 ->[(2,0,0),(4,2,2)] -> 3
		a4 ->[(0,0,2),(2,2,4)] -> 4
		a5 ->[(2,0,2),(4,2,4)] -> 5
		a6 ->[(0,2,2),(2,4,4)] -> 6
		a7 ->[(2,2,2),(4,4,4)] -> 7

		Cada nodo hoja tendra de espacio de 1(min)

		*/
	}

	bool insert(T a, T b, T c) {
		Punto<T>* temporal = new Punto<T>(a, b, c);
		Nodo<T>* r;
		int index;
		if (find(r, *temporal, index)) {
			cout << "Nodo ya creado anteriormente" << endl;
			return 0;
		}
		T x_a = r->bounding_box[0].x;
		T x_b = r->bounding_box[0].y;
		T x_c = r->bounding_box[0].z;
		T y_a = r->bounding_box[1].x;
		T y_b = r->bounding_box[1].y;
		T y_c = r->bounding_box[1].z;
		T m_a = (x_a + y_a) / 2;
		T m_b = (x_b + y_b) / 2; 
		T m_c = (x_c + y_c) / 2;
		
		r->hijos[0] = new Nodo<T>(Punto<T>(x_a, m_b, x_c), Punto<T>(m_a, y_b, m_c));		//a0 ->[(0, 2, 0), (2, 4, 2)] -> 0
		r->hijos[1] = new Nodo<T>(Punto<T>(m_a, m_b, x_c), Punto<T>(y_a, y_b, m_c));		//a1 ->[(2, 2, 0), (4, 4, 2)] -> 1
		r->hijos[2] = new Nodo<T>(Punto<T>(x_a, x_b, x_c), Punto<T>(m_a, m_b, m_c));		//a2 ->[(0, 0, 0), (2, 2, 2)] -> 2
		r->hijos[3] = new Nodo<T>(Punto<T>(m_a, x_b, x_c), Punto<T>(y_a, m_b, m_c));		//a3 ->[(2, 0, 0), (4, 2, 2)] -> 3
		r->hijos[4] = new Nodo<T>(Punto<T>(x_a, x_b, m_c), Punto<T>(m_a, m_b, y_c));		//a4 ->[(0, 0, 2), (2, 2, 4)] -> 4
		r->hijos[5] = new Nodo<T>(Punto<T>(m_a, x_b, m_c), Punto<T>(y_a, m_b, y_c));		//a5 ->[(2, 0, 2), (4, 2, 4)] -> 5
		r->hijos[6] = new Nodo<T>(Punto<T>(x_a, m_b, m_c), Punto<T>(m_a, y_b, y_c));		//a6 ->[(0, 2, 2), (2, 4, 4)] -> 6
		r->hijos[7] = new Nodo<T>(Punto<T>(m_a, m_b, m_c), Punto<T>(y_a, y_b, y_c));		//a7 ->[(2, 2, 2), (4, 4, 4)] -> 7
		//Nodo<T> *nodo = New Nodo();

		return 1;
	}

};

int main()
{
	cout << "Laboratorio Oct Tree" << endl;
	Punto<double> pt1(0.0, 0.0, 0.0);
	Punto<double> pt2(4.0, 4.0, 4.0);
	OctTree<double> o(pt1, pt2);

	Punto<double> pt3(0.0, 0.0, 0.0);
	Punto<double> pt4(1.0, 1.0, 1.0);
	if (o.insert(0.0, 0.0, 0.0)) {
		cout << "Nodo Ingresado Correctamente" << endl;
	}
	o.insert(1.0, 1.0, 1.0);
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
