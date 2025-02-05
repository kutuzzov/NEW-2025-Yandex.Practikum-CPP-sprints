#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(RandomIt range_begin, RandomIt range_end, string prefix) {
    // напишите реализацию
    string next_prefix = prefix;
    ++next_prefix[next_prefix.size() - 1];

    return make_pair(lower_bound(range_begin, range_end, prefix),
                     lower_bound(range_begin, range_end, next_prefix));
}

int main() {
    const vector<string> sorted_strings = { "moscow", "motovilikha", "murmansk" };
    const auto mo_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
    for (auto it = mo_result.first; it != mo_result.second; ++it) {
        cout << *it << " ";
    }
    cout << endl;
    const auto mt_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
    cout << (mt_result.first - begin(sorted_strings)) << " " << (mt_result.second - begin(sorted_strings)) << endl;
    const auto na_result = FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
    cout << (na_result.first - begin(sorted_strings)) << " " << (na_result.second - begin(sorted_strings)) << endl;
    return 0;
}
