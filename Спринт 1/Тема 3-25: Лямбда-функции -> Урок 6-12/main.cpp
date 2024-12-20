#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int CountAndAddNewDogs(const vector<string>& new_dogs, const map<string, int>& max_amount,
                       map<string, int>& shelter) {
    return count_if(new_dogs.begin(), new_dogs.end(), [&shelter, &max_amount](const string& dog) {
        int& current_amount = shelter[dog];
        if (current_amount < max_amount.at(dog)) {
            ++current_amount;
            return true;
        } else {
            return false;
        }
    });
}

int main() {
    map<string, int> shelter {
        {"shepherd"s, 1},
        {"corgi"s, 3},
    };

    map<string, int> max_amount {
        {"shepherd"s, 2},
        {"corgi"s, 3},
        {"shiba inu"s, 1},
    };

    cout << CountAndAddNewDogs({"shepherd"s, "shiba inu"s, "shiba inu"s, "corgi"s}, max_amount, shelter) << endl;
}
