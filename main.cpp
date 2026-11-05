#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

struct Weather {
    int year = 0;
    std::string location;
    double rain = 0.0;

    bool operator<(const Weather& other) const {
        if (year != other.year) return year < other.year;
        if (location != other.location) return location < other.location;
        return rain < other.rain;
    }
};

std::ostream& operator<<(std::ostream& out, const Weather& w) {
    out << w.year << ' ' << w.location << ' ' << w.rain;
    return out;
}

std::vector<Weather> loadFromFile(const std::string& path) {
    std::ifstream in(path);
    std::vector<Weather> data;

    if (!in) {
        std::cerr << "Could not open " << path << '\n';
        return data;
    }

    std::string header;
    std::getline(in, header);

    Weather row;
    while (in >> row.year >> row.location >> row.rain) {
        data.push_back(row);
    }
    return data;
}

bool writeVector(const std::vector<Weather>& data, const std::string& path) {
    std::ofstream out(path);
    if (!out) {
        std::cerr << "Could not write " << path << '\n';
        return false;
    }
    out << "Year Location Rain\n";
    for (const auto& row : data) {
        out << row << '\n';
    }
    return true;
}

std::set<Weather> uniquify(const std::vector<Weather>& data) {
    return std::set<Weather>(data.begin(), data.end());
}

bool sortByRainAndSave(const std::set<Weather>& unique, const std::string& path) {
    std::vector<Weather> sorted(unique.begin(), unique.end());
    std::sort(sorted.begin(), sorted.end(),
              [](const Weather& a, const Weather& b) {
                  return a.rain < b.rain;
              });

    std::ofstream out(path);
    if (!out) {
        std::cerr << "Could not write " << path << '\n';
        return false;
    }
    out << "Year Location Rain\n";
    for (const auto& row : sorted) {
        out << row << '\n';
    }
    return true;
}

std::map<int, Weather> buildYearMap(const std::set<Weather>& unique) {
    std::map<int, Weather> byYear;
    for (const auto& row : unique) {
        byYear.emplace(row.year, row);
    }
    return byYear;
}

int main() {
    auto data = loadFromFile("rainfall.txt");
    std::cout << "Step 1 — Vector size: " << data.size() << '\n';
    for (const auto& row : data) {
        std::cout << "  " << row << '\n';
    }

    if (writeVector(data, "vector_out.txt")) {
        std::cout << "\nStep 2 — Wrote vector_out.txt\n";
    }

    auto unique = uniquify(data);
    std::cout << "\nStep 3 — Unique records: " << unique.size() << '\n';
    for (const auto& row : unique) {
        std::cout << "  " << row << '\n';
    }

    if (sortByRainAndSave(unique, "sorted_by_rain.txt")) {
        std::cout << "\nStep 4 — Wrote sorted_by_rain.txt\n";
    }

    auto byYear = buildYearMap(unique);
    int lookupYear = 2015;
    std::cout << "\nStep 5 — Look up year " << lookupYear << ": ";
    auto it = byYear.find(lookupYear);
    if (it != byYear.end()) {
        std::cout << it->second << '\n';
    } else {
        std::cout << "not found\n";
    }

    return 0;
}
