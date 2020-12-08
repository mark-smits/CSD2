#include <iostream>

/*
  Assignment: complete this program by putting your code in all the locations
    that say -- your code here --

  Make sure that the program compiles and builds and check the output
    after every change.

  Tip: before you look at the output, always think ahead what you expect to
    see and then check if your assumption was correct.
 */

int main()
{
char letter = 97; // find this in the ASCII table (type 'man ascii')
char *letterpointer;

  std::cout << "Contents of the variable letter: ";
  std::cout << letter << "\n";

  letterpointer = &letter;
  std::cout << "Contents of letterpointer: ";
  std::cout << letterpointer << '\n';

  std::cout << "Contents of what letterpointer points to: ";
  std::cout << *letterpointer << '\n';

  *letterpointer = 'b';
  std::cout << "The variabele letter has gotten a new value through letterpointer.\n";
  std::cout << "Contents of what letterpointer points to: ";
  std::cout << *letterpointer << '\n';

  std::cout << "Contents of the variable letter: ";
  std::cout << letter << '\n';


  /*
   * Create the necessary pointer(s) and use them
   */

  unsigned short year = 2019;
  std::cout << "Contents of the variabele year: ";
  std::cout << year << '\n';

  // create a pointer to year
  short unsigned int *yearpointer = &year;

  std::cout << "Contents of yearpointer: ";
  std::cout << yearpointer << '\n';

  std::cout << "Contents of what yearpointer points to: ";
  std::cout << *yearpointer << '\n';

  // give year a new value via yearpointer
  *yearpointer = 2000;

  std::cout << "Contents of the variabele year: ";
  std::cout << year << '\n';


  // create another pointer to year, named anotheryearpointer
  short unsigned int *anotheryearpointer = &year;

  std::cout << "Contents of anotheryearpointer: ";
  std::cout << anotheryearpointer << '\n';

  std::cout << "Contents of what anotheryearpointer points to: ";
  std::cout << *anotheryearpointer << "\n";

  // give year a new value via anotheryearpointer
  *anotheryearpointer = 2005;

  std::cout << "Contents of year: ";
  std::cout << year << '\n';

  std::cout << "Contents of what anotheryearpointer points to: ";
  std::cout << *anotheryearpointer << "\n";

  anotheryearpointer++;

  std::cout << "Contents of anotheryearpointer after ++: ";
  std::cout << anotheryearpointer << "\n";


} // main()
