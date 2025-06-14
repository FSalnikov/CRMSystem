#include <iostream>
#include <fstream>
#include "CRMSystem.h"

void showMainMenu() {
    std::cout << "\n====== CRM Меню ======\n";
    std::cout << "1. Добавить клиента\n";
    std::cout << "2. Найти клиента\n";
    std::cout << "3. Удалить клиента\n";
    std::cout << "4. Добавить задачу клиенту\n";
    std::cout << "5. Просмотреть всех клиентов\n";
    std::cout << "6. Посмотреть все актуальные задачи\n";
    std::cout << "7. Статистика\n";
    std::cout << "8. Сохранить и выйти\n";
    std::cout << "Выберите опцию: ";
}

ClientCategory selectCategory() {
    int choice;
    while (true) {
        std::cout << "Категория клиента (0 - Обычный, 1 - Постоянный, 2 - VIP): ";
        std::cin >> choice;
        if (choice >= 0 && choice <= 2) {
            break;
        }
        std::cout << "❌ Неверный ввод. Попробуйте снова.\n";
    }
    return static_cast<ClientCategory>(choice);
}

void initializeDataFile() {
    std::ifstream testFile("clients.json");
    if (!testFile.good()) {
        std::ofstream newFile("clients.json");
        newFile << "[]";
        newFile.close();
    }
}

int main() {
    initializeDataFile();
    
    CRMSystem crm;
    try {
        crm.loadFromFile("clients.json");
    } catch (const std::exception& e) {
        std::cerr << "⚠️ Ошибка загрузки данных: " << e.what() << "\n";
        std::cerr << "Будет создана новая пустая база данных.\n";
    }

    while (true) {
        showMainMenu();
        int option;
        std::cin >> option;
        std::cin.ignore();

        try {
            if (option == 1) {
                std::string name, phone, email, notes;
                std::cout << "Имя: ";
                std::getline(std::cin, name);
                std::cout << "Телефон: ";
                std::getline(std::cin, phone);
                std::cout << "Email: ";
                std::getline(std::cin, email);
                std::cout << "Заметки: ";
                std::getline(std::cin, notes);
                
                crm.addClient(Client(name, phone, email, notes, selectCategory()));
                std::cout << "✅ Клиент добавлен.\n";

            } else if (option == 2) {
                std::string query;
                std::cout << "Введите имя, email или телефон: ";
                std::getline(std::cin, query);

                if (auto client = crm.findClient(query)) {
                    std::cout << "Найден: " << (*client)->getName() << "\n";
                } else {
                    std::cout << "❌ Клиент не найден.\n";
                }

            } else if (option == 3) {
                std::string name;
                std::cout << "Введите имя клиента для удаления: ";
                std::getline(std::cin, name);
                std::cout << (crm.removeClient(name) ? "✅ Удалено.\n" : "❌ Клиент не найден.\n");

            } else if (option == 4) {
                std::string name;
                std::cout << "Введите имя клиента: ";
                std::getline(std::cin, name);

                if (auto client = crm.findClient(name)) {
                    std::string text, dueDate;
                    std::cout << "Текст задачи: ";
                    std::getline(std::cin, text);
                    std::cout << "Срок (YYYY-MM-DD): ";
                    std::getline(std::cin, dueDate);

                    (*client)->addTask(Task(text, TaskStatus::Pending, dueDate));
                    std::cout << "✅ Задача добавлена.\n";
                } else {
                    std::cout << "❌ Клиент не найден.\n";
                }

            } else if (option == 5) {
                for (const auto* client : crm.getAllClientsSorted()) {
                    std::cout << "- " << client->getName() << " (" << client->getEmail() << ")\n";
                }

            } else if (option == 6) {
                for (const auto& task : crm.getAllPendingTasks()) {
                    std::cout << "[ ] " << task.getText() << " (до " << task.getDueDate() << ")\n";
                }

            } else if (option == 7) {
                auto stats = crm.getClientCategoryStats();
                std::cout << "Всего клиентов: " << crm.getTotalClients() << "\n";
                std::cout << "Обычных: " << stats[ClientCategory::Regular] << "\n";
                std::cout << "Постоянных: " << stats[ClientCategory::Frequent] << "\n";
                std::cout << "VIP: " << stats[ClientCategory::VIP] << "\n";

            } else if (option == 8) {
                crm.saveToFile("clients.json");
                std::cout << "💾 Данные сохранены. Выход.\n";
                break;

            } else {
                std::cout << "❌ Неизвестная опция.\n";
            }
        } catch (const std::exception& e) {
            std::cerr << "⚠️ Ошибка: " << e.what() << "\n";
        }
    }

    return 0;
}