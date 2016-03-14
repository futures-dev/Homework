//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.2.1
// 14.03.2016 

#include "fifo.h"

#ifndef SKIPPING_SIMULATION

#include <fstream>

fifo::fifo(int seconds_per_page) : simulator(seconds_per_page) { }

void fifo::simulate(string file) {
    loadworkload(file);

    queue<event> service; // Queue for events on service
    ofstream f(OUTPUT_FILE);// Output stream
    f << WELCOME;

    // init
    total_jobs = 0;
    total_latency = 0;
    int pages_to_print = 0; // pages left to print for service in progress
    int page_ready = 0; // time in seconds while the current page is being printed.
    // when reaches {seconds_per_page}, the page is ready

    // loop until all queues processed, incrementing current time
    for (int simulation_time = 0; !(service.empty() && workload.empty()); simulation_time++) {
        event *next; // event pointer to reduce .front() calls
        // load all the events arriving this second
        while (!workload.empty() && (next = &(workload.front()))->arrival_time() == simulation_time) {
            output(f, next->getjob().getnumpages(), next->getjob().getuser(), simulation_time, true);
            total_jobs++;
            service.push(*next);
            workload.pop();
        }
        // simulate printing this second
        if (pages_to_print > 0) {
            if (++page_ready == seconds_per_page) {
                page_ready = 0;
                pages_to_print--;
            }
        }
        if (pages_to_print == 0 && !service.empty()) {
            // service is finished and have new one to start
            next = &(service.front());
            output(f, next->getjob().getnumpages(), next->getjob().getuser(), simulation_time, false);
            total_latency += simulation_time - next->arrival_time();
            pages_to_print = next->getjob().getnumpages();
            page_ready = 0;
            service.pop();
        }
    }

    print_summary(f);

    f.close();
}


void fifo::output(ofstream &simulate_ofstream, int numpages, string user, int time, bool arriving) {
    simulate_ofstream << TAB
    << (arriving ? "Arriving: " : "Servicing: ")
    << numpages
    << (numpages == 1 ? " page" : " pages")
    << " from "
    << user
    << " at "
    << time
    << " seconds"
    << "\n";
}

void fifo::print_summary(ofstream &simulate_ofstream) {
    simulate_ofstream << "\n"
    << TAB
    << "Total jobs: "
    << total_jobs
    << "\n"
    << TAB
    << "Aggregate latency: "
    << total_latency
    << " seconds"
    << "\n"
    << TAB
    << "Mean latency: "
    << total_latency / (float) total_jobs
    << " seconds"
    << "\n";
}

#else

#include <fstream>

fifo::fifo(int seconds_per_page) : simulator(seconds_per_page) { }

void fifo::simulate(string file) {
    loadworkload(file);

    service = new queue<event>; // Queue for events on service
    simulate_ofstream = new ofstream(OUTPUT_FILE); // Output stream
    *simulate_ofstream << WELCOME;

    // init
    simulation_time = 0;
    service_end_time = 0; // time when the service in progress is finished
    total_jobs = 0;
    total_latency = 0;

    // loop until all queues processed
    while (!(service->empty() && workload.empty())) {
        if (service->empty()) {
            // nothing to print: load next from workload
            load_arriving();
            // skip time till arrival time
            simulation_time = service->front().arrival_time();
            // printing began. calculate time then it ends
            service_end_time = simulation_time + seconds_per_page * service->front().getjob().getnumpages();
        }
        else {
            // have something on service
            if (workload.empty()) {
                // no more arrivals. flush the service
                while (!service->empty()) {
                    // skip to when the service in progress is finished
                    simulation_time = service_end_time;
                    load_servicing();
                }
            }
            else {
                // both not empty
                // calculate closest event: arrival or service_end
                int arriving_time = workload.front().arrival_time();
                if (arriving_time <= service_end_time) {
                    simulation_time = arriving_time;
                    load_arriving();
                }
                else {
                    simulation_time = service_end_time;
                    load_servicing();
                }
            }
        }
    }

    print_summary();

    simulate_ofstream->close();
    delete simulate_ofstream;
    delete service;

}

void fifo::load_arriving() {
    const event next(workload.front());
    workload.pop();
    output(next.getjob().getnumpages(), next.getjob().getuser(), next.arrival_time(), true);
    if (service->empty()) {
        // no service in progress yet, then new one is started
        output(next.getjob().getnumpages(), next.getjob().getuser(), next.arrival_time(), false);
    }
    // enqueue the arrived event on service
    service->push(next);
    total_jobs++;
}

void fifo::load_servicing() {
    // the service if finished
    service->pop();
    if (!service->empty()) {
        // new one is started
        const event next(service->front());
        service_end_time += next.getjob().getnumpages() * seconds_per_page;
        total_latency += simulation_time - next.arrival_time();
        output(next.getjob().getnumpages(), next.getjob().getuser(), simulation_time, false);
    }
}

void fifo::output(int numpages, string user, int time, bool arriving) {
    *simulate_ofstream << TAB
    << (arriving ? "Arriving: " : "Servicing: ")
    << numpages
    << (numpages == 1 ? " page" : " pages")
    << " from "
    << user
    << " at "
    << time
    << " seconds"
    << "\n";
}

void fifo::print_summary() {
    *simulate_ofstream << "\n"
    << TAB
    << "Total jobs: "
    << total_jobs
    << "\n"
    << TAB
    << "Aggregate latency: "
    << total_latency
    << " seconds"
    << "\n"
    << TAB
    << "Mean latency: "
    << total_latency / (float) total_jobs
    << " seconds"
    << "\n";
}

#endif // SKIPPING SIMULATION