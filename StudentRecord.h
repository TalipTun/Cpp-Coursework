#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <map>
#include <vector>
#include "moduleinfo.h"

class GradeEntry {
public: 
    std::string moduleCode;
    int mark;

    GradeEntry(const std::string& id, int m) 
        : moduleCode(id), mark(m) {};
};

//Holds all transcript data for one student
class StudentRecord {
    private: 
        std::string studentId;
        std::map<int, std::vector<GradeEntry>> terms;

        double credit_weighted_average(
            const std::vector<GradeEntry>& grades,
            const std::map<std::string, ModuleInfo>& modules
        ) const;

    public:
        void debug_print() const;
        StudentRecord() : studentId("") {}   
        StudentRecord(const std::string& id) 
            : studentId(id) {};

        void add_grade(int term, const std::string& moduleCode, int mark);
        const std::string& get_id() const { return studentId; };
        bool has_term(int term) const;
        const std::vector<GradeEntry>& get_term(int term) const;
        //computes average for one specific term
        double term_average(int term, const std::map<std::string, ModuleInfo>& modules) const;
        //computes average for all terms
        double overall_average(const std::map<std::string, ModuleInfo>& modules) const;
        //prints transcript (full or single term)
        void print_transcript(const std::map<std::string, ModuleInfo>& modules, int requestedTerm = -1) const;
};

#endif