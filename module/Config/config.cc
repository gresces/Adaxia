/**
 * @file: module/Config/config.cc
 * @author: Gresces
 * @date: 2024-6-30
 * @brief: This file contains the Config pointer and some functions.
*/
#include "config.hpp"
#include <filesystem>
#include <ranges>
#include <vector>
#include "toml.hpp"

namespace Adaxia {
using namespace std;
using namespace std::ranges;

// If you want to change the parse order, change it here
std::vector<filesystem::path> checkList = {
  "~/.config/Adaxia/config.toml",
  "./config/config.toml"
  // the pointed config file path
};

// The static variable pointer
std::unique_ptr<Adaxia::Config> Adaxia::Config::instance_ = nullptr;

// Config constructor function
Config::Config(std::string filepath) {
  /// Default config file paths.
  /// The parser will parse the last valid file.
  checkList.push_back(filesystem::path(filepath));

  // Find the result if it's regular file.
  auto validConfig = ranges::find_if(
    checkList | views::reverse,
    [](filesystem::path path) -> bool {
      return filesystem::is_regular_file(path);
    }
  );

  // Parse the data.
  ConfigParse(*validConfig);  
}

// Parse the toml config file
auto Config::ConfigParse(std::string configFile) -> void {
  
}
}
