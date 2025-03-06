#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using filesystem::path;

path operator""_p(const char* data, std::size_t sz) {
    return path(data, data + sz);
}

// напишите эту функцию
void PrintTree(ostream& dst, const path& p, const filesystem::file_status& status, int offset) {
    dst << string(offset, ' ') << p.filename().string() << endl;
    
    vector<pair<path, filesystem::file_status>> pathes;

    if (status.type() == filesystem::file_type::directory) {
        for (const auto& dir_entry : filesystem::directory_iterator(p)) {
            pathes.push_back({ dir_entry.path(), dir_entry.status() });
        }
        sort(pathes.begin(), pathes.end(), 
            [](const auto& lhs, const auto& rhs) { 
                return lhs.first.filename().string() > rhs.first.filename().string();
            });
        for (const auto& [name, stat] : pathes) {
            PrintTree(dst, name, stat, offset + 2);
        }
    }
}

void PrintTree(ostream& dst, const path& p) {
    PrintTree(dst, p, filesystem::status(p), 0);
}

int main() {
    error_code err;
    filesystem::remove_all("test_dir", err);
    filesystem::create_directories("test_dir"_p / "a"_p, err);
    filesystem::create_directories("test_dir"_p / "b"_p, err);

    ofstream("test_dir"_p / "b"_p / "f1.txt"_p);
    ofstream("test_dir"_p / "b"_p / "f2.txt"_p);
    ofstream("test_dir"_p / "a"_p / "f3.txt"_p);

    ostringstream out;
    PrintTree(out, "test_dir"_p);
    assert(out.str() ==
        "test_dir\n"
        "  b\n"
        "    f2.txt\n"
        "    f1.txt\n"
        "  a\n"
        "    f3.txt\n"s
    );
}
