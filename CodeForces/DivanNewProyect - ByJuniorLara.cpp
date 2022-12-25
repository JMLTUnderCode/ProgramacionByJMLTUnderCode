/*
	Nombre: Junior Miguel Lara Torres
	Carnet: 1710303
	Nick: JMLTUnderCode
	
	Idea General:
	
	Para el arreglo de a_i dado, lo ordenamos, elegimos una posicion para la sede
	principal que se centra en el intervalo [0,n], es decir n+1/2. Esto permite
	distribuir las coordenadas a los edificios de manera optima, ya que es mejor tener
	la sede centrica a un borde. Para todas las posiciones de los edicios restamos la
	posicion de la sede ( esto para calcular |x_0 - x_i| ), dicho arreglo lo ordenamos
	entonces, ejemplo
	
	Visitas   = 1 5 10 15 20
	x_0 - x_i = 1 1  2  2  3
	
	Esto dice que para la distantia MAS LARGA x_0 - x_i se le asigna la cantidad de
	visitas MAS CORTA, con esto optimizamos la distribucion de coordenadas. 
*/
 
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
 
using namespace std;

//  Permite mostrar por pantalla un arreglo/vector
void print_vector(vector<int> &A) {
	for (int i=0 ; i<A.size() ; i++)
		cout << A[i] << " ";
	cout << endl;
}
 
// Permite realizar un ordenamiento ascendente sobre un arreglo/vector
vector<long long> counting_sort(vector<int> A, vector<long long> S, vector<int> &index) {
 
	int m = A[0], n = A.size();
	vector<int> ind(n);
	
	for ( int i = 1; i < n; i++)
		m = max(m, A[i]);
	
	vector<long long> accum(m+1, 0);
	vector<long long> R(n);
		
	for ( int i = 0; i < n; i++ )
		accum[A[i]]++;
	
	for ( int i = 1; i <= m; i++ )
		accum[i] += accum[i-1];
		
	for ( int i = n-1; i >= 0; i-- ) {
		accum[A[i]]--;
		R[accum[A[i]]] = S[i];
		ind[accum[A[i]]] = index[i];
	}
	index = ind;
	return R;
}

// Permite realizar un ordenamiento ascendente sobre un arreglo/vector
void radix_sort(vector<long long> &A, vector<int> &index) {
	
	int n = A.size(), d = 1;
	long long m = A[0];
	
	vector<int> dig(n);
	vector<long long> R(A);
	
	for ( int i = 1; i < n; i++) {
		m = max(m, A[i]);
	}
	
	while ( m >= d ) {
		for ( int i=0; i<n; i++ )
			dig[i] = ( R[i]/d ) % 10;
		R = counting_sort(dig, R, index);
		/*cout << endl;
		print_vector(R);
		print_vector(index);*/
		d *= 10;
	}
	A = R;
}

// Permite determinar un arreglo/vector de posiciones x_i para los edificios.
vector<int> Loc_apartment(int campus, int len) {
	vector<int> L(len);
	for( int k = 0; k < len; k++ ) {
		if( k < campus ) {
			L[k] = k;
		} else {
			L[k] = k+1;
		}
	}
	return L;
}
 
int main(){
	
	/* Inicializacion de Variables */
	int t; // Precondicion: 1 <= t <= 1000
	int n; // Precondicion: 0 <= n <= 2*10^5
 
	cin >> t;
	while( t-- > 0  ) {
		cin >> n;
		
		vector<long long> a_i(n);// Precondicion: 0 <= a_i <= 10^6
		for ( int k = 0; k < n; k++ ) {
			cin >> a_i[k];
		}
		
		// Elegimos una coordenada para la Cede Principal de Divan
		int Loc_campus = (n+1)/2; 
		
		// Formamos el arreglo de coordenadas para los edificios sin la Sede
		vector<int> apartments = Loc_apartment(Loc_campus, n);

		vector<long long> x_0_x_i(n);
		vector<int> a_i_index(n), x_0_x_i_index(n);
		
		for( int k = 0; k < n; k++ ) {
			
			// Una vez determinada la localizacion del campus lo restamos con 
			// todas las n localizacion para los edificios, esto calcula |x_0 - x_i|.
			x_0_x_i[k] = abs(Loc_campus - apartments[k]); 
			
			// Creamos un vector de indices tanto para a_i como |x_0 - x_i|
			// estoy permite que al realizar sorting sobre el vector principal
			// veamos como se mueven a nivel de indice dichos valores en el sort.
			x_0_x_i_index[k] = k;
			a_i_index[k] = k;
		}
		
		// Aplicamos Algoritmo de ordenamiento tanto a los A_i como a |x_0 - x_i|
		radix_sort(a_i, a_i_index);
		radix_sort(x_0_x_i, x_0_x_i_index);

		// Inicilizamos variables y guardamos la posicion de la Sede Principal
		vector<int> R(n+1,0);
		R[0] = Loc_campus;
		unsigned long long minutes = 0;
		
		for(int k = 0; k < n; k++){
			// Calculamos los minutos optimos para Divan
			minutes += 2*x_0_x_i[k]*a_i[n-1-k];
			
			// Asignamos las localizaciones de los edificios
			R[ a_i_index[n-1-k] + 1 ] = apartments[x_0_x_i_index[k]];
		}
		
		cout << minutes << endl;
		print_vector(R);
	}
		
	return 0;
}
