/*
  E3.c
  This program reads data from the file MC.txt.
  Created by Anders Lindman on 2015-11-12.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <time.h>

int auto_corr_fun(double * N, int nbr_of_lines, int k);
void center_data(double* N, int nbr_of_lines);
double block_average(double* data, int nbr_of_lines, int B);

int main(){

  // Declarations
  int nbr_of_lines;
  FILE *in_file;
  FILE * values_block;

  // Initializations
  nbr_of_lines = 1E6; // The number of lines in MC.txt.
  double *data = malloc((nbr_of_lines) * sizeof (double));

  // Read data from file.
  in_file = fopen("MC.txt","r");
  for (int i=0; i<nbr_of_lines; i++) {
    double tmpData;
    fscanf(in_file,"%lf",&tmpData);
    data[i] = tmpData;
  }
  fclose(in_file);

  int s_corr;
  int k= 400;
  int B;
  int step = 10;
  int end = 15000;
  int length_array = end / step;
  double s_block[length_array];

  for (int i=0; i<length_array; i++){
    s_block[i] = 0.0;
  }
  center_data(data, nbr_of_lines);
  values_block = fopen("block_value.dat", "w");

  for (B = 1; B<length_array+1; B++){
    s_block[B-1] = block_average(data, nbr_of_lines, B*step);
    fprintf(values_block, "%d \t %f\n", B*step, s_block[B-1]);
  }
  fclose(values_block);

  double s_block_avg_avg = 0;
  int start_avg = length_array/4;
  printf("%d\n", start_avg);
  for (int i=start_avg; i<length_array; i++){
    s_block_avg_avg += s_block[i] / (double)(length_array-start_avg);
  }

  s_corr = auto_corr_fun(data,nbr_of_lines, k);
  printf("s from autocorrelation function is:%d\n", s_corr);

  printf("s from block average function is:%f\n", s_block_avg_avg);

  return 0;
}


int auto_corr_fun(double* data, int nbr_of_lines, int k){
  double mean_ik[k];
  double phi[k];
  int good_guess=0;
  double s = exp(-2.0);
  for (int i=0; i<k; i++){
    mean_ik[i]=0;
    phi[i]=0;
  }
  double mean_squared = 0;
  FILE * valuessave;
  for (int i = 0; i<k; i++) {
    for (int j=0; j<nbr_of_lines-i; j++){
      mean_ik[i] += data[j]*data[i+j]/(double)(nbr_of_lines-i);
    }
  }
  for (int i=0; i<nbr_of_lines; i++){
    mean_squared += data[i]*data[i]/(double) nbr_of_lines;
  }
  valuessave = fopen("values.dat", "w");
  for (int i=0; i<k; i++){
    phi[i] = (mean_ik[i]) / (mean_squared);
    fprintf(valuessave, "%d \t %f\n", i, phi[i]);
    if(sqrt((phi[good_guess]-s)*(phi[good_guess]-s))> sqrt((phi[i]-s)*(phi[i]-s))){
      good_guess = i;
    }
  }
  fclose(valuessave);
  return good_guess;
}

double block_average(double* data, int nbr_of_lines, int B){
  double good_guess_B;
  int j;
  j = nbr_of_lines / B;
  double F[j];
  for (int i=0; i<j; i++){
    F[i] = 0;
  }

  for (int i=0; i<j; i++){
    for (int k=0; k<B; k++){
      F[i] += data[k+i*B]/(double)B;
    }
  }
  double variance_F = 0;
  double mean_F = 0;
  for (int i=0; i<j; i++){
    variance_F += F[i]*F[i]/(double)j;
    mean_F += F[i]/(double)j;
  }
  variance_F = variance_F - mean_F*mean_F;

  double variance_f = 0;
  for (int i=0; i<nbr_of_lines; i++){
    variance_f += data[i]*data[i];
  }
  variance_f = variance_f / (double)nbr_of_lines;
  good_guess_B = (double)B * variance_F / variance_f;
  return good_guess_B;
}



void center_data(double*data, int nbr_of_lines){
  double main_mean=0;
  for (int i=0; i<nbr_of_lines; i++){
    main_mean += data[i];
  }
  main_mean = main_mean / (double)nbr_of_lines;
  for (int i=0; i<nbr_of_lines; i++){
    data[i]=data[i]-main_mean;
  }
 

}
