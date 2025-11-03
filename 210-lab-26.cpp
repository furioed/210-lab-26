// COMSC-210 | Lab 26 | Mamadou Sissoko
// IDE used: Visual Studio Code
// Enhanced data structure races

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <algorithm>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// Read data into container
template <typename T>
long long raceRead(T& container, const vector<string>& data) {
    auto start = high_resolution_clock::now();
    for (const auto& s : data)
        container.insert(container.end(), s); // vector/list
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

// Specialization for set
long long raceRead(set<string>& st, const vector<string>& data) {
    auto start = high_resolution_clock::now();
    for (const auto& s : data)
        st.insert(s);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

// Sort vector/list
template <typename T>
long long raceSort(T& container) {
    auto start = high_resolution_clock::now();
    container.sort(); // list
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

// Sort vector specialization
long long raceSort(vector<string>& vec) {
    auto start = high_resolution_clock::now();
    sort(vec.begin(), vec.end());
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

// Set is already sorted
long long raceSort(set<string>&) {
    return -1;
}

// Insert in middle
template <typename T>
long long raceInsert(T& container, const string& value) {
    auto start = high_resolution_clock::now();
    auto it = container.begin();
    advance(it, container.size() / 2);
    container.insert(it, value);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

// Insert for set
long long raceInsert(set<string>& st, const string& value) {
    auto start = high_resolution_clock::now();
    st.insert(value);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

// Delete middle element
template <typename T>
long long raceDelete(T& container) {
    auto start = high_resolution_clock::now();
    auto it = container.begin();
    advance(it, container.size() / 2);
    container.erase(it);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

// Delete for set
long long raceDelete(set<string>& st) {
    auto start = high_resolution_clock::now();
    auto it = st.begin();
    advance(it, st.size() / 2);
    st.erase(it);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

int main() {
    vector<string> rawData;
    ifstream fin("codes.txt"); // For the data file
    if (!fin) {
        cerr << "Cannot open data file. Please check the file and try again.\n";
        return 1;
        
    }
    string line;
    while (getline(fin, line))
        rawData.push_back(line);
    fin.close();

    const int RUNS = 15; // Number of runs
    const int OPS = 4; // Number of operations
    const int STRUCTS = 3; // Number of structures
    long long results[RUNS][OPS][STRUCTS] = {0}; // 3D array to store results of runs

    for (int r = 0; r < RUNS; ++r) {  // Fresh containers every run
    vector<string> vec;
    list<string> lst;
    set<string> st;

  // Measure times and store in results
        results[r][0][0] = raceRead(vec, rawData);
        results[r][0][1] = raceRead(lst, rawData);
        results[r][0][2] = raceRead(st, rawData);

        results[r][1][0] = raceSort(vec);
        results[r][1][1] = raceSort(lst);
        results[r][1][2] = raceSort(st);

        results[r][2][0] = raceInsert(vec, "TESTCODE");
        results[r][2][1] = raceInsert(lst, "TESTCODE");
        results[r][2][2] = raceInsert(st, "TESTCODE");

        results[r][3][0] = raceDelete(vec);
        results[r][3][1] = raceDelete(lst);
        results[r][3][2] = raceDelete(st);
    }
// Compute averages
    long long averages[OPS][STRUCTS] = {0};
    for (int op = 0; op < OPS; ++op) {
        for (int st = 0; st < STRUCTS; ++st) {
            long long sum = 0;
            for (int r = 0; r < RUNS; ++r) {
                sum += results[r][op][st];
            }
            averages[op][st] = sum / RUNS;
        }
    }
cout << "\nNumber of simulations: " << RUNS << "\n";
    cout << left << setw(10) << "Operation"
         << setw(10) << "Vector"
         << setw(10) << "List"
         << setw(10) << "Set" << endl;

    string opsNames[OPS] = {"Read", "Sort", "Insert", "Delete"};

    for (int op = 0; op < OPS; ++op) {
        cout << setw(10) << opsNames[op]
             << setw(10) << averages[op][0]
             << setw(10) << averages[op][1]
             << setw(10) << averages[op][2] << endl;
    }

    return 0;
}