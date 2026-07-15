#include "repository/IItemReader.h"
#include "repository/JsonItemReader.h"

#define NOMINMAX
#include <windows.h>

#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace
{
    void printItem(const Item& item)
    {
        std::cout << "  " << item.id << " | " << item.name << std::endl;
    }

    void printItems(const std::vector<Item>& items)
    {
        if (items.empty())
        {
            std::cout << "조회된 항목이 없습니다." << std::endl;
            return;
        }

        for (const Item& item : items)
        {
            printItem(item);
        }
    }

    void printMenu()
    {
        std::cout << "==============================" << std::endl;
        std::cout << "[1] 전체 조회  [2] 이름 검색  [3] id 조회  [0] 종료" << std::endl;
        std::cout << "선택 > ";
    }

    void handleSearchByName(IItemReader& reader)
    {
        std::cout << "검색어 > ";
        std::string keyword;
        std::getline(std::cin, keyword);

        printItems(reader.searchByName(keyword));
    }

    void handleFindById(IItemReader& reader)
    {
        std::cout << "id > ";
        std::string id_text;
        std::getline(std::cin, id_text);

        try
        {
            const int id = std::stoi(id_text);
            const std::optional<Item> found = reader.findById(id);
            if (found.has_value())
            {
                printItem(*found);
            }
            else
            {
                std::cout << "해당 id의 항목이 없습니다." << std::endl;
            }
        }
        catch (const std::exception&)
        {
            std::cout << "숫자를 입력해주세요." << std::endl;
        }
    }
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    JsonItemReader reader("items.json");

    bool running = true;
    while (running)
    {
        printMenu();

        std::string command;
        std::getline(std::cin, command);

        if (command == "0") running = false;
        else if (command == "1") printItems(reader.findAll());
        else if (command == "2") handleSearchByName(reader);
        else if (command == "3") handleFindById(reader);
        else std::cout << "알 수 없는 명령입니다." << std::endl;
    }

    return 0;
}
