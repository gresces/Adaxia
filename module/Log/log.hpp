/**
 * @file: module/Log/log.hpp
 * @author: Gresces
 * @date: 2024-7-8
 * @brief: This file contains the log class
*/

#include <cassert>
#include <filesystem>
#include <memory>
#include <istream>
#include <string>
#include <vector>

namespace Adaxia {

using std::istream;

/// This class is designed to manage the logs.
class LogManager{
public:
  /// There are some log request collectors.
  
  // Write to queue
  static auto LogFile(const std::string& content) -> void;
  
  // Write to console(std::cout)
  static auto LogConsole(const std::string& content) -> void;

  // Write to console and file.
  static auto Log(const std::string& content) -> void {
    LogFile(content);
    LogConsole(content);
  }

private:
  auto writeToFile() -> void;
  auto writeToFileEnforce() -> void;

private:
  typedef struct {
    std::string date;
    std::string content;
  } logRequest;

private:
  /// This is the private variable for 
  std::filesystem::path logFilePath = 
    std::filesystem::path("./adaxia.log");
  /// logBatchSize is the queue size.
  int logBatchSize = 20;
  /// log count
  int logCount;
  /// requestQueue stores temporary logs.
  static std::shared_ptr<std::vector<logRequest>> requestQueue;

// Singleton
public:
  static auto LogInit(const std::string& filepath, int& batchSize) -> void {
    LogManager::instance_.reset(new LogManager(filepath, batchSize));
  }
  static auto LogDelete() -> void {
    LogManager::getInstance().writeToFileEnforce();
    LogManager::instance_.reset();
  }
  static auto getInstance() -> LogManager{
    assert(instance_);
    return *instance_;
  }

private:
  LogManager(const std::string&, int&);
  auto operator=(const LogManager&) -> LogManager& = delete;

private:
  static std::unique_ptr<LogManager> instance_;
};
}

