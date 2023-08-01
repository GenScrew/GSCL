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


Screw Screw::change_point(MultiVector new_point)
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
}


void Screw::show(MultiVector new_point)
{
	if (new_point.value.size())
		cout << (*this).change_point(new_point);
	else
		cout << *this;
}


ostream& operator<<(ostream& stream, Screw scw)
{
	stream << "Screw(\n\tdirection=" << scw.direction << "\n\tmoment=" << scw.moment << "\n)";
	return stream;
}


Screw operator+(Screw scw, Screw other)
{
	if (scw.ref_point != other.ref_point)
		other = other.change_point(scw.ref_point);

	return Screw(
			scw.ref_point,
			scw.direction + other.direction,
			scw.moment + other.moment
		);
}


Screw operator^(Screw scw, Screw other)
{
	if (scw.ref_point != other.ref_point)
		other = other.change_point(scw.ref_point);

	return Screw(
			scw.ref_point,
			(scw.direction ^ other.moment) + (scw.moment.grade_involution() ^ other.direction),
			scw.moment ^ other.moment
		);
}








CoScrew::CoScrew(MultiVector s_point, MultiVector s_direction, MultiVector s_moment)
{
	try
	{
		if (s_point.projection(1) != s_point)
			throw 1;
	}
	
	catch(int err)
	{
		if (err == 1)
			cout << "CoScrewErr: the reference point must be a point" << endl;
	}

	ref_point = MultiVector(s_point.ga, s_point.value);
	direction = MultiVector(s_direction.ga, s_direction.value);
	moment = MultiVector(s_moment.ga, s_moment.value);
}


CoScrew CoScrew::change_point(MultiVector new_point)
{
	try
	{
		if (new_point.projection(1) != new_point)
			throw 1;
	}
	
	catch(int err)
	{
		if (err == 1)
			cout << "CoScrewErr: the new reference point must be a point" << endl;
	}

	MultiVector new_moment = CoScrew::moment - (CoScrew::direction | (new_point - CoScrew::ref_point));
	return CoScrew(new_point, CoScrew::direction, new_moment);
}


void CoScrew::show(MultiVector new_point)
{
	if (new_point.value.size())
		cout << (*this).change_point(new_point);
	else
		cout << *this;
}


CoScrew CoScrew::composition(CoScrew other)
{
	try
	{
		if (!(CoScrew::direction.is_spinor() && other.direction.is_spinor()))
			throw 1;
	}
	catch(int err)
	{
		if (err == 1)
			cout << "CoScrewErr: the two coscrew directions must be spinors" << endl;
	}

	if (CoScrew::ref_point != other.ref_point)
		other = other.change_point(CoScrew::ref_point);

	return CoScrew(
			CoScrew::ref_point,
			CoScrew::direction * other.direction,
			CoScrew::direction * other.moment + CoScrew::moment * other.direction
		);
}



ostream& operator<<(ostream& stream, CoScrew scw)
{
	stream << "CoScrew(\n\tdirection=" << scw.direction << "\n\tmoment=" << scw.moment << "\n)";
	return stream;
}


CoScrew operator+(CoScrew scw, CoScrew other)
{
	if (scw.ref_point != other.ref_point)
		other = other.change_point(scw.ref_point);

	return CoScrew(
			scw.ref_point,
			scw.direction + other.direction,
			scw.moment + other.moment
		);
}


CoScrew operator*(MV_TYPE other, CoScrew scw)
{
	return CoScrew(
			scw.ref_point,
			other * scw.direction,
			other * scw.moment
		);
}


MV_TYPE comoment(CoScrew coscw, Screw scw)
{
	return ((-coscw.direction.grade_involution() * scw.moment.grade_involution())[0] + (scw.direction * coscw.moment)[0]);
}
