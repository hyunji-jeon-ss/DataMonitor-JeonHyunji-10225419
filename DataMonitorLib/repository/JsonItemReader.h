#pragma once

#include "repository/IItemReader.h"

#include <string>

class JsonItemReader : public IItemReader
{
    public:
        explicit JsonItemReader(const std::string& file_path);

        std::vector<Item> findAll() override;
        std::optional<Item> findById(int id) override;
        std::vector<Item> searchByName(const std::string& keyword) override;

    private:
        std::string file_path;
};
