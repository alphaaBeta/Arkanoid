#include "Ball.h"

#include <math.h>


double Ball::V() {
	return (sqrt((vx*vx) + (vy*vy)));
}

