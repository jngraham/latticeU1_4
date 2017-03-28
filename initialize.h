
/*
/////////////////////////////////////////////////////////////////////////////

U(1) Lattice Gauge Theory Simulator | James Graham

Declare the function to initialize all the pointers in the arrays because
it involves 30 lines of hardcode that won't look pretty in the simulate file

/////////////////////////////////////////////////////////////////////////////
*/

#include <array>

int initialize(std::array<double*,30>* site, double* links, int x, int y, int t);
