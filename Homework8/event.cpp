#include <iostream>

using namespace std;

#include "event.h"

event::event(job j, int wait_until) : j(j), wait_until(wait_until) { }

event::event() : wait_until(-1) { }

job event::getjob() const {
    return j;
}


int event::arrival_time() const {
    return wait_until;
}

istream &operator>>(istream &stream, event &e) {
    stream >> e.wait_until;
    stream >> e.j;
    return stream;
}


ostream &operator<<(ostream &stream, event &e) {
    stream << e.wait_until << " " << e.j;
    return stream;
}

