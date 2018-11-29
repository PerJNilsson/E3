#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#define M_PI 3.14159265358979323846


double trial_change (double x_m, double r);
double weightfunction(double x, double y, double z);
double integral_function(double x, double y, double z);
int main() {
  int nbr_of_simulations = 8;
  int N[nbr_of_simulations];
  double random_value;
  double I_value;
  double variance;
  double value_of_integral;
  double I;
  double w2, w1;
  long count;
  int init_phase = 10000;

  // GSL INITIALIZATION
  double u;
	const gsl_rng_type *T;
	gsl_rng *q;
  // Initializations
  gsl_rng_env_setup();
	T = gsl_rng_default;
	q = gsl_rng_alloc(T);
	gsl_rng_set(q,time(NULL));

  // generate uniform random number
	u = gsl_rng_uniform(q);

  for (int i=0; i<nbr_of_simulations; i++){
    N[i]= pow(10, i+1);
  }
  double x1,x2,y1,y2,z1,z2;
  srand(time(NULL));
  for (int i=0; i<nbr_of_simulations-1; i++){
    I_value=0;
    variance=0;
    count = 0;
    x1=0.8*u; y1=-0.3*u; z1=0.5*u;
    w1=0; w2=0;
    // Initialization phase
    for (int j=0; j<init_phase; j++){
      //random_value = (double) rand() / (double) RAND_MAX;
      random_value = gsl_rng_uniform(q);
      x2 = trial_change(x1, random_value);

      //random_value = (double) rand() / (double) RAND_MAX;
      random_value = gsl_rng_uniform(q);
      y2 = trial_change(y1, random_value);

      //random_value = (double) rand() / (double) RAND_MAX;
      random_value = gsl_rng_uniform(q);
      z2 = trial_change(z1, random_value);

      w1 = weightfunction(x1,y1,z1);
      w2 = weightfunction(x2,y2,z2);

      //random_value = (double) rand() / (double) RAND_MAX;
      random_value = gsl_rng_uniform(q); 
      if (random_value > w2/w1) {
        x2=x1; y2=y1; z2=z1;
      }
      x1=x2; y1=y2; z1=z2;
    }


    for (int j=0; j<N[i]; j++){
      //random_value = (double) rand() / (double) RAND_MAX;
      random_value = gsl_rng_uniform(q);
      x2 = trial_change(x1, random_value);

      //random_value = (double) rand() / (double) RAND_MAX;
      random_value = gsl_rng_uniform(q);
      y2 = trial_change(y1, random_value);

      //random_value = (double) rand() / (double) RAND_MAX;
      random_value = gsl_rng_uniform(q);
      z2 = trial_change(z1, random_value);

      w1 = weightfunction(x1,y1,z1);
      w2 = weightfunction(x2,y2,z2);

      //random_value = (double) rand() / (double) RAND_MAX;
      random_value = gsl_rng_uniform(q); 
      if (random_value > w2/w1) {
        x2=x1; y2=y1; z2=z1;
        count+=1;
      }
      x1=x2; y1=y2; z1=z2;

      I = integral_function(x1,y1,z1);
      I_value += I;
    }
    I_value = I_value / (double)(N[i]);
    variance = sqrt(I_value)/ (double) N[i];


    value_of_integral = I_value;
    printf("N=%09d | I=%f | variance=%f | new states: %f\n",N[i], value_of_integral, variance,1.0-(double)count/(double)N[i]);
  }
  return 0;
}

double trial_change (double x_m, double r) {
  double x_n, C;
  C = 2.00;
  return x_n = x_m+C*(r-0.5); 
}

double weightfunction(double x, double y, double z){
  return (1.0/sqrt(M_PI*M_PI*M_PI))*exp(-(x*x+y*y+z*z));
}

double integral_function(double x, double y, double z){
  return (x*x+x*x*y*y+x*x*y*y*z*z);
}

