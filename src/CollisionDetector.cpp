#include "../header/CollisionDetector.h"

bool CollisionDectector::CircleAndCircle(Circle c1, Circle c2)
{
	if (distance_square(c1.center, c2.center) <= pow(c1.radius+c2.radius,2))
	{
		return true;
	}
	return false;
}

bool CollisionDectector::RectAndRect(Rectangle r1, Rectangle r2)
{
	// Define 4 corners'coordinate of rectangle r1
	float bottom_right_x_r1 = r1.center.x + r1.width/2.0;
	float bottom_right_y_r1 = r1.center.y + r1.height/2.0;
	
	float top_left_x_r1 = r1.center.x - r1.width/2.0;
	float top_left_y_r1 = r1.center.y - r1.height/2.0;

	// Define 4 corners'coordinate of rectangle r2
	float bottom_right_x_r2 = r2.center.x + r2.width/2.0;
	float bottom_right_y_r2 = r2.center.y + r2.height/2.0;

	float top_left_x_r2 = r2.center.x - r2.width/2.0;	
	float top_left_y_r2 = r2.center.y - r2.height/2.0;

	// Check conditions for intersection
	if (bottom_right_x_r1 < top_left_x_r2 
			|| bottom_right_y_r1 < top_left_y_r2 
				|| bottom_right_x_r2 < top_left_x_r1 
					|| bottom_right_y_r2 < top_left_y_r1) 
	{
		return false;
	}

	return true;
}

bool CollisionDectector::CircleAndRect(Circle c, Rectangle r)
{
	float circleDistance_x = abs(c.center.x - r.center.x);
    float circleDistance_y = abs(c.center.y - r.center.y);

	if (circleDistance_x > (r.width/2.0 + c.radius)) { return false; }
    if (circleDistance_y > (r.height/2.0 + c.radius)) { return false; }

	if (circleDistance_x <= (r.width/2.0)) { return true; } 
    if (circleDistance_y <= (r.height/2.0)) { return true; }

	float cornerDistance_sq = pow((circleDistance_x - r.width/2.0),2) +
                         pow((circleDistance_y - r.height/2.0),2);

	return cornerDistance_sq <= pow(c.radius,2);
}

bool CollisionDectector::CircleAndRect(Rectangle r, Circle c)
{
	return this->CircleAndRect(c, r);
}
