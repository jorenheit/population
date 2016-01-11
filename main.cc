#include <iostream>
#include <cstdlib>

void run(int nStart, int nYears);

int main(int argc, char **argv)
try
{
    if (argc != 3)
    {
        std::cerr << "Syntax: " << argv[0] << " [nStart] [nYears]\n";
        return 1;
    }

   std::srand(time(0));
   std::srand(0);
   run(std::stoi(argv[1]), std::stoi(argv[2]));
}
catch (std::string const &msg)
{
    std::cerr << "Error: " << msg << '\n';
}
