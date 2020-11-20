#include <string>

class Auto
{
public:
  Auto(int jaartalIn, float lengteIn, std::string naamIn); //construcor
  ~Auto(); //deconstructor
  void geefEigenschappen();
private:
  int jaartal;
  float lengte;
  std::string naam;
};
