#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
	const string cadena = "Llego a la estacion a las 16:50";
	
	//Conversion de la cadena a binario ASCII
	string binario;
	for (char a : cadena) {
		binario.append(bitset<7>(a).to_string());
	}
	//cout<<binario<<endl;
	
	vector<string> matrizParidad(0);
	int paridadVertical1s = 0;
	int paridadHorizontal1s = 0;
	
	//Añadidura de los bits de paridad impar al final de cada fila
	string substr;
	int contador1s = 0;
	
	for (unsigned int i=0; i<binario.length(); i++) {
		substr.push_back(binario[i]);
		binario[i] == '1' ? contador1s += 1 : contador1s += 0;
		
		if ((i+1) % 7 == 0) {
			if(contador1s % 2 == 0){
				substr.append("1") ;
				paridadHorizontal1s += 1;
			} else {
				substr.append("0");
			}
			contador1s = 0;

			matrizParidad.push_back(substr);
			substr = "";
		}
		
	}
	
	//Añadidura de los bits de paridad impar al final de cada columna menos la ultima
	string filaBitsParidadVertical;
	for (unsigned int j = 0; j < 7; j++) {
		int contBitsColumna = 0;
		for (unsigned int i = 0; i < (binario.length()/7); i++) {
			matrizParidad[i][j] == '1' ? contBitsColumna += 1 : contBitsColumna += 0;
		}
		if (contBitsColumna % 2 == 0 ){
			filaBitsParidadVertical.append("1");
			paridadVertical1s += 1;
		} else {
			filaBitsParidadVertical.append("0");
		}
	}
	//Una vez que la fila de bits de paridad esta armada la añado a la matriz de paridad
	matrizParidad.push_back(filaBitsParidadVertical);
	
	//Añado el bit de paridad entre la columna y la fila de paridad
	(paridadHorizontal1s+paridadVertical1s) % 2 == 0 ? matrizParidad[binario.length()/7].append("1") : 
													   matrizParidad[binario.length()/7].append("0");
	
	
	ofstream myfile;
	myfile.open ("resultadosParidad2.txt");
	//Muestro la cadena codificada
	for (unsigned int i = 0; i<matrizParidad.size(); i++) {
		myfile<<matrizParidad[i];
	}
	myfile.close();
	
	
	return 0;
}

