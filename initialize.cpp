
/*
/////////////////////////////////////////////////////////////////////////////

U(1) Lattice Gauge Theory Simulator | James Graham

Write the function to initialize all the pointers in the arrays because
it involves 30 lines of hardcode that won't look pretty in the simulate file

/////////////////////////////////////////////////////////////////////////////
*/

#include <array>
#include <iostream>
#include <typeinfo>

#include "globals.h"
#include "initialize.h"

// gotta pass in the pointer so we can actually change the value in the array
int initialize(std::array<double*,30>* site, double* links, int x, int y, int t){

  int xthis = 3*x;
  int xnext = 3*((x+1)%Lx);
  int xprev = 3*((x+Lx-1)%Lx);

  int ythis = 3*Lx*y;
  int ynext = 3*((y+1)%Ly);
  int yprev = 3*((y+Ly-1)%Ly);

  int tthis = 3*Lx*Ly*t;
  int tnext = 3*((t+1)%Lt);
  int tprev = 3*((t+Lt-1)%Lt);

  // I've written which link goes where in legend.txt

  (*site)[0] = links + xthis + ythis + tthis;
  (*site)[1] = links + xthis + ythis + tthis + 1;
  (*site)[2] = links + xthis + ythis + tthis + 2;
  (*site)[3] = links + xprev + ythis + tthis;
  (*site)[4] = links + xprev + ythis + tthis + 1;
  (*site)[5] = links + xprev + ythis + tthis + 2;
  (*site)[6] = links + xnext + ythis + tthis + 1;
  (*site)[7] = links + xnext + ythis + tthis + 2;
  (*site)[8] = links + xthis + yprev + tthis;
  (*site)[9] = links + xthis + yprev + tthis + 1;
  (*site)[10] = links + xthis + yprev + tthis + 2;
  (*site)[11] = links + xthis + ynext + tthis;
  (*site)[12] = links + xthis + ynext + tthis + 2;
  (*site)[13] = links + xthis + ythis + tprev;
  (*site)[14] = links + xthis + ythis + tprev + 1;
  (*site)[15] = links + xthis + ythis + tprev + 2;
  (*site)[16] = links + xthis + ythis + tnext;
  (*site)[17] = links + xthis + ythis + tnext + 1;
  (*site)[18] = links + xnext + yprev + tthis + 1;
  (*site)[19] = links + xnext + ythis + tprev + 2;
  (*site)[20] = links + xprev + yprev + tthis;
  (*site)[21] = links + xprev + yprev + tthis + 1;
  (*site)[22] = links + xprev + ynext + tthis;
  (*site)[23] = links + xprev + ythis + tprev;
  (*site)[24] = links + xprev + ythis + tprev + 2;
  (*site)[25] = links + xprev + ythis + tnext;
  (*site)[26] = links + xthis + yprev + tprev + 1;
  (*site)[27] = links + xthis + yprev + tprev + 2;
  (*site)[28] = links + xthis + yprev + tnext + 1;
  (*site)[29] = links + xthis + yprev + tnext + 2;

  // std::cout << *(*site)[0] << std::endl;


  return 0;
}
