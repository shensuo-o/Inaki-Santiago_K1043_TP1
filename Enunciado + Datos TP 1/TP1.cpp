#include <iostream>
#include <fstream>

using namespace std;

void mostrar(string vec[], int dim) //Mostrar vector de string.
{
	for (int i = 0; i < dim; ++i){
		cout << "vec[" << i << "]= " << vec[i] << endl;
	}
}

void mostrar(int vec[], int dim) //Mostrar vector de enteros.
{
	for (int i = 0; i < dim; ++i){
		cout << "vec[" << i << "]= " << vec[i] << endl;
	}
}

void mostrar(float vec[], int dim) //Mostrar vector de floats.
{
	for (int i = 0; i < dim; ++i){
		cout << "vec[" << i << "]= " << vec[i] << endl;
	}
}

void mostrarmat(float m[][5], int dfil) //Mostrar matriz de float.
{
	const int dcol = 5; 

	for (int i = 0; i < dfil; ++i) {
		for (int j = 0; j < dcol; ++j){
			cout << m[i][j] << '\t';
		}
		cout << endl;
	}

}

int maximo(int vec[], int dim) //Encontrar el maximo en un vector de enteros.
{
	int max = vec[0];
	int imax = 0;

	for (int i = 1; i < dim; i++){
		if (vec[i] > max) {
			max = vec[i];
			imax = i;
		}
	}
	return imax;
}

float maximo(float vec[], int dim) //Encontrar el maximo en un vector de floats.
{
	float max = vec[0];
	float imax = 0;

	for (int i = 1; i < dim; i++){
		if (vec[i] > max) {
			max = vec[i];
			imax = i;
		}
	}
	return imax;
}

void ordenar(float v[], int tam[], int dim) //Ordenar un vector (ascendente).
{
	int i;
	int pos; 
	int imin; 
	int temp;

	for (pos = 0; pos < dim - 1 ; pos++) {
		imin = pos;

		for (i = pos + 1 ; i < dim ; i++){

			if (v[i] < v[imin]){
				imin = i;
			}
		}
		swap(v[pos], v[imin]);
		swap(tam[pos], tam[imin]);
	}
}

int main()
{
    const int nclie = 8;
	const int nprod = 5;

    string clientes[nclie]; //nombre de los clientes.
	string productos[nprod]; //nombre de los productos.
	int indiceProd[nprod]{0, 1, 2, 3, 4}; //indice del vector de productos.

    float peso[nclie][nprod] {}; //total del peso por Cliente/Producto.
    float distancia[nclie][nprod]{}; //total de distancia recorrida por Cliente/Producto.
    int envios[nprod]{}; //envios realizados por producto.
	int enviosPeso[nclie]{}; //envios arriba de 13k KG por Cliente.
	float enviosDist[nprod]{}; //lista de disctancia de envios del cleinte con mas productos por arriba de 13k KG.
	
    //Lee el archivo de nombres, de Clientes y Productos.
	ifstream archilec;
	archilec.open("Nombres.txt");
	if (!archilec) {
		cout << "Error al tratar de abrir el archivo de nombres" << endl;
		return 1;
	}

	for (int i = 0; i < nclie && archilec >> clientes[i]; ++i);
	for (int i = 0; i < nprod && archilec >> productos[i]; ++i);

	cout << "\n====================================================\n" << endl;
	mostrar(clientes, nclie);
	cout << "\n====================================================\n" << endl;
	mostrar(productos, nprod);
    
	archilec.close();

    //Lee el archivo con los datos de envios.
	archilec.open("Datos.txt");
	if (!archilec) {
		cout << "Error al tratar de abrir el archivo de producción" << endl;
		return 1;
	}

	int ifil; 
	int icol; 
	float cant;
    float dist;
	
	while (archilec >> ifil >> icol >> cant >> dist) {
		peso[ifil][icol] += cant;
        distancia[ifil][icol] += dist;
		envios[icol]++;
	}
	archilec.close();

	cout << "\n=================Peso Cliente/Producto================\n" << endl;
	mostrarmat(peso, nclie);

    cout << "\n===============Distancia Cliente/Producto=============\n" << endl;
	mostrarmat(distancia, nclie);

	cout << "\n=====================Cant. Envios=====================\n" << endl;
	mostrar(envios, nprod);
	cout << endl;
	cout << "\n======================================================\n" << endl;

    //Punto 1=================================================================
    const int param = 13000;
	int cont = 0;

	cout << "Punto 1 -- Listado por clientes, de los tipos de productos que superen los 13000 Kg acumulados: " << endl;

    for (int i = 0; i < nclie; ++i){
		cout << clientes[i] << ": ";

		for (int j = 0; j < nprod; ++j){

            if (peso[i][j] > param){
				cout << productos[j] << ", ";
				++cont;
            }
        }
		enviosPeso[i] = {cont};
		cont = 0;
		cout << endl;
    }
	cout << "\n======================================================\n" << endl;

    //Punto 2=================================================================

	cout << "Punto 2 -- Listado de Km recorridos por tipo de producto: " << endl;

	int masEnv;
	masEnv = maximo(enviosPeso, nclie);

	for (int i = 0; i < nprod; ++i){
		enviosDist[i] = distancia[masEnv][i];
	}

	ordenar(enviosDist, indiceProd, nprod);

	for (int i = 0; i < nprod; ++i){
		cout << productos[indiceProd[i]] << ": " << enviosDist[i] << "Km" << endl;
	}
	cout << "\n======================================================\n" << endl;

	//Punto 3=================================================================

	int masRec;
	masRec = maximo(enviosDist, nprod);

	cout << "Punto 3: " << endl;
	cout << "Cantidad de entregas para el tipo de producto " << productos[indiceProd[masRec]] << " es: " << envios[indiceProd[masRec]] << endl;
	cout << "\n======================================================\n" << endl;

    return 0;
}