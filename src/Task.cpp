#include "Task.h"


Task::Task(const std::string& text, const std::string& dueDate)
    : text(text), dueDate(dueDate), status(TaskStatus::Pending) {}

std::string Task::getText() const {
    return text;
}

std::string Task::getDueDate() const {
    return dueDate;
}

TaskStatus Task::getStatus() const {
    return status;
}

void Task::markCompleted() {
    status = TaskStatus::Completed;
}

std::string Task::getStatusString() const {
    return status == TaskStatus::Completed ? "Completed" : "Pending";
}

nlohmann::json Task::toJson() const {
    return {
        {"text", text},
        {"dueDate", dueDate},
        {"status", status == TaskStatus::Completed ? "completed" : "pending"}
    };
}

Task Task::fromJson(const nlohmann::json& j) {
    Task task(j.at("text"), j.at("dueDate"));
    std::string stat = j.at("status");
    if (stat == "completed") {
        task.markCompleted();
    }
    return task;
}
