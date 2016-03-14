//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 14.03.2016 

#include <fstream>
#include "fifo.h"

fifo::fifo(int seconds_per_page) : simulator(seconds_per_page) { }

void fifo::simulate(string file) {
    loadworkload(file);
    int n = workload.size();
    ofstream f("output.out");
    f << "FIFO Simulation\n\n";
    for (int i = 0; i < n; i++) {
        f << TAB <<
    }
}
