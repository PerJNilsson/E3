#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define M_PI 3.14159265358979323846


double trial_change (double x_m, double r);
double weightfunction(double x, double y, double z);
double integral_function(double x, double y, double z);
//double abs(double x);
int main() {
  int nbr_of_simulations = 8;
  int N[nbr_of_simulations];
  double random_value;
  double mean_value;
  double variance;
  double value_of_integral;
  double error;
  double px, gx;
  double I;
  double w2, w1, q;
  long count;

  for (int i=0; i<nbr_of_simulations; i++){
    N[i]= pow(10, i+1);
  }
  double x1,x2,y1,y2,z1,z2;
  srand(time(NULL));
  for (int i=0; i<nbr_of_simulations-1; i++){
    mean_value=0;
    variance=0;
    count = 0;
    x1=0.1; y1=-0.1; z1=0.5;
    w1=0; w2=0;
    for (int j=0; j<N[i]; j++){
      random_value = (double) rand() / (double) RAND_MAX;
      x2 = trial_change(x1, random_value);
      y2 = trial_change(y1, random_value);
      z2 = trial_change(z1, random_value);

      w1 = weightfunction(x1,y1,z1);
      w2 = weightfunction(x2,y2,z2);

      random_value = (double) rand() / (double) RAND_MAX;
      if (random_value > w2/w1) {
        x2=x1; y2=y1; z2=z1;
        count+=1;
      }
      x1=x2; y1=y2; z1=z2;

      I = integral_function(x1,y1,z1);
      mean_value += I;
      variance += I*I;
    }
    mean_value = mean_value / (double)(N[i]);
    variance = variance / (double) N[i] - mean_value*mean_value;


    value_of_integral = mean_value + sqrt(variance/((double)N[i]));
    error = 0; //sqrt((value_of_integral-(1.0/6.0))*(value_of_integral-(1.0/6.0)))/(1.0/6.0);
    printf("N=%09d | I=%f | error=%f | variance=%f | new states generated: %f\n",N[i], value_of_integral, error, variance,(double)count/(double)N[i]);
  }
  
  return 0;
}

double trial_change (double x_m, double r) {
  double x_n, C;
  C = 2.5;
  return x_n = x_m+C*(r-0.5); 
}

double weightfunction(double x, double y, double z){
  double w;

  return (1.0/sqrt(M_PI*M_PI*M_PI))*exp(-(x*x+y*y+z*z));
}

double integral_function(double x, double y, double z){
  return (1.0/sqrt(M_PI*M_PI*M_PI))*exp(-(x*x+y*y+z*z))*(x*x+x*x*y*y+x*x*y*y*z*z);
}




/* EARLIER SHIT CODE

   random_value = (double) rand() / (double) RAND_M;
   px = acos(1-2*random_value)/M_PI;

   mean_value += px*(1.0-px)/sin(M_PI*px)*2/M_PI; // 2/pi to have int of px equal to one
   variance += (px*(1.0-px))*(px*(1.0-px))/sin(M_PI*px)/sin(M_PI*px)*4/M_PI/M_PI;
   }
   mean_value = mean_value / (double)(N[i]);
   variance = variance / (double) N[i] - mean_value*mean_value;

   value_of_integral = mean_value + sqrt(variance/((double)N[i]));
   error = sqrt((value_of_integral-(1.0/6.0))*(value_of_integral-(1.0/6.0)))/(1.0/6.0);
   printf("N=%08d | I=%f | error=%f | variance=%f\n",N[i], value_of_integral, error, variance);

*/
