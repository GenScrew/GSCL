#ifndef _SCREW_H
#define _SCREW_H

#include "include/geometric_algebra.h"


class Screw
{
	public:
		MultiVector ref_point;
		MultiVector direction;
		MultiVector moment;

		Screw(MultiVector s_point, MultiVector s_direction, MultiVector s_moment);
		Screw change_point(MultiVector new_point);
		void show(MultiVector new_point=MultiVector());
};

ostream& operator<<(ostream& stream, Screw scw);

Screw operator+(Screw scw, Screw other);
Screw operator^(Screw scw, Screw other);


class CoScrew
{
	public:
		MultiVector ref_point;
		MultiVector direction;
		MultiVector moment;

		CoScrew(MultiVector s_point, MultiVector s_direction, MultiVector s_moment);
		CoScrew change_point(MultiVector new_point);
		void show(MultiVector new_point=MultiVector());
		CoScrew composition(CoScrew other);
};

ostream& operator<<(ostream& stream, CoScrew scw);
CoScrew operator+(CoScrew scw, CoScrew other);
CoScrew operator*(MV_TYPE other, CoScrew scw);


MV_TYPE comoment(CoScrew coscw, Screw scw);




#endif /* _SCREW_H */