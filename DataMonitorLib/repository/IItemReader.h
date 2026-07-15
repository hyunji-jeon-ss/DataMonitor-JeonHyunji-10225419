#pragma once

#include "model/Item.h"

#include <optional>
#include <string>
#include <vector>

class IItemReader
{
    public:
        virtual ~IItemReader() = default;

        virtual std::vector<Item> findAll() = 0;
        virtual std::optional<Item> findById(int id) = 0;
        virtual std::vector<Item> searchByName(const std::string& keyword) = 0;
};
