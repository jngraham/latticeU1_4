#include <iostream>
#include <stdlib.h>
#include <array>

int fun(std::array<int,2>* a);

int main(){

  std::array<int, 2>* foo;

  (*foo)[0] = 2;
  (*foo)[1] = 5;

  fun(foo);

  std::cout << (*foo)[1] << std::endl;
}

int fun(std::array<int,2>* a){

  (*a)[1] += 1;

  return 0;
}
