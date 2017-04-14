#include "Racket.h"



int Racket::Move(char dir, double step = 0.01) {

	
	switch (dir) {
	case 'l':
		double xnew = this->x - step;
		if (GetDistanceFromLine(this->x, 0.0) <= this->width / 2) {
			return 0;
		}
		else
			this->x = xnew;
		return 1;

	case 'r':
		double xnew = this->x + step;
		if (GetDistanceFromLine(this->x, double(FIELD_WIDTH)) <= this->width / 2) {
			return 0;
		}
		else
			this->x = xnew;
		return 1;

	}

}