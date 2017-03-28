
/*
/////////////////////////////////////////////////////////////////////////////

U(1) Lattice Gauge Theory Simulator | James Graham

Here I write the simulator as a separate function so I can use main() to simulate
with a different beta each time.

/////////////////////////////////////////////////////////////////////////////
*/

#include <iostream>
#include <fstream>
#include <typeinfo>

#include <random>
#include <cmath>
#include <array>
#include <vector>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "globals.h"
#include "initialize.h"
#include "update.h"
#include "operators.h"

// #include "update.h"
// #include "operators.h"
// #include "write.h"

int simulate(float beta){

  clock_t t1 = clock();

  // set up the RNG

  // std::mt19937 generator(time(0));
  std::default_random_engine generator;
  std::normal_distribution<double> gaussian_distribution(mu,sigma);

  // declare lattice

  // lattice will be an array of pointers to standard arrays, which themselves contain pointers to doubles
  std::array<double*,30>* lattice [N_sites];

  // links is just an array of doubles
  // the x, y, t site is accessed by link[3*x + 3*Lx*y + 3*Lx*Ly*t]
  // get the x, y, t link from that site by adding, respectively, 0, 1, 2 to index
  double links [N_links] = {0};

  // declare V

  // std::array<double, N_V> V;
  double V [N_V] = {0};

  // declare data arrays

  double avg_plaquette_data [N_samples] = {0};
  double jpc_plus_data [Lt*N_samples] = {0};
  double jpc_minus_data [Lt*N_samples] = {0};
  double flux_re_data [Lt*N_samples] = {0};
  double flux_im_data [Lt*N_samples] = {0};

  // declare the plaquette average

  double this_avg_plaquette;
  double jpc_plus_zero;
  double jpc_minus_zero;
  double flux_re_zero;
  double flux_im_zero;
  double flux_re;
  double flux_im;

  // allocate memory for the arrays; initialize their entries to point to the right links

  for (int x = 0; x < Lx; x++){
    for (int y = 0; y < Ly; y++){

      // int latticey = Lx*y;
      for (int t = 0; t < Lt; t++){

        // int latticet = Lx*Ly*t;
        lattice[x + Lx*y + Lx*Ly*t] = new std::array<double*,30>;
        // std::cout << lattice[x + Lx*y + Lx*Ly*t] << std::endl;
        initialize(lattice[x + Lx*y + Lx*Ly*t], links, x, y, t);
        // std::cout << (*lattice[x + Lx*y + Lx*Ly*t])[29] << std::endl;
      }
    }
  }

  // initialize V

  for (size_t i = 0; i < N_V; i += 2){
    double number = gaussian_distribution(generator);
    V[i] = number;
    V[i+1] = -number;
  }

  clock_t t2 = clock();

  // relax the initial configuration

  for (int i = 0; i < 1; i++){
    update(lattice, V, beta);
  }

  // do the simulation

  int op_sample;

  for (int i = 0; i < N_samples; i++){

    op_sample = Lt*i;

    for (int j = 0; j < N_configs_per_sample; j++){
      update(lattice, V, beta);

      this_avg_plaquette = avg_p(lattice);
  //     jpc_plus_zero = m_plus(lattice, 0, this_avg_plaquette);
  //     jpc_minus_zero = m_minus(lattice, 0);
  //
  //     flux(lattice, 0, &flux_re_zero, &flux_im_zero);
  //
      avg_plaquette_data[i] += this_avg_plaquette / N_configs_per_sample;
  //
  //     for (int t = 0; t < Lt; t++){
  //
  //       jpc_plus_data[op_sample + t] += jpc_plus_zero*m_plus(lattice, t, this_avg_plaquette) / N_configs_per_sample;
  //       jpc_minus_data[op_sample + t] += jpc_minus_zero*m_minus(lattice, t) / N_configs_per_sample;
  //
  //       // we need two numbers out of this, which is not ideal
  //       flux(lattice, t, &flux_re, &flux_im);
  //
  //       flux_re_data[op_sample + t] += (flux_re_zero*flux_re + flux_im_zero*flux_im) / N_configs_per_sample;
  //       flux_im_data[op_sample + t] += (flux_re_zero*flux_im - flux_im_zero*flux_re) / N_configs_per_sample;
  //
  //       if ((j+1)%10000 == 0){
  //         std::cout << (j+1)/1000 << " configs complete for sample " << (i+1) << "\n";
  //       }
  //     }
    }

    std::cout << "sample " << (i+1) << " of " << N_samples << " complete\n";
  //
  }

  // delete all pointers!
  for (int i = 0; i < N_sites; i++){
    delete lattice[i];
  }

  //
  // write(avg_plaquette_data, jpc_plus_data, jpc_minus_data, flux_re_data, flux_im_data, beta);

  clock_t t3 = clock();

  for (int i = 0; i < N_samples; i++){
    std::cout << avg_plaquette_data[i] << std::endl;
  }
  //
  std::cout << "setup time: " << (double(t2) - double(t1)) / CLOCKS_PER_SEC << std::endl;
  std::cout << "compute time: " << (double(t3) - double(t2)) / CLOCKS_PER_SEC << std::endl;
  //

  return 0;
}
