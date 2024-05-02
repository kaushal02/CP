#include "sink.h"

class FileLogger {
  static std::shared_ptr<spdlog::Sink> sink;
  std::string prefix;
 public:
  FileLogger(const std::string& p): prefix(p) {}
  static bool CreateSink(const std::string& m) {
    sink = std::make_shared<spdlog::Sink>(m); // should be executed only once
    std::cout << "created sink with message " << m << "\n";
    return true;
  }
  void Log(const std::string& s) {
    sink->Log(prefix + s);
  }
};
