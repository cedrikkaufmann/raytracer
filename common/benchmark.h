#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <chrono>

struct Timer {
  // Constructor
  Timer() {}

  inline void start() { this->t0 = std::chrono::high_resolution_clock::now(); }
  inline void end() {
      this->t1 = std::chrono::high_resolution_clock::now();
      this->duration = this->t1 - this->t0;
  }

  inline std::chrono::seconds getSeconds() { return std::chrono::duration_cast<std::chrono::seconds>(this->duration); }
  inline std::chrono::milliseconds getMilliseconds() { return std::chrono::duration_cast<std::chrono::milliseconds>(this->duration); }
  inline std::chrono::microseconds getMicroseconds() { return std::chrono::duration_cast<std::chrono::microseconds>(this->duration); }

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> t0, t1;
  std::chrono::duration<float> duration;
};

#endif // BENCHMARK_H
