//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 14.03.2016

#ifndef HOMEWORK_FIFO_H
#define HOMEWORK_FIFO_H

#include "simulator.h"

class fifo : public simulator {

public:
    virtual void simulate(string file);

    fifo(int i);

private:
    std::queue queue;
    const auto TAB = "      ";
};


#endif //HOMEWORK_FIFO_H
