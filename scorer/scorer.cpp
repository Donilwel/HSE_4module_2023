#include "scorer.h"

struct TaskStatus {
    time_t last_success_time = 0;
    bool merge_request_open = false;
};

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    Events sorted = events;
    std::sort(sorted.begin(), sorted.end(), [](const Event& a, const Event& b) { return a.time < b.time; });

    std::map<StudentName, std::map<TaskName, TaskStatus>> student_tasks;

    for (const auto& el : sorted) {
        if (el.time > score_time) {
            continue;
        }
        auto& stata = student_tasks[el.student_name][el.task_name];
        if (el.event_type == EventType::CheckFailed) {
            stata.last_success_time = 0;
        } else if (el.event_type == EventType::CheckSuccess) {
            stata.last_success_time = el.time;
        } else if (el.event_type == EventType::MergeRequestOpen) {
            stata.merge_request_open = true;
        } else if (el.event_type == EventType::MergeRequestClosed) {
            stata.merge_request_open = false;
        }
    }
    ScoreTable score_cards;
    for (const auto& [student, tasks] : student_tasks) {
        for (const auto& [task, status] : tasks) {
            if (status.last_success_time > 0) {
                if (status.last_success_time <= score_time) {
                    if (!status.merge_request_open) {
                        score_cards[student].insert(task);
                    }
                }
            }
        }
    }
    return score_cards;
}