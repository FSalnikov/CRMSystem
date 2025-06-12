#pragma once

#include <string>
#include <chrono>
#include <nlohmann/json.hpp>

/// @brief Статус задачи
enum class TaskStatus {
    Pending,
    Completed
};

/// @brief Представляет задачу, связанную с клиентом
class Task {
public:
    /// @brief Конструктор задачи
    /// @param text Текст задачи
    /// @param dueDate Срок выполнения
    Task(const std::string& text, const std::string& dueDate);

    /// @brief Получить текст задачи
    std::string getText() const;

    /// @brief Получить срок задачи
    std::string getDueDate() const;

    /// @brief Получить статус задачи
    TaskStatus getStatus() const;

    /// @brief Отметить задачу как выполненную
    void markCompleted();

    /// @brief Получить строковое представление статуса
    std::string getStatusString() const;

    /// @brief Сериализация задачи в JSON
    nlohmann::json toJson() const;

    /// @brief Десериализация задачи из JSON
    static Task fromJson(const nlohmann::json& j);

private:
    std::string text;
    std::string dueDate;
    TaskStatus status;
};
#pragma once
#include <string>

/**
 * @brief Статус задачи
 */
enum class TaskStatus {
    Pending,   ///< Задача ожидает выполнения
    Completed  ///< Задача выполнена
};

/**
 * @brief Класс, представляющий задачу для клиента
 */
class Task {
private:
    std::string text;       ///< Текст задачи
    TaskStatus status;      ///< Статус выполнения задачи
    std::string dueDate;    ///< Срок выполнения (в формате YYYY-MM-DD)

public:
    /**
     * @brief Конструктор задачи
     * @param text Текст задачи
     * @param status Статус задачи
     * @param dueDate Дата выполнения
     */
    Task(const std::string& text, TaskStatus status, const std::string& dueDate);

    const std::string& getText() const;
    TaskStatus getStatus() const;
    const std::string& getDueDate() const;
    void markDone();

    // Для сериализации
    std::string toString() const;
};
