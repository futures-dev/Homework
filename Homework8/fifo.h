//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.2.1
// 14.03.2016

#ifndef HOMEWORK_FIFO_H
#define HOMEWORK_FIFO_H

/*
 * Сначала реализовал ленивый simulate (SKIPPING_SIMULATION),
 * который сразу прыгает во времени на следующее событие (Arriving/Servicing),
 * а не прокручивает "секунды". В реальном мире такая
 * симуляция должна быть быстрее и, соотв., более применима.
 *
 * Без дефайна реализация по ТЗ, нижнюю можно не проверять.
 *
 */

//#define SKIPPING_SIMULATION
#ifndef SKIPPING_SIMULATION

#include "simulator.h"

class fifo : public simulator {

public:
    /*
     * Simulates the *.run file input and creates output.out
     */
    virtual void simulate(string file);

    /*
     * Construct fifo with set pages printing rate
     */
    fifo(int seconds_per_page);

private:
    // Format const
    const char *WELCOME = "FIFO Simulation \n\n";
    const char *TAB = "      ";
    const char *OUTPUT_FILE = "output.out";

    // Algo stats
    int total_jobs;
    int total_latency;

    /*
     * Writes event info into previously opened output stream
     */
    inline void output(ofstream &f, int numpages, string user, int seconds, bool arriving);

    /*
     * Writes simulation stats into previously opened output stream
     */
    inline void print_summary(ofstream &f);

};

#else

#include "simulator.h"

class fifo : public simulator {

public:
    /*
     * Simulates the *.run file input and creates output.out
     */
    virtual void simulate(string file);

    /*
     * Construct fifo with set pages printing rate
     */
    fifo(int i);

private:
    // Format const
    const char *WELCOME = "FIFO Simulation \n\n";
    const char *TAB = "      ";
    const char *OUTPUT_FILE = "output.out";

    // Algo stats and variables
    int simulation_time;
    int service_end_time;
    int total_jobs;
    int total_latency;
    std::queue<event> *service;
    ofstream *simulate_ofstream;

    /*
     * Pop arriving event from workload
     */
    void load_arriving();

    /*
     * Pop event from service queue
     */
    void load_servicing();

    /*
     * Writes event info into previously opened output stream
     */
    inline void output(int numpages, string user, int seconds, bool arriving);

    /*
     * Writes simulation stats into previously opened output stream
     */
    inline void print_summary();

};

#endif // SKIPPING_SIMULATION

#endif //HOMEWORK_FIFO_H
