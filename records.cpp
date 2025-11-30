#include "records.h"
#include <fstream>
#include <iostream>

using namespace std;

std::map<std::string, StudentRecord> read_records(const std::string& filename) {
    ifstream f(filename);
    map<string, StudentRecord> studentrecords;
    if (!f) {
        cerr << "Error opening file: " << filename << "\n";
        return studentrecords;
    }

    string studentID;
    int term;
    string moduleCode;
    int mark;

    while (f >> studentID >> term >> moduleCode >> mark) {
        if (studentrecords.find(studentID) == studentrecords.end()) {
            studentrecords[studentID] = StudentRecord(studentID);
        }

        studentrecords[studentID].add_grade(term, moduleCode, mark);
    }

    return studentrecords;
}