#include <iostream>
#include "include/main.h"
#include "include/geometric_algebra.h"
#include "include/screw.h"
using namespace std;


int main()
{
	GeometricAlgebra ga(3);
	MultiVector s = ga[0];
	MultiVector e1 = ga[1];
	MultiVector e2 = ga[2];
	MultiVector e3 = ga[3];
	MultiVector e12 = ga[4];
	MultiVector e13 = ga[5];
	MultiVector e23 = ga[6];
	MultiVector e123 = ga[7];


	Screw myscrew(e23, e1, e1);
	return 0;
}




/* TESTS */
/*

Générer l'ensemble des partitions
---------------------------------
vector<int> input = {1, 2, 3};
vector< vector<int> > multivector;
 
for(int a: input)
{
	vector<int> tmp;
	tmp.push_back(a);

	for(int b: input)
	{
		multivector.push_back(tmp);
		tmp.push_back(b);
	}
	multivector.push_back(tmp);
	
}

Afficher un vector à n-dimensionnel
-----------------------------------
template <class T>
ostream& operator<<(ostream& o, const vector<T>& vec)
{
    o << '[';
    for (size_t i = 0; i < vec.size(); ++i)
        o << (i != 0 ? " " : "") << vec[i];
    o << ']';
    return o;
}

template <typename T>
void print(const T& val)
{
    cout << val;
}
*/