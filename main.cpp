#include "common/progressbar.h"
#include "common/vector3d.h"

#include <chrono>

int main() {
  std::cout << "SSE Improvements Vector Benchmark" << std::endl;

  ProgressBar bar(70);
  bar.start();

  Vector3d vecA(100.5627283f, 20.212121221f, -32.43255667f);
  Vector3d vecB(-132.3269f, 21213.323f, -43242.434f);

  auto start_time = std::chrono::high_resolution_clock::now();

  for (unsigned int a = 0; a <= 10000; a++) {
      vecA = vecA *2;
      vecB = vecB *2;

      for (unsigned int b = 0; b <= 10000; b++) {
          Vector3d cross = crossProduct(vecA, vecB);
          float dot = dotProduct(vecA, vecB);
          normalize(&vecA);
          normalize(&vecB);
          vecA -= (dot * cross);
          vecB += (dot * cross);
      }

      bar.progress((float(a + 1) / 10000));
  }

  auto end_time = std::chrono::high_resolution_clock::now();
  auto time = end_time - start_time;

  bar.end();

  std::cout << "CPU time: " << std::chrono::duration_cast<std::chrono::milliseconds>(time).count() << "ms" << std::endl;

  return 0;
}
