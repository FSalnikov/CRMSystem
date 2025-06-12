#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "Task.h"

/// @brief Категория клиента
enum class ClientCategory {
    VIP,
    Regular,
    Other
};

/// @brief Представляет клиента CRM системы
class Client {
public:
    /// @brief Конструктор клиента
    Client(std::string name, std::string phone, std::string email, std::string notes, ClientCategory category);

    /// @brief Добавить задачу клиенту
    void addTask(const Task& task);

    /// @brief Получить все задачи
    const std::vector<Task>& getTasks() const;

    /// @brief Получить имя клиента
    std::string getName() const;

    /// @brief Получить телефон
    std::string getPhone() const;

    /// @brief Получить email
    std::string getEmail() const;

    /// @brief Получить заметки
    std::string getNotes() const;

    /// @brief Получить категорию
    ClientCategory getCategory() const;

    /// @brief Сериализация в JSON
    nlohmann::json toJson() const;

    /// @brief Десериализация из JSON
    static Client fromJson(const nlohmann::json& j);

private:
    std::string name;
    std::string phone;
    std::string email;
    std::string notes;
    ClientCategory category;
    std::vector<Task> tasks;
};
#pragma once
#include <string>
#include <vector>
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

    const std::string& getName() const;
    const std::string& getPhone() const;
    const std::string& getEmail() const;
    const std::string& getNotes() const;
    ClientCategory getCategory() const;

    const std::vector<Task>& getTasks() const;
    void addTask(const Task& task);
    void markTaskDone(size_t index);

    // JSON сериализация
    std::string toJson() const;
};
