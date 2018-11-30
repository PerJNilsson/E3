#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//double abs(double x);
int main() {
  int nbr_of_simulations = 8;
  int N[nbr_of_simulations];
  double random_value;
  double mean_value;
  double variance;
  double value_of_integral;
  double error;
  for (int i=0; i<nbr_of_simulations; i++){
    N[i]= pow(10, i+1);
  }

  srand(time(NULL));
  for (int i=0; i<nbr_of_simulations-1; i++){
    mean_value=0;
    variance=0;
    for (int j=0; j<N[i]; j++){
      random_value = (double) rand() / (double) RAND_MAX;

      mean_value += random_value*(1.0-random_value);
      variance += (random_value*(1.0-random_value))*(random_value*(1.0-random_value));
    }
    mean_value = mean_value / (double)N[i];
    variance = variance / (double) N[i] - mean_value*mean_value;

    value_of_integral = mean_value + sqrt(variance/((double)N[i]));
    //error = sqrt((value_of_integral-(1.0/6.0))*(value_of_integral-(1.0/6.0)))/(1.0/6.0);
    printf("N=%08d | I=%f | sigma_f=%f | sigma_I=%f\n",N[i], value_of_integral, variance, variance / sqrt((double)N[i]));
  }
  return 0;
  }
