#include "progressbar.h"

#include <iostream>

void ProgressBar::progress(float progress) {
    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
}

void ProgressBar::start() {
    progress(0);
}

void ProgressBar::end() {
    progress(1.0f);
    std::cout << std::endl;
}
