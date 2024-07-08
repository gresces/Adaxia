/**
 * @file: main.cc
 * @author: Gresces
 * @brief: This file contains the program entry point.
*/
#include <format>
#include "module/Log/log.hpp"

using namespace Adaxia;

class server {
public:
  auto run() -> void {
    int a = 20;
    Adaxia::LogManager::LogInit("adaxia.log", a);
  }
  ~server() {
    Adaxia::LogManager::LogDelete();
  }
};

auto main(int argc, char **argv) -> int {

  server app;
  app.run();

  LogManager::Log(std::format("[[INFO]] : Adaxia starting..."));
  
  return 0;
}
