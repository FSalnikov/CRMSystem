#include "Client.h"

Client::Client(std::string name, std::string phone, std::string email, std::string notes, ClientCategory category)
    : name(std::move(name)), phone(std::move(phone)), email(std::move(email)), notes(std::move(notes)), category(category) {}

void Client::addTask(const Task& task) {
    tasks.push_back(task);
}

const std::vector<Task>& Client::getTasks() const {
    return tasks;
}

std::string Client::getName() const {
    return name;
}

std::string Client::getPhone() const {
    return phone;
}

std::string Client::getEmail() const {
    return email;
}

std::string Client::getNotes() const {
    return notes;
}

ClientCategory Client::getCategory() const {
    return category;
}

nlohmann::json Client::toJson() const {
    nlohmann::json j;
    j["name"] = name;
    j["phone"] = phone;
    j["email"] = email;
    j["notes"] = notes;

    std::string cat;
    switch (category) {
        case ClientCategory::VIP: cat = "VIP"; break;
        case ClientCategory::Regular: cat = "Regular"; break;
        default: cat = "Other"; break;
    }
    j["category"] = cat;

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
    else if (catStr == "Regular") cat = ClientCategory::Regular;
    else cat = ClientCategory::Other;

    Client client(j.at("name"), j.at("phone"), j.at("email"), j.at("notes"), cat);

    for (const auto& taskJson : j.at("tasks")) {
        client.addTask(Task::fromJson(taskJson));
    }

    return client;
}
