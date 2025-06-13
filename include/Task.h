#pragma once
#include <string>
#include <nlohmann/json.hpp>

/**
 * @brief Статус задачи
 */
enum class TaskStatus {
    Pending,    ///< Задача ожидает выполнения
    Completed   ///< Задача выполнена
};

/**
 * @brief Класс, представляющий задачу для клиента
 */
class Task {
private:
    std::string text;     ///< Текст задачи
    std::string dueDate;  ///< Срок выполнения (в формате YYYY-MM-DD)
    TaskStatus status;    ///< Статус выполнения задачи

public:
    /**
     * @brief Конструктор задачи со статусом по умолчанию (Pending)
     * @param text Текст задачи
     * @param dueDate Дата выполнения
     */
    Task(const std::string& text, const std::string& dueDate);
    
    /**
     * @brief Конструктор задачи с указанием статуса
     * @param text Текст задачи
     * @param status Статус задачи
     * @param dueDate Дата выполнения
     */
    Task(const std::string& text, TaskStatus status, const std::string& dueDate);

    /// @brief Получить текст задачи
    const std::string& getText() const;
    
    /// @brief Получить статус задачи
    TaskStatus getStatus() const;
    
    /// @brief Получить срок выполнения
    const std::string& getDueDate() const;
    
    /// @brief Отметить задачу как выполненную
    void markCompleted();
    
    /// @brief Получить строковое представление статуса
    std::string getStatusString() const;
    
    /// @brief Сериализация в JSON
    nlohmann::json toJson() const;
    
    /// @brief Десериализация из JSON
    static Task fromJson(const nlohmann::json& j);
};

