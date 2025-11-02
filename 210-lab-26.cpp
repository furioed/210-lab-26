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



    vector<string> vec;
    list<string> lst;
    set<string> st;

    // Header
    cout << left << setw(10) << "Operation"
         << setw(10) << "Vector"
         << setw(10) << "List"
         << setw(10) << "Set" << endl;


    // Read     
    cout << setw(10) << "Read"
         << setw(10) << raceRead(vec, rawData)
         << setw(10) << raceRead(lst, rawData)
         << setw(10) << raceRead(st, rawData) << endl;
        

    // Sort 
    cout << setw(10) << "Sort"
         << setw(10) << raceSort(vec)
         << setw(10) << raceSort(lst)
         << setw(10) << raceSort(st) << endl;
    
    // Insert 
    cout << setw(10) << "Insert"
         << setw(10) << raceInsert(vec, "TESTCODE")
         << setw(10) << raceInsert(lst, "TESTCODE")
         << setw(10) << raceInsert(st, "TESTCODE") << endl;
        
    // Delete
    cout << setw(10) << "Delete"
         << setw(10) << raceDelete(vec)
         << setw(10) << raceDelete(lst)
         << setw(10) << raceDelete(st) << endl;

    return 0;
}
