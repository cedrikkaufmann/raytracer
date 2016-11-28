#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <iostream>

struct ProgressBar {
  // Components
  int barWidth;

  // Constructor
  ProgressBar() {}
  ProgressBar(int const& barWidth)
    : barWidth(barWidth){}

  void progress(float progress);
  void end();
};

#endif // PROGRESSBAR_H
