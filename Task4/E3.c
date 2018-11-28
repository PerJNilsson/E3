/*
  E3.c
  This program reads data from the file MC.txt.
  Created by Anders Lindman on 2015-11-12.
*/

#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  // Declarations
  double u;
	const gsl_rng_type *T;
	gsl_rng *q;
  int nbr_of_lines;
  FILE *in_file;

  // Initializations
  gsl_rng_env_setup();
	T = gsl_rng_default;
	q = gsl_rng_alloc(T);
	gsl_rng_set(q,time(NULL));
  nbr_of_lines = 1e6; /* The number of lines in MC.txt. */
  double *data = malloc((nbr_of_lines) * sizeof (double));

	// generate uniform random number
	u = gsl_rng_uniform(q);

  /* Read data from file. */
  in_file = fopen("MC.txt","r");
  for (int i=0; i<nbr_of_lines; i++) {
    fscanf(in_file,"%lf",&data[i]);
  }
  fclose(in_file);

  gsl_rng_free(q);
}


void auto_corr_fun(double* data, int nbr_of_lines){
  int k = 1000;
  double mean_ik_i[k];
  double phi_k[k];
  double mean_i2, mean_i;
  for (int i=0; i<nbr_of_lines-k; i++){
    for (int j=0; j<k; j++){
      mean_ik_i[k] += data[i]*data[i+k]/(nbr_of_lines-k);
    }
  }
  for (int i=0; i<nbr_of_lines; i++){
    mean_i2 += data[i]*data[i]/nbr_of_lines;
    mean_i += data[i]/nbr_of_lines;
  }
  for (int i=0; i<k; i++){
    phi_k[k] = (mean_ik_i[k] - mean_i*mean_i) / (mean_i2-mean_i*mean_i);
  }
}
