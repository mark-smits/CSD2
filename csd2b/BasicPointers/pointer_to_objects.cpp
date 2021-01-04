#include <iostream>

class SimpleClass
{
public:
  SimpleClass();
  SimpleClass(float par);
  ~SimpleClass();
  void setParam(float par);
  float getParam();
private:
  float param;
};

SimpleClass::SimpleClass() {}

SimpleClass::SimpleClass(float par)
{
  this->param = par;
}

SimpleClass::~SimpleClass()
{
}

void SimpleClass::setParam(float par)
{
  this->param = par;
}

float SimpleClass::getParam()
{
  return param;
}

int main ()
{
  SimpleClass simpel[50];
  SimpleClass *simpelpointer[50];
  for (int i = 0; i<50; i++)
  {
    simpel[i] = SimpleClass(i);
    simpelpointer[i] = &simpel[i];
    std::cout << "simpel " << i << " param: " << simpelpointer[i]->getParam() << '\n';
  }
  return 0;
}
