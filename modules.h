#ifndef MODULES_H
#define MODULES_H

#include <map>
#include <string>
#include "moduleinfo.h"

// read the modules.txt file and builds a map in this format: 
// (moduleCode:"CSC1024", ModuleInfo: moduleInfo("Java", 15))
std::map<std::string, ModuleInfo> read_modules(const std::string& filename);

#endif
