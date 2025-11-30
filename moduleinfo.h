#ifndef MODULEINFO_H
#define MODULEINFO_H

#include <string>

class ModuleInfo {
    std::string name;
    int credit;

    public:
        ModuleInfo() : name("") , credit(0) {}
        ModuleInfo(const std::string& n, int c) : name(n), credit(c) {}

        // public getter so that other files can read module informations.
        const std::string& get_name() const { return name; };
        int get_credit() const { return credit; };
};

#endif
