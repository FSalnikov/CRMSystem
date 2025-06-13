#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "Task.h"

/**
 * @brief Категория клиента
 */
enum class ClientCategory {
    Regular,    ///< Обычный клиент
    Frequent,   ///< Постоянный клиент
    VIP         ///< VIP клиент
};

/**
 * @brief Класс, описывающий клиента
 */
class Client {
private:
    std::string name;           ///< Имя клиента
    std::string phone;          ///< Телефон
    std::string email;          ///< Электронная почта
    std::string notes;          ///< Заметки
    ClientCategory category;    ///< Категория клиента
    std::vector<Task> tasks;    ///< Список задач

public:
    /**
     * @brief Конструктор клиента
     * @param name Имя
     * @param phone Телефон
     * @param email Email
     * @param notes Заметки
     * @param category Категория клиента
     */
    Client(const std::string& name,
           const std::string& phone,
           const std::string& email,
           const std::string& notes,
           ClientCategory category);

    // Геттеры
    const std::string& getName() const;
    const std::string& getPhone() const;
    const std::string& getEmail() const;
    const std::string& getNotes() const;
    ClientCategory getCategory() const;
    const std::vector<Task>& getTasks() const;

    // Методы для работы с задачами
    void addTask(const Task& task);
    void markTaskDone(size_t index);

    // JSON сериализация/десериализация
    nlohmann::json toJson() const;
    static Client fromJson(const nlohmann::json& j);
};