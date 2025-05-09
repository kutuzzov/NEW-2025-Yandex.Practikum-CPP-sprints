#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

int EffectiveCount(const vector<int>& v, int n, int i) {
    // место для вашего решения
    int result;
    int64_t exp_response = static_cast<int64_t>(v.size()) * (i + 1) / (n + 1);

    if (exp_response <= log2(v.size())) {
        cout << "Using find_if"s << endl;
        auto it = find_if(v.begin(), v.end(), [&i](int x) { return x > i; });
        result = it - v.begin();
    }
    else {
        cout << "Using upper_bound"s << endl;
        auto it = upper_bound(v.begin(), v.end(), i);
        result = it - v.begin();
    }

    return result;
}

int main() {
    static const int NUMBERS = 1'000'000;
    static const int MAX = 1'000'000'000;

    mt19937 r;
    uniform_int_distribution<int> uniform_dist(0, MAX);

    vector<int> nums;
    for (int i = 0; i < NUMBERS; ++i) {
        int random_number = uniform_dist(r);
        nums.push_back(random_number);
    }
    sort(nums.begin(), nums.end());

    int i;
    cin >> i;
    int result = EffectiveCount(nums, MAX, i);
    cout << "Total numbers before "s << i << ": "s << result << endl;
}
