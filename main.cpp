#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "modules.h"
#include "records.h"
#include "StudentRecord.h"

using namespace std;

int main() {
    // Load modules (names and credits)
    std::map<std::string, ModuleInfo> modules = read_modules("modules.txt");

    // Load student grade records
    std::map<std::string, StudentRecord> records = read_records("grades.txt");

    // Open requests file
    std::ifstream req("requests.txt");
    if (!req) {
        std::cerr << "Error opening requests.txt\n";
        return 1;
    }

    std::string line;

    //processing each request line by line
    while (std::getline(req, line)) {
        // ignore blank
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string studentID;
        int term;

        //check if studentID is on the line, if not continue to the next line
        ss >> studentID;
        if (studentID.empty()) continue;

        //find students data, if not continue
        auto it = records.find(studentID);
        if (it == records.end()) {
            continue;
        }

        if (ss >> term) {
            //print only this term
            it->second.print_transcript(modules, term);
        } else {
            //print full transcript
            it->second.print_transcript(modules);
        }
    }

    return 0;
}
