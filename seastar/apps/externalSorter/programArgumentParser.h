#ifndef programArgumentParser_h
#define programArgumentParser_h
#include "boost/program_options.hpp"
#include <iostream>
#include <stdio.h>
#include <string>

namespace po = boost::program_options;
class programArgumentParser {
private:
  std::string filePath;
  double memorySize;

public:
  programArgumentParser(int argc, char **argv) noexcept(true)
      : filePath(""), memorySize() {
    po::variables_map vm;
    po::options_description description("Program Usage");
    try {
      description.add_options()("help,h", po::value<std::string>()->required(),
                                "Program ussage")(
          "memorySize,memSize", po::value<double>()->required(),
          "Size of available memory in kbytes")(
          "filePath,fPath", po::value<std::string>()->required(),
          "Absolute path to file");
      po::store(po::command_line_parser(argc, argv).options(description).run(),
                vm);
      po::notify(vm);
      this->filePath = vm["filePath"].as<std::string>();
      this->memorySize = vm["memorySize"].as<double>();
    } catch (...) {
      if (vm.count("help")) {
        std::cout << description;
      }
    }
  }
};
#endif // programArgumentParser_h
