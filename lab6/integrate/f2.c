#include <math.h>
  
double f( double x){
  return fabs(x) <= 1 ? sqrt(1.0L - x*x) : 0;
}

