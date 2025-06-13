#include "Client.h"

Client::Client(const std::string& name, const std::string& phone, 
               const std::string& email, const std::string& notes,
               ClientCategory category)
    : name(name), phone(phone), email(email), notes(notes), category(category) {}

void Client::addTask(const Task& task) {
    tasks.push_back(task);
}

void Client::markTaskDone(size_t index) {
    if (index < tasks.size()) {
        tasks[index].markCompleted();
    }
}

const std::string& Client::getName() const {
    return name;
}

const std::string& Client::getPhone() const {
    return phone;
}

const std::string& Client::getEmail() const {
    return email;
}

const std::string& Client::getNotes() const {
    return notes;
}

ClientCategory Client::getCategory() const {
    return category;
}

const std::vector<Task>& Client::getTasks() const {
    return tasks;
}

nlohmann::json Client::toJson() const {
    nlohmann::json j;
    j["name"] = name;
    j["phone"] = phone;
    j["email"] = email;
    j["notes"] = notes;

    // Сериализация категории
    std::string catStr;
    switch (category) {
        case ClientCategory::VIP: catStr = "VIP"; break;
        case ClientCategory::Frequent: catStr = "Frequent"; break;
        default: catStr = "Regular"; break;
    }
    j["category"] = catStr;

    // Сериализация задач
    j["tasks"] = nlohmann::json::array();
    for (const auto& task : tasks) {
        j["tasks"].push_back(task.toJson());
    }

    return j;
}

Client Client::fromJson(const nlohmann::json& j) {
    std::string catStr = j.at("category");
    ClientCategory cat;
    if (catStr == "VIP") cat = ClientCategory::VIP;
    else if (catStr == "Frequent") cat = ClientCategory::Frequent;
    else cat = ClientCategory::Regular;

    Client client(j.at("name"), j.at("phone"), j.at("email"), j.at("notes"), cat);

    // Десериализация задач
    for (const auto& taskJson : j.at("tasks")) {
        client.addTask(Task::fromJson(taskJson));
    }

    return client;
}