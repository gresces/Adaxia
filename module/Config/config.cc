/**
 * @file: module/Config/config.cc
 * @author: Gresces
 * @date: 2024-6-30
 * @brief: This file contains the Config pointer and some functions.
*/
#include "config.hpp"
#include "../Log/log.hpp"
#include <algorithm>
#include <filesystem>
#include <format>
#include <memory>
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

// The static variable pointers
std::unique_ptr<Adaxia::Config> Adaxia::Config::instance_ = nullptr;
std::unique_ptr<struct Adaxia::Setting> Adaxia::Config::settings = nullptr;

// The static content parse function.
static auto the_parse_Function(toml::parse_result tbl) -> void {
  Config::getConfig().website_.port = tbl.at_path("Website.port").value_or(toml::uint16_t());
  LogManager::Log(std::format("--CONF-- : Website open on port {}", Config::getConfig().website_.port));
}

// Config constructor function
Config::Config(std::string filepath) {
  /// Default config file paths.
  /// The parser will parse the last valid file.
  checkList.push_back(filesystem::path(filepath));

  auto filter = [](filesystem::path path) -> bool {
    return filesystem::is_regular_file(path);
  };

  // Find the result if it's regular file.
  if (auto validConfig = ranges::find_if(
    checkList.rbegin(), checkList.rend(), filter
  ); validConfig != checkList.rend()) {
    LogManager::Log(std::format("--INFO-- : Choose config file {}", validConfig->c_str()));
    // Parse the data.
    ConfigParse(validConfig->c_str(), the_parse_Function);
  }
  else {
    LogManager::Log(std::format("--ERROR-- : No config file"));
  }


}

// Parse the toml config file
auto Config::ConfigParse(std::string configFile, auto parseFunc) -> void {
  try {
    parseFunc(toml::parse_file(configFile));
  } catch (const toml::parse_error & e) {
    LogManager::Log(e.what());
  }
}

}
