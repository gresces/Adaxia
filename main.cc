/**
 * @file: main.cc
 * @author: Gresces
 * @brief: This file contains the program entry point.
*/
#include <format>
#include "module/Log/log.hpp"
#include "module/Config/config.hpp"

using namespace Adaxia;

class server {
public:
  auto run() -> void {
    int a = 20;
    Adaxia::LogManager::LogInit("adaxia.log", a);
    LogManager::Log(std::format("--INFO-- : Adaxia starting..."));
    Adaxia::Config::ConfigInit("./config.toml");
  }
  ~server() {
    Adaxia::Config::ConfigDelete();
    Adaxia::LogManager::LogDelete();
  }
};

auto main(int argc, char **argv) -> int {

  server app;
  app.run();

  return 0;
}
