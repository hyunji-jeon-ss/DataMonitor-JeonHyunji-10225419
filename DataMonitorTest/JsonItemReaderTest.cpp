#include "repository/JsonItemReader.h"

#include "gmock/gmock.h"

#include <cstdio>
#include <fstream>
#include <string>

using namespace testing;

namespace
{
    void writeJsonFile(const std::string& path, const std::string& content)
    {
        std::ofstream output(path);
        output << content;
    }
}

class JsonItemReaderTest : public Test
{
    protected:
        void SetUp() override
        {
            std::remove(file_path.c_str());
        }

        void TearDown() override
        {
            std::remove(file_path.c_str());
        }

        std::string file_path = "test_monitor.json";
};

TEST_F(JsonItemReaderTest, FindAllReturnsEmptyWhenFileDoesNotExist)
{
    JsonItemReader reader(file_path);

    EXPECT_TRUE(reader.findAll().empty());
}

TEST_F(JsonItemReaderTest, FindAllReturnsAllStoredItems)
{
    writeJsonFile(file_path, R"([{"id":1,"name":"Sample-A"},{"id":2,"name":"Sample-B"}])");

    JsonItemReader reader(file_path);

    ASSERT_EQ(reader.findAll().size(), 2u);
}

TEST_F(JsonItemReaderTest, FindAllReflectsExternalFileChanges)
{
    writeJsonFile(file_path, R"([{"id":1,"name":"Sample-A"}])");
    JsonItemReader reader(file_path);
    ASSERT_EQ(reader.findAll().size(), 1u);

    writeJsonFile(file_path, R"([{"id":1,"name":"Sample-A"},{"id":2,"name":"Sample-B"}])");
    EXPECT_EQ(reader.findAll().size(), 2u);
}

TEST_F(JsonItemReaderTest, FindByIdReturnsMatchingItem)
{
    writeJsonFile(file_path, R"([{"id":1,"name":"Sample-A"},{"id":2,"name":"Sample-B"}])");
    JsonItemReader reader(file_path);

    const std::optional<Item> found = reader.findById(2);
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(found->name, "Sample-B");
}

TEST_F(JsonItemReaderTest, FindByIdReturnsNulloptWhenMissing)
{
    JsonItemReader reader(file_path);

    EXPECT_FALSE(reader.findById(999).has_value());
}

TEST_F(JsonItemReaderTest, SearchByNameMatchesCaseInsensitiveSubstring)
{
    writeJsonFile(file_path, R"([{"id":1,"name":"Wafer-Sample"},{"id":2,"name":"Other"}])");
    JsonItemReader reader(file_path);

    const std::vector<Item> matched = reader.searchByName("wafer");
    ASSERT_EQ(matched.size(), 1u);
    EXPECT_EQ(matched[0].id, 1);
}

TEST_F(JsonItemReaderTest, SearchByNameReturnsEmptyWhenNoMatch)
{
    writeJsonFile(file_path, R"([{"id":1,"name":"Sample-A"}])");
    JsonItemReader reader(file_path);

    EXPECT_TRUE(reader.searchByName("nonexistent").empty());
}

int main(int argc, char** argv)
{
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
