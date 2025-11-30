#include "modules.h"
#include <fstream>
#include <iostream>
using namespace std;

map<string, ModuleInfo> read_modules(const string& filename) {
    map<string, ModuleInfo> modules;
    ifstream f(filename);

    if (!f) {
        cerr << "Error opening file: " << filename << "\n";
        return modules;
    }

    string moduleCode;
    int credit;
    string moduleName;

    while (f >> moduleCode >> credit >> moduleName) {
        ModuleInfo moduleData(moduleName, credit);
        modules.insert({moduleCode, moduleData});
    }

    f.close();
    return modules;
}