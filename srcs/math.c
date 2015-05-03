#include "atari.h"

double				two_pi_modulo(double rad)
{
	if (rad > 2 * PI)
		return (rad - 2 * PI);
	return rad;
}
