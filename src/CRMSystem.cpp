#include "CRMSystem.h"
#include <algorithm>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void CRMSystem::addClient(const Client& client) {
    clients.push_back(client);
}

bool CRMSystem::removeClient(const std::string& name) {
    auto it = std::remove_if(clients.begin(), clients.end(),
        [&name](const Client& c) { return c.getName() == name; });
    
    bool removed = it != clients.end();
    clients.erase(it, clients.end());
    return removed;
}

std::optional<Client*> CRMSystem::findClient(const std::string& query) {
    for (auto& client : clients) {
        if (client.getName() == query || 
            client.getEmail() == query || 
            client.getPhone() == query) {
            return &client;
        }
    }
    return std::nullopt;
}

std::vector<Client*> CRMSystem::getAllClientsSorted() {
    std::vector<Client*> sorted;
    sorted.reserve(clients.size());
    
    for (auto& client : clients) {
        sorted.push_back(&client);
    }

    std::sort(sorted.begin(), sorted.end(),
        [](Client* a, Client* b) { return a->getName() < b->getName(); });

    return sorted;
}

void CRMSystem::saveToFile(const std::string& filename) const {
    json j;
    for (const auto& client : clients) {
        j.push_back(client.toJson());
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для записи: " + filename);
    }
    file << j.dump(4);
}

void CRMSystem::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }

    try {
        json j;
        file >> j;
        
        std::vector<Client> newClients;
        for (const auto& item : j) {
            newClients.push_back(Client::fromJson(item));
        }
        clients = std::move(newClients);
    } catch (const json::exception& e) {
        throw std::runtime_error("Ошибка парсинга JSON: " + std::string(e.what()));
    }
}

std::map<ClientCategory, int> CRMSystem::getClientCategoryStats() const {
    std::map<ClientCategory, int> stats = {
        {ClientCategory::Regular, 0},
        {ClientCategory::Frequent, 0},
        {ClientCategory::VIP, 0}
    };
    
    for (const auto& client : clients) {
        stats[client.getCategory()]++;
    }
    return stats;
}

size_t CRMSystem::getTotalClients() const {
    return clients.size();
}

std::vector<Task> CRMSystem::getAllPendingTasks() const {
    std::vector<Task> pendingTasks;
    for (const auto& client : clients) {
        for (const auto& task : client.getTasks()) {
            if (task.getStatus() == TaskStatus::Pending) {
                pendingTasks.push_back(task);
            }
        }
    }
    
    // Сортировка по дате выполнения
    std::sort(pendingTasks.begin(), pendingTasks.end(),
        [](const Task& a, const Task& b) { return a.getDueDate() < b.getDueDate(); });
    
    return pendingTasks;
}