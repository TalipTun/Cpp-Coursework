#include "StudentRecord.h"
#include <iostream>
#include <iomanip>

// adds a new grade to correct term vector
void StudentRecord::add_grade(int term, const std::string& moduleCode, int mark) {
    GradeEntry grade(moduleCode, mark);
    terms[term].push_back(grade);
}

void StudentRecord::debug_print() const {
    std::cout << "Student ID: " << studentId << "\n";

    for (const auto& pair : terms) {
        int term = pair.first;
        const auto& grades = pair.second;

        std::cout << "Term " << term << ": ";

        for (const auto& g : grades) {
            std::cout << "(" << g.moduleCode << ", " << g.mark << ") ";
        }
        std::cout << "\n";
    }
}

// self explanatory
bool StudentRecord::has_term(int term) const {
    return terms.find(term) != terms.end();
}

//gets all grades for a term
const std::vector<GradeEntry>& StudentRecord::get_term(int term) const {
    return terms.at(term);
}

//compute the average of grades and modules parameters
double StudentRecord::credit_weighted_average(
    const std::vector<GradeEntry>& grades,
    const std::map<std::string, ModuleInfo>& modules
) const {
    double weightedSum = 0;
    int totalCredits = 0;

    for (const auto& g : grades) {
        auto it = modules.find(g.moduleCode);
        // module must exist
        if (it == modules.end()) continue;

        int credit = it->second.get_credit();
        weightedSum += g.mark * credit;
        totalCredits += credit;
    }

    if (totalCredits == 0) return 0.0;
    return weightedSum / totalCredits;
}

// compute single term average
double StudentRecord::term_average(
    int term,
    const std::map<std::string, ModuleInfo>& modules
) const {
    if (!has_term(term)) return 0.0;
    return credit_weighted_average(terms.at(term), modules);
}

// compute the average of all terms
double StudentRecord::overall_average(
    const std::map<std::string, ModuleInfo>& modules
) const {
    double weightedSum = 0;
    int totalCredits = 0;

    for (const auto& t : terms) {
        for (const auto& g : t.second) {
            auto it = modules.find(g.moduleCode);
            if (it == modules.end()) continue;

            int credit = it->second.get_credit();
            weightedSum += g.mark * credit;
            totalCredits += credit;
        }
    }

    if (totalCredits == 0) return 0.0;
    return weightedSum / totalCredits;
}

//prints the entire transcript (single or mutliple terms)
void StudentRecord::print_transcript(
    const std::map<std::string, ModuleInfo>& modules,
    int requestedTerm
) const {
    std::cout << "Student ID: " << studentId << "\n";

    if (requestedTerm != -1) {
        if (!has_term(requestedTerm)) return;

        std::cout << "  Term " << requestedTerm << ":\n";

        for (const auto& g : terms.at(requestedTerm)) {
            const ModuleInfo& info = modules.at(g.moduleCode);
            std::cout << "    " << g.moduleCode << " "
                      << info.get_name() << " (" << info.get_credit()
                      << " credits): " << g.mark << "\n";
        }

        double avg = term_average(requestedTerm, modules);
        std::cout << "  Term Average: " << std::fixed << std::setprecision(2)
                  << avg << "\n";
        return;
    }

    for (const auto& t : terms) {
        int termCode = t.first;
        std::cout << "  Term " << termCode << ":\n";

        for (const auto& g : t.second) {
            const ModuleInfo& info = modules.at(g.moduleCode);
            std::cout << "    " << g.moduleCode << " "
                      << info.get_name() << " (" << info.get_credit()
                      << " credits): " << g.mark << "\n";
        }

        double avg = term_average(termCode, modules);
        std::cout << "  Term Average: " << std::fixed << std::setprecision(2)
                  << avg << "\n";
    }

    double overall = overall_average(modules);
    std::cout << "  Overall Average: " << std::fixed << std::setprecision(2)
              << overall << "\n\n";
}