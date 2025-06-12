#include "CRMSystem.h"
#include <fstream>
#include <algorithm>

void CRMSystem::addClient(const Client& client) {
    clients.push_back(client);
}

bool CRMSystem::removeClient(const std::string& name) {
    auto it = std::remove_if(clients.begin(), clients.end(),
        [&name](const Client& c) { return c.getName() == name; });
    if (it != clients.end()) {
        clients.erase(it, clients.end());
        return true;
    }
    return false;
}

std::optional<Client*> CRMSystem::findClient(const std::string& query) {
    for (auto& client : clients) {
        if (client.getName() == query || client.getEmail() == query || client.getPhone() == query) {
            return &client;
        }
    }
    return std::nullopt;
}

std::vector<Client*> CRMSystem::getAllClientsSorted() const {
    std::vector<Client*> sorted;
    for (const auto& client : clients)
        sorted.push_back(const_cast<Client*>(&client));

    std::sort(sorted.begin(), sorted.end(),
        [](Client* a, Client* b) { return a->getName() < b->getName(); });

    return sorted;
}

void CRMSystem::saveToFile(const std::string& filename) const {
    nlohmann::json j;
    for (const auto& client : clients) {
        j.push_back(client.toJson());
    }
    std::ofstream file(filename);
    file << j.dump(4);
}

void CRMSystem::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    nlohmann::json j;
    file >> j;
    clients.clear();
    for (const auto& item : j) {
        clients.push_back(Client::fromJson(item));
    }
}

std::map<ClientCategory, int> CRMSystem::getClientCategoryStats() const {
    std::map<ClientCategory, int> stats;
    for (const auto& client : clients) {
        stats[client.getCategory()]++;
    }
    return stats;
}

size_t CRMSystem::getTotalClients() const {
    return clients.size();
}

std::vector<Task> CRMSystem::getAllPendingTasks() const {
    std::vector<Task> pending;
    for (const auto& client : clients) {
        for (const auto& task : client.getTasks()) {
            if (task.getStatus() == TaskStatus::Pending) {
                pending.push_back(task);
            }
        }
    }
    return pending;
}
