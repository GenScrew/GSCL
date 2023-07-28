#include <iostream>
#include "include/screw.h"
using namespace std;


Screw::Screw(MultiVector s_point, MultiVector s_direction, MultiVector s_moment)
{
	try
	{
		if (s_point.projection(1) != s_point)
			throw 1;
	}
	
	catch(int err)
	{
		if (err == 1)
			cout << "ScrewErr: the reference point must be a point" << endl;
	}

	ref_point = MultiVector(s_point.ga, s_point.value);
	direction = MultiVector(s_direction.ga, s_direction.value);
	moment = MultiVector(s_moment.ga, s_moment.value);
}


/*Screw Screw::change_point(MultiVector new_point)
{
	try
	{
		if (new_point.projection(1) != new_point)
			throw 1;
	}
	
	catch(int err)
	{
		if (err == 1)
			cout << "ScrewErr: the new reference point must be a point" << endl;
	}

	MultiVector new_moment = Screw::moment - ((new_point - Screw::ref_point) ^ Screw::direction);
	return Screw(new_point, Screw::direction, new_moment);
}*/
