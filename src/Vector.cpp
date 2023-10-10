#include "../header/Vector.h"


Vector Vector::operator + (Vector const & other)
{
	Vector res;
	res.x = this->x + other.x;
	res.y = this->y + other.y;
	return res;
}

Vector Vector::operator - (Vector const & other)
{
	Vector res;
	res.x = this->x - other.x;
	res.y = this->y - other.y;
	return res;
}

Vector::Vector(float x, float y)
{
	this->x = x;
	this->y = y;
}

int distance_square(Vector v1, Vector v2) 
{
	return (pow((v1.x-v2.x),2)+pow((v1.y-v2.y),2));
}

float Vector::GetLength()
{
	return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

Vector Vector::GetUnitVector()
{
	float length = sqrt(pow(this->x, 2) + pow(this->y, 2));
	return Vector(this->x / length, this->y / length);
}

Vector Vector::operator * (float n)
{
	return Vector(this->x * n, this->y * n);
}

Vector Vector::operator / (float n)
{
	return Vector(this->x / n, this->y / n);
}

bool Vector::operator == (Vector const & other)
{
	if(this->x == other.x && this->y == other.y) return true;
	return false;
}

bool Vector::operator != (Vector const & other)
{
	if(this->x != other.x || this->y != other.y) return true;
	return false;
}

float Vector::DotProduct(Vector other)
{
	return this->x * other.x + this->y * other.y;
}

float Vector::GetCosAngle(Vector other)
{
	float dot_product = this->DotProduct(other);
	float dot_length = this->GetLength() * other.GetLength();
	return dot_product / dot_length;
}

float Vector::GetSinAngle(Vector other)
{
	float cos = this->GetCosAngle(other);
	float sin = sqrt(1 - cos*cos);
	return sin;
}

bool Vector::IsOppositeDirection(Vector other)
{
	if(this->x > 0 && other.x < 0) return true;
	if(this->y > 0 && other.y < 0) return true;
	if(this->x < 0 && other.x > 0) return true;
	if(this->y < 0 && other.y > 0) return true;
	return false;
}