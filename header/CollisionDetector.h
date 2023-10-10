#ifndef CollisionDectector_H

#define CollisionDectector_H

#include "./ShapeBounder.h"
#include <math.h>

//Dùng phát hiện đụng độ
class CollisionDectector
{
	public:
		bool CircleAndCircle(Circle c1, Circle c2);
		bool RectAndRect(Rectangle r1, Rectangle r2);
		bool CircleAndRect(Circle c, Rectangle r);
		bool CircleAndRect(Rectangle r, Circle c);
};

#endif