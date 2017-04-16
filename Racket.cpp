#include "Racket.h"

#include "Ball.h"


int Racket::Move(char dir, double step = 0.01) {

	double xnew;
	switch (dir) {
	case 'l':
		xnew = this->x - step;
		if (GetDistanceFromLine(this->x, 0.0) <= this->width / 2) {
			return 0;
		}
		else
			this->x = xnew;
		return 1;

	case 'r':
		xnew = this->x + step;
		if (GetDistanceFromLine(this->x, double(FIELD_WIDTH)) <= this->width / 2) {
			return 0;
		}
		else
			this->x = xnew;
		return 1;

	}

}