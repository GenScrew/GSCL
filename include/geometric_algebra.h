/* GSCL: geometric_algebra

   This module provided a GeometricAlgebra ans a MultiVector classes.
*/
#ifndef _GEOMETRIC_ALGEBRA_H
#define _GEOMETRIC_ALGEBRA_H

#include <cstring>
#include <vector>
using namespace std;

#define MV_TYPE float


/* BladeId

   PLEASE DO NOT USE OR MODIFY.
   This class is only used for initializing GeometricAlgebra instances. */
class BladeId
{
	public:
		unsigned int value;

		BladeId(const unsigned int n=0);
		bool operator<(const BladeId other);
};


class MultiVector;

/* GeometricAlgebra

   This class implements an n-dimensional geometric algebra (a.k.a. Clifford's
   algebra). Creating an instance of GeometricAlgebra will provide you with a
   framework for multivector manipulations.

   To create a new GeometricAlgebra, you just have to do as follow:
   ```cpp
   GeometricAlgebra ga(3); // where 3 is the wanted dimension	
   ``` */
class GeometricAlgebra
{
	public:
		// The dimension of the geometric algebra.
		int dim;

		// The number of basis blades of the algebra.
		int nb_blades;

		vector<string> names;

		// The basis blades index for geometric product calculation.
		vector<int> blades;

		// The MultiVector instances of basis blades.
		vector<MultiVector> basis;

		// The number of basis blades per grade.
		vector<int> grades;


		// Contructor method.
		GeometricAlgebra(const int dim, const vector<string> blades_names);

		/* get_gp_basis: computes the geometric product

		   This method takes the index of two basis blades and returns
		   the index of the basis blade resulting from the geometric
		   product of the two given blades. */
		unsigned int get_gp_basis(const int basis_index1, const int basis_index2);

		/* get_gp_sign: computes the signe of the geometric product

		   This methods takes the index of two basis blades and returns
		   the sign of the geometric product of the two given blades. */
		MV_TYPE get_gp_sign(int basis_index1, int basis_index2);

		/* get_grade: get all the index of basis k-blades.

		  This methods computes the first and last index of the basis
		  k-blades where ``k`` is the grade you want. */
		void get_grade(const int grade_index, unsigned int &first_index, unsigned int &last_index);

		// Returns the `index` basis blade of the algebra.
		MultiVector operator[](const int index);
};


class MultiVector
{
	public:
		// The GeometricAlgebra the multivector instance belongs.
		GeometricAlgebra* ga;

		// The component of the multivector.
		vector<MV_TYPE> value;

		// Constructor Method.
		MultiVector(GeometricAlgebra* geo_alg, vector<MV_TYPE> component);
		MultiVector(void){};

		MV_TYPE operator[](const unsigned int index);

		/* projection: project the multivector on a subspace.

		   This method takes as argument the grade on which you want to
		   project the multivector and returns the result of the
		   projection. For instance, if you have a multivector like:
		   `MultiVector mv = 1 + 2 * e1 + 3*e12`, calling
		   `mv.projection(0)` will return the scalar 1; calling
		   `mv.projection(1)` will return `2*e1` and so on. */
		MultiVector projection(int k);

		// Computes the grade involution of the multivector.
		MultiVector grade_involution(void);

		// Computes the reversion of the multivector.
		MultiVector reversion(void);

		// Computes the inverse multivector.
		MultiVector inverse(void);

		// Computes the dual multivector.
		MultiVector dual(void);

		/* is_spinor: Tests if the multivector is a spinor
		
		   Tests if the multivector is a spinor, i.e. if it has only
		   even grades. */
		bool is_spinor(void);
};

ostream& operator<<(ostream& stream, MultiVector mv);

// Tests the equality between two multivectors.
bool operator==(MultiVector mv, MultiVector other);

// Tests the non-equality between two multivectors.
bool operator!=(MultiVector mv, MultiVector other);

// Additions
MultiVector operator+(MultiVector mv, MV_TYPE other);
MultiVector operator+(MV_TYPE other, MultiVector mv);
MultiVector operator+(MultiVector mv, MultiVector other);

// Unary minus and subtractions
MultiVector operator-(MultiVector mv);
MultiVector operator-(MultiVector mv, MV_TYPE other);
MultiVector operator-(MV_TYPE other, MultiVector mv);
MultiVector operator-(MultiVector mv, MultiVector other);

// Geometric products
MultiVector operator*(MultiVector mv, MV_TYPE other);
MultiVector operator*(MV_TYPE other, MultiVector mv);
MultiVector operator*(MultiVector mv, MultiVector other);

// Outer products
MultiVector operator^(MultiVector mv, MV_TYPE other);
MultiVector operator^(MV_TYPE other, MultiVector mv);
MultiVector operator^(MultiVector mv, MultiVector other);

// Inner product
MultiVector operator|(MultiVector mv, MultiVector other);

// Divisions
MultiVector operator/(MultiVector mv, MV_TYPE other);
MultiVector operator/(MV_TYPE other, MultiVector mv);
MultiVector operator/(MultiVector mv, MultiVector other);


// Computes the binomial coefficien nCk.
int binomial_coefficient(int n, int k);


#endif /* _GEOMETRIC_ALGEBRA_H */