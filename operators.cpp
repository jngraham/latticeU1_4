
/*
/////////////////////////////////////////////////////////////////////////////

U(1) Lattice Gauge Theory Simulator | James Graham

Write out the operator functions

/////////////////////////////////////////////////////////////////////////////
*/

#include <iostream>
#include <cmath>
#include <array>
#include <typeinfo>

#include "globals.h"
#include "operators.h"

double avg_p(std::array<double*,30>** array){

  double p_sum = 0;

  double p_xy = 0;
  double p_xt = 0;
  double p_yt = 0;

  std::array<double*,30> site;

  for (int i = 0; i < N_sites; i++){
    site = *array[i];

    p_xy = *site[0] + *site[6] - *site[11] - *site[1];
    p_xt = *site[0] + *site[7] - *site[16] - *site[2];
    p_yt = *site[1] + *site[12] - *site[17] - *site[2];

    p_sum = p_sum + cos(p_xy) + cos(p_xt) + cos(p_yt);
  }

  return p_sum / N_plaquettes;
}

// double m_plus(Site** lattice, int t, double VEV){
//
//   double jpc_plus_sum = 0;
//   double p_xy = 0;
//
//   size_t start = Lx*Ly*t;
//   size_t end = Lx*Ly*(t+1);
//
//   Site** ptr = lattice;
//
//   for (size_t i = start; i < end; i++){
//     p_xy = (*ptr)->xlink + (*ptr)->xnext->ylink - (*ptr)->ynext->xlink - (*ptr)->ylink;
//
//     jpc_plus_sum += cos(p_xy) - VEV;
//     ptr++;
//   }
//
//   return jpc_plus_sum;
//
// }
//
// double m_minus(Site** lattice, int t){
//
//   double jpc_minus_sum = 0;
//   double p_xy = 0;
//
//   size_t start = Lx*Ly*t;
//   size_t end = Lx*Ly*(t+1);
//
//   Site** ptr = lattice + start;
//
//   for (size_t i = start; i < end; i++){
//     p_xy = (*ptr)->xlink + (*ptr)->xnext->ylink - (*ptr)->ynext->xlink - (*ptr)->ylink;
//
//     jpc_minus_sum += sin(p_xy);
//     ptr++;
//   }
//
//   return jpc_minus_sum;
// }
//
// void flux(Site** lattice, int t, double* re_ptr, double* im_ptr){
//
//   double phase_sum = 0;
//   double re_sum = 0;
//   double im_sum = 0;
//
//   size_t start = Lx*Ly*t;
//   size_t end = Lx*Ly*(t+1);
//
//   Site** ptr = lattice + start;
//
//   for (size_t i = 0; i < Ly; i++){
//     for (size_t j = 0; j < Lx; j++){
//       phase_sum += (*ptr)->xlink;
//       ptr++;
//     }
//
//     re_sum += cos(phase_sum);
//     im_sum += sin(phase_sum);
//
//     phase_sum = 0;
//   }
//
//   *re_ptr = re_sum;
//   *im_ptr = im_sum;
//
//   return;
// }
