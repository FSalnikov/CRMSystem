cmake_minimum_required(VERSION 3.10)
project(CRM_System)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Прямые абсолютные пути
set(DOCTEST_PATH "C:/Users/fedor/C++/crm_project/include/doctest.h")
set(NLOHMANN_JSON_PATH "C:/Users/fedor/C++/crm_project/include/nlohmann/json.hpp")

# Основное приложение
add_executable(crm_system
    "C:/Users/fedor/C++/crm_project/main.cpp"
    "C:/Users/fedor/C++/crm_project/src/Client.cpp"
    "C:/Users/fedor/C++/crm_project/src/CRMSystem.cpp"
    "C:/Users/fedor/C++/crm_project/src/Task.cpp"
)

# Включаем директории с заголовочными файлами
target_include_directories(crm_system PRIVATE
    "C:/Users/fedor/C++/crm_project/include"
)

# Проверка и загрузка nlohmann/json
if(NOT EXISTS ${NLOHMANN_JSON_PATH})
    message(STATUS "Downloading nlohmann/json.hpp...")
    file(DOWNLOAD
        "https://github.com/nlohmann/json/releases/download/v3.11.2/json.hpp"
        ${NLOHMANN_JSON_PATH}
        SHOW_PROGRESS
    )
endif()

# Настройки для тестов
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    enable_testing()
    
    # Проверка наличия doctest.h
    if(NOT EXISTS ${DOCTEST_PATH})
        message(STATUS "Downloading doctest.h...")
        file(DOWNLOAD
            "https://raw.githubusercontent.com/doctest/doctest/master/doctest/doctest.h"
            ${DOCTEST_PATH}
            SHOW_PROGRESS
        )
    endif()
    
    # Исполняемый файл для тестов
    add_executable(crm_tests
        "C:/Users/fedor/C++/crm_project/tests/test_crm.cpp"
        "C:/Users/fedor/C++/crm_project/src/Client.cpp"
        "C:/Users/fedor/C++/crm_project/src/CRMSystem.cpp"
        "C:/Users/fedor/C++/crm_project/src/Task.cpp"
    )
    
    target_include_directories(crm_tests PRIVATE
        "C:/Users/fedor/C++/crm_project/include"
    )
    
    add_test(NAME CRMTests COMMAND crm_tests)
endif()