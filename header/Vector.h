#ifndef Vector_H

#define Vector_H
#include <math.h>

/// Vector
class Vector
{
	public:
		float x;
		float y;
		Vector(){}
		Vector(float x, float y);
		Vector operator + (Vector const & other);
		Vector operator - (Vector const & other);
		bool operator == (Vector const & other);
		bool operator != (Vector const & other);
		bool IsOppositeDirection(Vector other);
		Vector operator * (float n);
		Vector operator / (float n);
		float DotProduct(Vector other);
		float GetCosAngle(Vector other);
		float GetSinAngle(Vector other);
		float GetLength();
		Vector GetUnitVector();
};

int distance_square(Vector v1, Vector v2);

#endif