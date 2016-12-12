#include "progressbar.h"

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
    startTime = clock();
}

void ProgressBar::end() {
    progressTime = (clock() - startTime) / CLOCKS_PER_SEC;
    progress(1.0f);
    std::cout << std::endl;
}
