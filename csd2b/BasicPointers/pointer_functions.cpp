#include <iostream>

int kwadraat(int getal_in) {
  return getal_in*getal_in;
}

void kwadraatPointer(int* getal_in) {
  *getal_in = *getal_in * *getal_in;
}

void kwadraatReference(int& getal_in) {
  getal_in = getal_in * getal_in;
}


int main() {
  int getal = 2;
  std::cout << "getal: " << getal << '\n';
  std::cout << "kwadraat via value: " << kwadraat(getal) << '\n';

  std::cout << "getal: " << getal << '\n';
  kwadraatPointer(&getal);
  std::cout << "kwadraat via pointer: " << getal << '\n';

  std::cout << "getal: " << getal << '\n';
  kwadraatReference(getal);
  std::cout << "kwadraat via reference: " << getal << '\n';
}
