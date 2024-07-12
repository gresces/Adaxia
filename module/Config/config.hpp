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

struct Setting {
  // Website
  struct {
    uint16_t port;
  } website_;
  // How to parse

};

class Config {
private:
  static std::unique_ptr<struct Setting> settings;

public:
  static auto getConfig() -> struct Setting& {
    assert(settings);
    return *settings;
  }

private:
  static auto ConfigParse(std::string configFile, auto parseFunc) -> void;

// Singleton
public:
  static auto ConfigInit(std::string filepath) -> void {
    Config::settings.reset(new struct Setting);
    Config::instance_.reset(new Config(filepath));
  }
  static auto ConfigDelete() -> void {
    Config::settings.reset();
    Config::instance_.reset();
  }
  static auto getInstance() -> Config {
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
