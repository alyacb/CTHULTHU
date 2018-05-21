#include "util.h"
#include <math.h>

/******************************************************************
 *
 *  @author: Alya Carina Berciu
 *
 *
 ******************************************************************/

const double ARBITRARY_EPSILON = 0.0000000001;
 
bool doubleEquals(double d1, double d2){
	return doubleEquals(d1, d2, ARBITRARY_EPSILON);
}

bool doubleEquals(double d1, double d2, double cutoff){
        return abs(d1 - d2) < cutoff;
}
