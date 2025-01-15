#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses,
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator>>(istream& is, Query& q) {
    // Реализуйте эту функцию
    string type;
    is >> type;
    if (type == "NEW_BUS"s) {
        q.type = QueryType::NewBus;
        is >> q.bus;
        int stop_count;
        is >> stop_count;
        q.stops.resize(stop_count);
        for (size_t i = 0; i < stop_count; ++i) {
            is >> q.stops[i];
        }
    }
    else if (type == "BUSES_FOR_STOP"s) {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }
    else if (type == "STOPS_FOR_BUS"s) {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }
    else if (type == "ALL_BUSES"s) {
        q.type = QueryType::AllBuses;
    }

    return is;
}

// Структура выдачи списка автобусов через остановку.
struct BusesForStopResponse {
    // Наполните полями эту структуру
    vector<string> buses;
};

ostream& operator<<(ostream& os, const BusesForStopResponse& r) {
    // Реализуйте эту функцию
    if (r.buses.empty()) {
        os << "No stop"s;
    }
    else {
        bool is_first = true;
        for (const string& bus : r.buses) {
            if (!is_first) {
                os << " "s;
            }
            is_first = false;
            os << bus;
        }
    }
    return os;
}

// Структура выдачи описания остановок для маршрута автобуса.
struct StopsForBusResponse {
    // Наполните полями эту структуру
    string bus;
    vector<string> stops;
    map<string, vector<string>> stops_to_buses;
};

ostream& operator<<(ostream& os, const StopsForBusResponse& r) {
    // Реализуйте эту функцию
    if (r.bus.empty()) {
        os << "No bus"s;
    }
    else {
        bool is_first = true;
        for (const string& stop : r.stops) {
            if (!is_first) {
                os << endl;
            }
            is_first = false;
            os << "Stop "s << stop << ":"s;
            if (r.stops_to_buses.at(stop).size() == 1) {
                os << " no interchange"s;
            }
            else {
                for (const string& other_bus : r.stops_to_buses.at(stop)) {
                    if (r.bus != other_bus) {
                        os << " "s << other_bus;
                    }
                }
            }
        }
    }
    return os;
}

// Структура выдачи описания всех автобусов.
struct AllBusesResponse {
    // Наполните полями эту структуру
    map<string, vector<string>> buses_to_stops;
};

ostream& operator<<(ostream& os, const AllBusesResponse& r) {
    // Реализуйте эту функцию
    if (r.buses_to_stops.empty()) {
        os << "No buses"s;
    }
    else {
        bool is_first = true;
        for (const auto& bus_item : r.buses_to_stops) {
            if (!is_first) {
                os << endl;
            }
            is_first = false;
            os << "Bus "s << bus_item.first << ":"s;
            for (const string& stop : bus_item.second) {
                os << " "s << stop;
            }
        }
    }
    return os;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        // Реализуйте этот метод
        buses_to_stops_[bus] = stops;
        for (const string& stop : stops) {
            stops_to_buses_[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        // Реализуйте этот метод
        if (!stops_to_buses_.count(stop)) {
            return {};
        }
        return { stops_to_buses_.at(stop) };
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        // Реализуйте этот метод
        if (!buses_to_stops_.count(bus)) {
            return {};
        }
        return { bus, buses_to_stops_.at(bus), stops_to_buses_ };
    }

    AllBusesResponse GetAllBuses() const {
        // Реализуйте этот метод
        return { buses_to_stops_ };
    }

private:
    map<string, vector<string>> buses_to_stops_;
    map<string, vector<string>> stops_to_buses_;
};

// Реализуйте функции и классы, объявленные выше, чтобы эта функция main
// решала задачу "Автобусные остановки"

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::StopsForBus:
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::AllBuses:
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }
}
