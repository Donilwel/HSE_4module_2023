#include "sort_students.h"

bool CompareStudentsByName(const Student& a, const Student& b) {
    if (a.last_name != b.last_name) {
        return a.last_name < b.last_name;
    } else if (a.name != b.name) {
        return a.name < b.name;
    } else {
        return a.birth_date.year < b.birth_date.year ||
               (a.birth_date.year == b.birth_date.year && a.birth_date.month < b.birth_date.month) ||
               (a.birth_date.year == b.birth_date.year && a.birth_date.month == b.birth_date.month &&
                a.birth_date.day < b.birth_date.day);
    }
}

bool CompareStudentsByDate(const Student& a, const Student& b) {
    return a.birth_date.year < b.birth_date.year ||
           (a.birth_date.year == b.birth_date.year && a.birth_date.month < b.birth_date.month) ||
           (a.birth_date.year == b.birth_date.year && a.birth_date.month == b.birth_date.month &&
            a.birth_date.day < b.birth_date.day) ||
           (a.birth_date.year == b.birth_date.year && a.birth_date.month == b.birth_date.month &&
            a.birth_date.day == b.birth_date.day && a.last_name < b.last_name) ||
           (a.birth_date.year == b.birth_date.year && a.birth_date.month == b.birth_date.month &&
            a.birth_date.day == b.birth_date.day && a.last_name == b.last_name && a.name < b.name);
}

void SortStudents(std::vector<Student>& students, SortKind sort_kind) {
    if (sort_kind == SortKind::Name) {
        std::sort(students.begin(), students.end(), CompareStudentsByName);
    } else if (sort_kind == SortKind::Date) {
        std::sort(students.begin(), students.end(), CompareStudentsByDate);
    }
}
