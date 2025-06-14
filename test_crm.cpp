#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Client.h"
#include "CRMSystem.h"

TEST_CASE("Client Creation") {
    Client client("Иван Петров", "1234567890", "ivan@example.com", "VIP", ClientCategory::VIP);
    
    CHECK(client.getName() == "Иван Петров");
    CHECK(client.getPhone() == "1234567890");
    CHECK(client.getEmail() == "ivan@example.com");
    CHECK(client.getNotes() == "VIP");
    CHECK(client.getCategory() == ClientCategory::VIP);
}

TEST_CASE("Task Management") {
    Client client("Анна Смирнова", "9876543210", "anna@example.com", "", ClientCategory::Frequent);
    
    Task task("Позвонить", TaskStatus::Pending, "2025-06-15");
    client.addTask(task);

    const auto& tasks = client.getTasks();
    REQUIRE(tasks.size() == 1);
    CHECK(tasks[0].getText() == "Позвонить");
    CHECK(tasks[0].getStatus() == TaskStatus::Pending);
}

TEST_CASE("CRM Operations") {
    CRMSystem crm;
    
    SUBCASE("Add and Find Client") {
        Client client("Сергей Иванов", "1112223333", "sergey@example.com", "", ClientCategory::Regular);
        crm.addClient(client);
        
        auto found = crm.findClient("sergey@example.com");
        REQUIRE(found.has_value());
        CHECK((*found)->getName() == "Сергей Иванов");
    }
    
    SUBCASE("Client Statistics") {
        crm.addClient(Client("A", "1", "a@a.a", "", ClientCategory::Regular));
        crm.addClient(Client("B", "2", "b@b.b", "", ClientCategory::Frequent));
        
        auto stats = crm.getClientCategoryStats();
        CHECK(stats.at(ClientCategory::Regular) == 1);
        CHECK(stats.at(ClientCategory::Frequent) == 1);
    }
}
