#ifndef RECORDS_IO_H
#define RECORDS_IO_H

#include <map>
#include <string>
#include "StudentRecord.h"

// reads grades.txt and creates a map in this format:
// (StudentID: "20231234", GradeEntry: (moduleCode: "CSC1024", mark: "78")))
std::map<std::string, StudentRecord> read_records(const std::string& filename);

#endif