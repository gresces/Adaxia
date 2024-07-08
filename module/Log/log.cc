/**
 * @file: module/Log/log.cc
 * @author: Gresces
 * @date: 2024-7-8
 * @brief: This file contains how the program log info
*/

#include "log.hpp"
#include <cstdlib>
#include <ctime>
#include <format>
#include <fstream>
#include <iostream>

namespace Adaxia {
// The Log Factory locates here.
std::unique_ptr<LogManager> LogManager::instance_ = nullptr;
std::shared_ptr<std::vector<LogManager::logRequest>> 
  LogManager::requestQueue = nullptr;

LogManager::LogManager(const std::string& filepath, int& batchSize) {
  if (!std::filesystem::is_regular_file(filepath) && std::filesystem::exists(filepath)) {
    std::cout << "[[ERROR]] : not a regular file: " << filepath << std::endl;
    std::exit(1);
  }
  LogManager::logBatchSize = batchSize;
  LogManager::logFilePath = std::filesystem::path(filepath);
  requestQueue = std::make_shared<std::vector<logRequest>>();
}

auto LogManager::LogFile(const std::string& content) -> void {
  // get time then add to log list.
  auto now = time(0);
  logRequest req;
  req.content = content;
  req.date = ctime(&now);
  LogManager::getInstance().requestQueue->push_back(req);
  LogManager::getInstance().writeToFile();
}

auto LogManager::LogConsole(const std::string& content) -> void {
  std::cout << std::format("{}", content) << std::endl;
}

auto LogManager::writeToFile() -> void {
  // if full, then write and clear.
  logCount++;
  if (logCount == logBatchSize) {
    writeToFileEnforce();
    LogManager::requestQueue->clear();
    logCount = 0;
  }
}

auto LogManager::writeToFileEnforce() -> void {
  std::ofstream fs;
  fs.open(logFilePath.c_str(), std::ios::app | std::ios::out);
  if (!fs.is_open()) {
    std::cout << "[[PANIC]] : Open log file failed: " << logFilePath <<std::endl; 
  }
  for (const auto & log : *LogManager::requestQueue) {
    fs << log.date << log.content << std::endl;
  }
  fs.close();
  LogManager::requestQueue->clear();
  logCount = 0;
}

}

