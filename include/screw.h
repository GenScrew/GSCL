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
		// Screw change_point(MultiVector new_point);
};

#endif /* _SCREW_H */