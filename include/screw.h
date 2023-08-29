/* GSCL: screw

   This module provides a Screw and CoScrew classes which implement generalized
   (co)screws.
*/
#ifndef _SCREW_H
#define _SCREW_H

#include "include/geometric_algebra.h"


/* Screw
  
  This class implements generalized screws. The components of generalized screws
  are multivectors instead of vectors.

  This class overloads the main operators:
  - <<
  - + for the addition
  - ^ for the outer product

  Each screw are given with a reference point, you can change this point by using `change_point` */
class Screw
{
	public:
		// The point of reference for the screw.
		MultiVector ref_point;

		// The direction of the screw.
		MultiVector direction;

		// The moment of the screw.
		MultiVector moment;

		// Constructor method.
		Screw(MultiVector s_point, MultiVector s_direction, MultiVector s_moment);

		/* change_point
		
		   This method takes in argument the new point of reference of
		   the screw and change it to the new one.*/
		Screw change_point(MultiVector new_point);

		/* show

		   This method can take a point of reference as argument and
		   display the screw at this point. If no point were given, it
		   displays the screw at its reference point. */
		void show(MultiVector new_point=MultiVector());
};

/* operator<<
   
   This method overloads <<. It allows to display a screw with the classic way:
   ```cpp
   cout << my_screw << endl;
   ``` */
ostream& operator<<(ostream& stream, Screw scw);

// The addition of screws.
Screw operator+(Screw scw, Screw other);

// The outer product of screws.
Screw operator^(Screw scw, Screw other);


/* CoScrew

  This class implements generalized screws. The components of generalized screws
  are multivectors instead of vectors.

  This class overloads the main operators:
  - <<
  - + for the addition
  - * for the scalar product

  Each screw are given with a reference point, you can change this point by using `change_point` */
class CoScrew
{
	public:
		// The point of reference for the screw.
		MultiVector ref_point;

		// The direction of the screw.
		MultiVector direction;

		// The moment of the screw.
		MultiVector moment;

		// Constructor method.
		CoScrew(MultiVector s_point, MultiVector s_direction, MultiVector s_moment);

		/* change_point
		
		   This method takes in argument the new point of reference of
		   the screw and change it to the new one.*/
		CoScrew change_point(MultiVector new_point);

		/* show

		   This method can take a point of reference as argument and
		   display the screw at this point. If no point were given, it
		   displays the screw at its reference point. */
		void show(MultiVector new_point=MultiVector());

		/* composition

		   Computes the composition of two coscrews. */
		CoScrew composition(CoScrew other);
};

/* operator<<
   
   This method overloads <<. It allows to display a coscrew with the classic
   way:
   ```cpp
   cout << my_coscrew << endl;
   ``` */
ostream& operator<<(ostream& stream, CoScrew scw);

// The addition of coscrews.
CoScrew operator+(CoScrew scw, CoScrew other);

// The scalar product.
CoScrew operator*(MV_TYPE other, CoScrew scw);

// Compute the comoment between a coscrew and a screw.
MV_TYPE comoment(CoScrew coscw, Screw scw);


#endif /* _SCREW_H */