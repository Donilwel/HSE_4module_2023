#include "admission.h"

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::vector<const Applicant*> s_applicant(applicants.size());
    auto i = 0;
    while (i != s_applicant.size()) {
        s_applicant[i] = &applicants[i];
        ++i;
    }
    std::sort(s_applicant.begin(), s_applicant.end(), [](const Applicant* one, const Applicant* two) {
        return std::tie((*two).points, (*one).student.birth_date.year, (*one).student.birth_date.month,
                        (*one).student.birth_date.day, (*one).student.name) <
               std::tie((*one).points, (*two).student.birth_date.year, (*two).student.birth_date.month,
                        (*two).student.birth_date.day, (*two).student.name);
    });
    std::unordered_map<std::string, size_t> places;
    for (int u = 0; u < universities.size(); ++u) {
        places[universities[u].name] = universities[u].max_students;
    }
    AdmissionTable answer;
    for (const auto& el : s_applicant) {
        for (const auto& univ : (*el).wish_list) {
            auto it = places.find(univ);
            if (it != places.end() && (*it).second > 0) {
                --(*it).second;
                answer[univ].push_back(&el->student);
                break;
            }
        }
    }
    return answer;
}