#pragma once

#include "Client.h"
#include <vector>
#include <optional>
#include <string>
#include <nlohmann/json.hpp>

/// @brief Основной класс CRM системы
class CRMSystem {
public:
    /// @brief Добавить клиента
    void addClient(const Client& client);

    /// @brief Удалить клиента по имени
    bool removeClient(const std::string& name);

    /// @brief Найти клиента по имени, телефону или email
    std::optional<Client*> findClient(const std::string& query);

    /// @brief Получить всех клиентов, отсортированных по имени
    std::vector<Client*> getAllClientsSorted() const;

    /// @brief Сохранить клиентов в файл JSON
    void saveToFile(const std::string& filename) const;

    /// @brief Загрузить клиентов из JSON
    void loadFromFile(const std::string& filename);

    /// @brief Получить количество клиентов в каждой категории
    std::map<ClientCategory, int> getClientCategoryStats() const;

    /// @brief Получить общее количество клиентов
    size_t getTotalClients() const;

    /// @brief Получить все актуальные задачи (не выполненные)
    std::vector<Task> getAllPendingTasks() const;

private:
    std::vector<Client> clients;
};
#pragma once
#include <vector>
#include <string>
#include <optional>
#include <map>
#include "Client.h"

/**
 * @brief Класс системы CRM для управления клиентами
 */
class CRMSystem {
private:
    std::vector<Client> clients; ///< Список клиентов

public:
    /**
     * @brief Добавить клиента
     * @param client Клиент
     */
    void addClient(const Client& client);

    /**
     * @brief Найти клиента по имени, email или телефону
     * @param query Поисковый запрос
     * @return Указатель на найденного клиента (или nullopt)
     */
    std::optional<Client*> findClient(const std::string& query);

    /**
     * @brief Удалить клиента по имени
     * @param name Имя клиента
     * @return true, если клиент был удалён
     */
    bool removeClient(const std::string& name);

    /**
     * @brief Получить всех клиентов, отсортированных по имени
     * @return Вектор указателей на клиентов
     */
    std::vector<Client*> getAllClientsSorted();

    /**
     * @brief Получить все невыполненные задачи
     * @return Список задач
     */
    std::vector<Task> getAllPendingTasks() const;

    /**
     * @brief Получить статистику по категориям
     * @return Карта <Категория, Количество>
     */
    std::map<ClientCategory, int> getClientCategoryStats() const;

    /**
     * @brief Сохранить данные в файл
     * @param filename Имя файла
     */
    void saveToFile(const std::string& filename) const;

    /**
     * @brief Загрузить данные из файла
     * @param filename Имя файла
     */
    void loadFromFile(const std::string& filename);

    /**
     * @brief Получить общее число клиентов
     */
    size_t getTotalClients() const;
};
