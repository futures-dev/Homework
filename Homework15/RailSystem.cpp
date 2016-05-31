#pragma warning (disable:4786)
#pragma warning (disable:4503)

#include "RailSystem.h"
#include <set>

void RailSystem::reset(void) {

    for (auto it = cities.begin(); it != cities.end(); it++) {
        auto newCity = new City(it->second->name);
        delete it->second;
        it->second = newCity;
    }

}

RailSystem::RailSystem(string const &filename) {

    load_services(filename);
}

void RailSystem::load_services(string const &filename) {

    ifstream inf(filename.c_str());
    string from, to;
    int fee, distance;

    while (inf.good()) {

        // Read in the from city, to city, the fee, and distance.
        inf >> from >> to >> fee >> distance;

        if (inf.good()) {
            cin >> from >> to >> fee >> distance;
            auto c = cities.find(from);
            if (c == cities.end()) {
                cities.insert(make_pair(from, new City(from)));
            }
            c = cities.find(to);
            if (c == cities.end()) {
                cities.insert(make_pair(to, new City(to)));
            }
            outgoing_services[from].push_back(new Service(to, fee, distance));
        }
    }

    inf.close();
}

RailSystem::~RailSystem(void) {

    for (auto it = cities.begin(); it != cities.end(); it++) {
        delete it->second;
    }

    for (auto it = outgoing_services.begin(); it != outgoing_services.end(); it++) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            delete *it2;
        }
    }

}

void RailSystem::output_cheapest_route(const string &from,
                                       const string &to, ostream &out) {

    reset();
    pair<int, int> totals = calc_route(from, to);

    if (totals.first == INT_MAX) {
        out << "There is no route from " << from << " to " << to << "\n";
    } else {
        out << "The cheapest route from " << from << " to " << to << "\n";
        out << "costs " << totals.first << " euros and spans " << totals.second
        << " kilometers\n";
        cout << recover_route(to) << "\n\n";
    }
}

bool RailSystem::is_valid_city(const string &name) {

    return cities.count(name) == 1;
}

pair<int, int> RailSystem::calc_route(string from, string to) {
    // You can use another container
    set<City *, Cheapest> candidates;

    // TODO: Implement Dijkstra's shortest path algorithm to
    // find the cheapest route between the cities

    candidates.insert(cities[from]);
    while (!candidates.empty()) {
        auto currentCity = *candidates.begin();
        candidates.erase(candidates.begin());
        auto &currentServices = outgoing_services[currentCity->name];
        currentCity->visited = true;
        for (auto it = currentServices.begin(); it != currentServices.end(); it++) {
            auto &service = *it;
            auto city = cities[service->destination];
            if (city->total_distance > currentCity->total_distance + service->distance) {
                candidates.erase(city);
                city->total_distance = currentCity->total_distance + service->distance;
                city->total_fee = currentCity->total_fee + service->fee;
                city->from_city = currentCity->name;
            }
            candidates.insert(city);
        }
    }

    // Return the total fee and total distance.
    // Return (INT_MAX, INT_MAX) if not path is found.
    if (cities[to]->visited) {
        return pair<int, int>(cities[to]->total_fee, cities[to]->total_distance);
    }
    else {
        return pair<int, int>(INT_MAX, INT_MAX);
    }
}

string RailSystem::recover_route(const string &city) {

    auto currentCity = cities[city];
    while (currentCity->from_city != "") {
        currentCity = cities[currentCity->from_city];
    }

    return currentCity->name;
}


Route RailSystem::getCheapestRoute(const string &from, const string &to) {
    assert(is_valid_city(from));
    assert(is_valid_city(to));
    reset();
    pair<int, int> p = calc_route(from, to);
    return Route(from, to, p.first, p.second);
}