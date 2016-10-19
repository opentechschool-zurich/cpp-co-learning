#include <mlpack/core.hpp>

using namespace mlpack;

int main(int argc, char** argv)
{
  CLI::ParseCommandLine(argc, argv);
  Log::Debug << "Compiled with debugging symbols." << std::endl;
  Log::Info << "Some test informational output." << std::endl;
  Log::Warn << "A warning!" << std::endl;
  Log::Fatal << "Program has crashed." << std::endl;
  Log::Warn << "Made it!" << std::endl;
}
