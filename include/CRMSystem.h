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
     * @param client Клиент для добавления
     */
    void addClient(const Client& client);

    /**
     * @brief Удалить клиента по имени
     * @param name Имя клиента для удаления
     * @return true если клиент был найден и удалён, false если не найден
     */
    bool removeClient(const std::string& name);

    /**
     * @brief Найти клиента по имени, телефону или email
     * @param query Поисковый запрос
     * @return optional с указателем на клиента, если найден
     */
    std::optional<Client*> findClient(const std::string& query);

    /**
     * @brief Получить всех клиентов, отсортированных по имени
     * @return Вектор указателей на клиентов
     */
    std::vector<Client*> getAllClientsSorted();

    /**
     * @brief Сохранить клиентов в файл JSON
     * @param filename Имя файла для сохранения
     */
    void saveToFile(const std::string& filename) const;

    /**
     * @brief Загрузить клиентов из JSON
     * @param filename Имя файла для загрузки
     */
    void loadFromFile(const std::string& filename);

    /**
     * @brief Получить количество клиентов в каждой категории
     * @return Карта с количеством клиентов по категориям
     */
    std::map<ClientCategory, int> getClientCategoryStats() const;

    /**
     * @brief Получить общее количество клиентов
     * @return Количество клиентов в системе
     */
    size_t getTotalClients() const;

    /**
     * @brief Получить все актуальные задачи (не выполненные)
     * @return Вектор невыполненных задач
     */
    std::vector<Task> getAllPendingTasks() const;
};