/**
 * @file: module/Config/config.hpp
 * @author: Gresces
 * @date: 2024-6-30
 * @brief: This file contains the singletom class <Config>
*/

#pragma once
#include <cassert>
#include <memory>
#include <string>

namespace Adaxia {

class Config {
public:
  static auto ConfigParse(std::string configFile) -> void;

// Singleton
public:
  auto ConfigInit(std::string filepath) -> void {
    Config::instance_.reset(new Config(filepath));
  }
  auto ConfigDelete() -> void {
    Config::instance_.reset();
  }
  auto getInstance() -> Config {
    assert(instance_);
    return *instance_;
  }

private:
  Config(std::string);
  auto operator=(const Config&) -> Config& = delete;
  
private:
  static std::unique_ptr<Config> instance_;
};

}
