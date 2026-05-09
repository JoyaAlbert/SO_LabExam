int tr_integrate( double * result, double x1, double x2, long nstep, double(*f)(double)){

  double a, x, step;
  long i;

  step = (x2-x1)/(double)nstep;

  for( i = 0, a = 0, x = x1; i < nstep; i++){
    double xn; 
    xn = x + step;
    a += ( f(x) + f(xn) ) * step / 2;
    x = xn; 
  }   
  
  *result = a;

  return 0;
}

