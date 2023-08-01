#include <iostream>
#include "include/main.h"
#include "include/geometric_algebra.h"
#include "include/screw.h"

using namespace std;


int main()
{
	GeometricAlgebra ga(3, {"s", "e1", "e2", "e3", "e12", "e13", "e23", "e123"});
	MultiVector s = ga[0];
	MultiVector e1 = ga[1];
	MultiVector e2 = ga[2];
	MultiVector e3 = ga[3];
	MultiVector e12 = ga[4];
	MultiVector e13 = ga[5];
	MultiVector e23 = ga[6];
	MultiVector e123 = ga[7];

	Screw scw(e1, e1, 0*s);
	CoScrew coscw(e1, e2, 0*s);
	cout << comoment(coscw, scw) << endl;
	
	return 0;
}
