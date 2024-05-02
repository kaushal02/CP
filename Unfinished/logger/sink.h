namespace spdlog {

class Sink {
  const std::string message;
 public:
  Sink(const std::string& m): message(m) {}
  void Log(const std::string& m) {
    std::cout << "[" << message << "] " << m << "\n";
  }
  ~Sink() {}
};

}  // namespace spdlog