#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <iostream>
#include <time.h>

struct ProgressBar {
  // Components
  int barWidth;
  time_t startTime, progressTime;
  // Constructor
  ProgressBar() {}
  ProgressBar(int const& barWidth)
    : barWidth(barWidth){}
  void progress(float progress);
  void start();
  void end();
};

#endif // PROGRESSBAR_H
