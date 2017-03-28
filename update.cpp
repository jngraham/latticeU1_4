
/*
/////////////////////////////////////////////////////////////////////////////

U(1) Lattice Gauge Theory Simulator | James Graham

Write out the update function

/////////////////////////////////////////////////////////////////////////////
*/

#include <iostream>
#include <random>
#include <cmath>
#include <array>
#include <stdlib.h>
#include <time.h>

#include "globals.h"
#include "update.h"

// std::mt19937 update_generator(time(0));
std::default_random_engine update_generator;
std::uniform_int_distribution<int> int_distribution(0,N_V-1);
std::uniform_real_distribution<double> real_distribution(0.0,1.0);

int update_site(std::array<double*,30> site, double* gauss, double beta);

int update(std::array<double*,30>** array, double* gauss, double beta){

  for (int i = 0; i < N_sites; i++){
    // std::cout << typeid(array).name() << std::endl;
    // std::cout << typeid(array[i]).name() << std::endl;
    update_site(*array[i], gauss, beta);
  }

  return 0;
}

int update_site(std::array<double*,30> site, double* gauss, double beta){

  double old_link;
  double new_link;

  double staple1;
  double staple2;
  double staple3;
  double staple4;

  double minus_old_action;
  double minus_new_action;

  double C;
  double z;

  // // int N_acceptances = 0;

  // update the x link

  // std::cout << typeid(*site[0]).name() << std::endl;
  old_link = *site[0];
  new_link = old_link + gauss[int_distribution(update_generator)];

  staple1 = *site[6] - *site[11] - *site[1];
  staple2 = - *site[18] - *site[8] + *site[9];
  staple3 = *site[7] - *site[16] - *site[2];
  staple4 = - *site[19] - *site[13] + *site[15];

  // staple1 = (*ptr)->xnext->ylink - (*ptr)->ynext->xlink - (*ptr)->ylink;
  // staple2 = - (*ptr)->xnext->yprev->ylink - (*ptr)->yprev->xlink + (*ptr)->yprev->ylink;
  // staple3 = (*ptr)->xnext->tlink - (*ptr)->tnext->xlink - (*ptr)->tlink;
  // staple4 = - (*ptr)->xnext->tprev->tlink - (*ptr)->tprev->xlink + (*ptr)->tprev->tlink;

  minus_old_action = cos(old_link + staple1) + cos(old_link + staple2) + cos(old_link + staple3) + cos(old_link + staple4);
  minus_new_action = cos(new_link + staple1) + cos(new_link + staple2) + cos(new_link + staple3) + cos(new_link + staple4);

  // note that if the new action is smaller than the old action, then
  // C > 1 so we accept the new link.
  C = exp(beta * (minus_new_action-minus_old_action));

  z = real_distribution(update_generator);
  // z = real_distribution(generator);

  if (z < C){
    // N_acceptances++;
    *site[0] = new_link;
  }

  // update the y link

  old_link = *site[1];
  new_link = old_link + gauss[int_distribution(update_generator)];

  staple1 = *site[11] - *site[6] - *site[0];
  staple2 = - *site[22] - *site[4] + *site[3];
  staple3 = *site[12] - *site[17] - *site[2];
  staple4 = - *site[29] - *site[14] + *site[15];

  // staple1 = (*ptr)->ynext->xlink - (*ptr)->xnext->ylink - (*ptr)->xlink;
  // staple2 = - (*ptr)->xprev->ynext->xlink - (*ptr)->xprev->ylink + (*ptr)->xprev->xlink;
  // staple3 = (*ptr)->ynext->tlink - (*ptr)->tnext->ylink - (*ptr)->tlink;
  // staple4 = - (*ptr)->tprev->ynext->tlink - (*ptr)->tprev->ylink + (*ptr)->tprev->tlink;

  minus_old_action = cos(old_link + staple1) + cos(old_link + staple2) + cos(old_link + staple3) + cos(old_link + staple4);
  minus_new_action = cos(new_link + staple1) + cos(new_link + staple2) + cos(new_link + staple3) + cos(new_link + staple4);

  // note that if the new action is smaller than the old action, then
  // C > 1 so we accept the new link.
  C = exp(beta * (minus_new_action-minus_old_action));

  z = real_distribution(update_generator);
  // z = real_distribution(generator);

  if (z < C){
    // N_acceptances++;
    *site[1] = new_link;
  }

  // update the t link

  old_link = *site[2];
  new_link = old_link + gauss[int_distribution(update_generator)];

  staple1 = *site[16] - *site[7] - *site[0];
  staple2 = - *site[25] - *site[5] + *site[3];
  staple3 = *site[17] - *site[12] - *site[1];
  staple4 = - *site[28] - *site[10] + *site[9];

  // staple1 = (*ptr)->tnext->xlink - (*ptr)->xnext->tlink - (*ptr)->xlink;
  // staple2 = - (*ptr)->xprev->tnext->xlink - (*ptr)->xprev->tlink + (*ptr)->xprev->xlink;
  // staple3 = (*ptr)->tnext->ylink - (*ptr)->ynext->tlink - (*ptr)->ylink;
  // staple4 = - (*ptr)->yprev->tnext->ylink - (*ptr)->yprev->tlink + (*ptr)->yprev->ylink;

  minus_old_action = cos(old_link + staple1) + cos(old_link + staple2) + cos(old_link + staple3) + cos(old_link + staple4);
  minus_new_action = cos(new_link + staple1) + cos(new_link + staple2) + cos(new_link + staple3) + cos(new_link + staple4);

  // note that if the new action is smaller than the old action, then
  // C > 1 so we accept the new link.
  C = exp(beta * (minus_new_action-minus_old_action));

  z = real_distribution(update_generator);
  // z = real_distribution(generator);

  if (z < C){
    // N_acceptances++;
    *site[2] = new_link;
  }


  // std::cout << "acceptance rate: " << double(N_acceptances) / double(N_links) << std::endl;

  return 0;
}
