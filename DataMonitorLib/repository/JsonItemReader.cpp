#include "repository/JsonItemReader.h"

#include <nlohmann/json.hpp>

#include <algorithm>
#include <cctype>
#include <fstream>

using nlohmann::json;

namespace
{
    Item fromJson(const json& element)
    {
        return Item{ element.at("id").get<int>(), element.at("name").get<std::string>() };
    }

    std::string toLower(const std::string& value)
    {
        std::string lowered = value;
        std::transform(lowered.begin(), lowered.end(), lowered.begin(),
            [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        return lowered;
    }

    bool containsIgnoreCase(const std::string& text, const std::string& keyword)
    {
        return toLower(text).find(toLower(keyword)) != std::string::npos;
    }
}

JsonItemReader::JsonItemReader(const std::string& file_path)
    : file_path(file_path)
{
}

std::vector<Item> JsonItemReader::findAll()
{
    std::ifstream input(file_path);
    if (!input.is_open()) return {};

    input.seekg(0, std::ios::end);
    if (input.tellg() == 0) return {};
    input.seekg(0, std::ios::beg);

    json root;
    input >> root;

    std::vector<Item> items;
    items.reserve(root.size());
    for (const json& element : root)
    {
        items.push_back(fromJson(element));
    }
    return items;
}

std::optional<Item> JsonItemReader::findById(int id)
{
    for (const Item& item : findAll())
    {
        if (item.id == id) return item;
    }
    return std::nullopt;
}

std::vector<Item> JsonItemReader::searchByName(const std::string& keyword)
{
    std::vector<Item> matched;
    for (const Item& item : findAll())
    {
        if (containsIgnoreCase(item.name, keyword)) matched.push_back(item);
    }
    return matched;
}
