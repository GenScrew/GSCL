#include <algorithm>
#include <bit>
#include <cmath>
#include <iostream>
#include <typeinfo>
#include "include/geometric_algebra.h"

using namespace std;


BladeId::BladeId(const unsigned int n)
{
	value = n;
}


bool BladeId::operator<(const BladeId other)
{
	return __builtin_popcount(BladeId::value) < __builtin_popcount(other.value);
}


GeometricAlgebra::GeometricAlgebra(const int n)
{
	dim = n;
	nb_blades = pow(2, n);

	vector<BladeId> tmp_blades;
	for (int i = 0; i < nb_blades; i ++)
	{
		BladeId id(i);
		tmp_blades.push_back(id);
		if (i <= dim)
			grades.push_back(binomial_coefficient(dim, i));

		vector<MV_TYPE> value(nb_blades, 0);
		value[i] = 1;
		basis.push_back(MultiVector(this, value));
	}
	
	sort(tmp_blades.begin(), tmp_blades.end());

	for (BladeId id: tmp_blades)
		blades.push_back(id.value);
}


unsigned int GeometricAlgebra::get_gp_basis(const int basis_index1, const int basis_index2)
{
	int gp_index = GeometricAlgebra::blades[basis_index1] xor GeometricAlgebra::blades[basis_index2];
	return GeometricAlgebra::blades[gp_index];
}


MV_TYPE GeometricAlgebra::get_gp_sign(int basis_index1, int basis_index2)
{
	basis_index1 = basis_index1 >> 1;
	int n_swap = 0;
	while (basis_index1)
	{
		n_swap += __builtin_popcount(basis_index1 & basis_index2);
		basis_index1 = basis_index1 >> 1;
	}
	n_swap ++;
	return (MV_TYPE) 2 * (n_swap % 2) - 1;
}


void GeometricAlgebra::get_grade(const int grade_index, unsigned int &first_index, unsigned int &last_index)
{
	first_index = 0;
	for (int i = 0; i < grade_index; i ++)
		first_index += GeometricAlgebra::grades[i];

	last_index = first_index + GeometricAlgebra::grades[grade_index];
}


void GeometricAlgebra::show(void)
{
	cout << "GeometricAlgebra(dim=" << GeometricAlgebra::dim << ")" << endl;
}


MultiVector GeometricAlgebra::operator[](const int index)
{
	return GeometricAlgebra::basis[index];
}


MultiVector::MultiVector(GeometricAlgebra* geo_alg, vector<MV_TYPE> component)
{
	ga = geo_alg;
	value = component;
}


void MultiVector::show(void)
{
	cout << "MultiVector({ ";
	for (MV_TYPE i: MultiVector::value)
		cout << i << " ";
	cout << "})" << endl;
}


MV_TYPE MultiVector::operator[](const unsigned int index)
{
	return MultiVector::value[index];
}


MultiVector MultiVector::projection(int k)
{
	vector<MV_TYPE> new_value(MultiVector::ga->nb_blades, 0);
	unsigned int first, last;
	MultiVector::ga->get_grade(k, first, last);

	for (unsigned int i = 0; i < MultiVector::ga->nb_blades; i ++)
	{
		if (i >= first && i < last)
			new_value[i] = MultiVector::value[i];
	}

	return MultiVector(MultiVector::ga, new_value);
}


MultiVector MultiVector::grade_involution(void)
{
	vector<MV_TYPE> new_value(MultiVector::ga->nb_blades, 0);
	MultiVector new_mv(MultiVector::ga, new_value);

	for (int i = 0; i <= MultiVector::ga->dim; i ++)
		new_mv = new_mv + pow(-1, i) * MultiVector::projection(i);

	return new_mv;
}


MultiVector MultiVector::reversion(void)
{
	vector<MV_TYPE> new_value(MultiVector::ga->nb_blades, 0);
	MultiVector new_mv(MultiVector::ga, new_value);

	for (int i = 0; i <= MultiVector::ga->dim; i ++)
		new_mv = new_mv + pow(-1, (i * (i - 1)) / 2) * MultiVector::projection(i);

	return new_mv;
}


MultiVector MultiVector::inverse(void)
{
	vector<MV_TYPE> new_value(MultiVector::ga->nb_blades, 0);
	return MultiVector(MultiVector::ga, new_value);
}


MultiVector MultiVector::dual(void)
{
	unsigned int n = MultiVector::ga->basis.size();
	MultiVector I = MultiVector::ga->basis[n - 1];
	return *this * I.inverse();
}


bool MultiVector::is_spinor(void)
{
	vector<MV_TYPE> new_value(MultiVector::ga->nb_blades, 0);
	MultiVector new_mv(MultiVector::ga, new_value);
	for (int i = 0; i < MultiVector::ga->nb_blades; i += 2)
		new_mv = new_mv + this->projection(i);

	return (new_mv == *this);
}


bool operator==(MultiVector mv, MultiVector other)
{
	for (int i = 0; i < mv.ga->nb_blades; i ++)
	{
		if (mv.value[i] != other.value[i])
			return false;
	}

	return true;
}


bool operator!=(MultiVector mv, MultiVector other)
{
	return !(mv == other);
}


MultiVector operator+(MultiVector mv, MV_TYPE other)
{
	vector<MV_TYPE> new_value(mv.ga->nb_blades, 0);
	new_value[0] = other;

	for (int i = 0; i < mv.ga->nb_blades; i ++)
		new_value[i] += mv.value[i];

	return MultiVector(mv.ga, new_value);
}


MultiVector operator+(MV_TYPE other, MultiVector mv)
{
	return mv + other;
}


MultiVector operator+(MultiVector mv, MultiVector other)
{
	vector<MV_TYPE> new_value(mv.ga->nb_blades, 0);

	for (int i = 0; i < mv.ga->nb_blades; i ++)
		new_value[i] = mv.value[i] + other.value[i];

	return MultiVector(mv.ga, new_value);
}


MultiVector operator-(MultiVector mv)
{
	vector<MV_TYPE> new_value(mv.ga->nb_blades, 0);

	for (int i = 0; i < mv.ga->nb_blades; i ++)
		new_value[i] = -mv.value[i];

	return MultiVector(mv.ga, new_value);
}


MultiVector operator-(MultiVector mv, MV_TYPE other)
{
	return mv + (-other);
}


MultiVector operator-(MV_TYPE other, MultiVector mv)
{
	return other + (-mv);
}


MultiVector operator-(MultiVector mv, MultiVector other)
{
	vector<MV_TYPE> new_value(mv.ga->nb_blades, 0);

	for (int i = 0; i < mv.ga->nb_blades; i ++)
		new_value[i] = mv.value[i] - other.value[i];

	return MultiVector(mv.ga, new_value);

}


MultiVector operator*(MultiVector mv, MV_TYPE other)
{
	vector<MV_TYPE> new_value(mv.ga->nb_blades, 0);

	for (int i = 0; i < mv.ga->nb_blades; i ++)
		new_value[i] = other * mv.value[i];

	return MultiVector(mv.ga, new_value);	
}


MultiVector operator*(MV_TYPE other, MultiVector mv)
{
	return mv * other;
}


MultiVector operator*(MultiVector mv, MultiVector other)
{
	vector<MV_TYPE> new_value(mv.ga->nb_blades, 0);

	for (int i = 0; i < mv.ga->nb_blades; i ++)
	{
		for (int j = 0; j < mv.ga->nb_blades; j ++)
		{
			int index = mv.ga->get_gp_basis(i, j);
			MV_TYPE sign = mv.ga->get_gp_sign(i, j);
			new_value[index] += sign * mv.value[i] * other.value[j];
		}
	}

	return MultiVector(mv.ga, new_value);	
}


MultiVector operator^(MultiVector mv, MV_TYPE other)
{
	return mv * other;
}


MultiVector operator^(MV_TYPE other, MultiVector mv)
{ 
	return mv * other;
}


MultiVector operator^(MultiVector mv, MultiVector other)
{
	vector<MV_TYPE> new_value(mv.ga->nb_blades, 0);
	MultiVector new_mv(mv.ga, new_value);

	for (int gd1 = 0; gd1 < mv.ga->dim; gd1 ++)
	{
		for (int gd2 = 0; gd2 < mv.ga->dim; gd2 ++)
		{
			if (gd1 + gd2 <= mv.ga->dim)
			{
				MultiVector mv1 = mv.projection(gd1);
				MultiVector mv2 = other.projection(gd2);
				new_mv = new_mv + (mv1 * mv2).projection(gd1 + gd2);
			}
		}
	}
	return new_mv;
}


MultiVector operator|(MultiVector mv, MultiVector other)
{
	vector<MV_TYPE> new_value(mv.ga->nb_blades, 0);
	MultiVector new_mv(mv.ga, new_value);

	for (int gd1 = 1; gd1 <= mv.ga->dim; gd1 ++)
	{
		for (int gd2 = 1; gd2 <= mv.ga->dim; gd2 ++)
		{
			MultiVector mv1 = mv.projection(gd1);
			MultiVector mv2 = other.projection(gd2);
			new_mv = new_mv + (mv1 * mv2).projection(abs(gd2 - gd1));
		}
	}
	return new_mv;
}


MultiVector operator/(MultiVector mv, MV_TYPE other)
{
	vector<MV_TYPE> new_value(mv.ga->nb_blades, 0);
	for (int i = 0; i < mv.ga->nb_blades; i ++)
		new_value[i] = mv.value[i] / other;

	return MultiVector(mv.ga, new_value);
}


MultiVector operator/(MV_TYPE other, MultiVector mv)
{
	return other * mv.inverse();
}


MultiVector operator/(MultiVector mv, MultiVector other)
{
	return mv * other.inverse();
}


int binomial_coefficient(int n, int k)
{
	if (k < 0 or k > n)
		return 0;
	if (k == 0 or k == n)
		return 1;

	k = min(k, n - k);
	int coeff = 1;
	for (int i = 0; i < k; i ++)
		coeff = floor(coeff * (n - i) / (i + 1));

	return coeff;
}
