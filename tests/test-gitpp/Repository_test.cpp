#include <gitpp/Repository.h>

#include <test_data.h>

#include <gtest/gtest.h>

#include <algorithm>
#include <filesystem>
#include <fstream>

namespace
{

class RepositoryTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        const ::testing::TestInfo *test_info = ::testing::UnitTest::GetInstance()->current_test_info();
        m_test_dir = std::filesystem::path{gitpp::test::SCRATCH_DIR} / test_info->name();
        std::filesystem::remove_all(m_test_dir);
        std::filesystem::create_directories(m_test_dir);
    }

    void TearDown() override
    {
        std::filesystem::remove_all(m_test_dir);
    }

    void write_file(const char *name, const std::string &content)
    {
        std::ofstream out(m_test_dir / name);
        out << content;
    }

    std::filesystem::path m_test_dir;
};

TEST_F(RepositoryTest, commitToEmptyRepository)
{
    gitpp::Repository::create(m_test_dir);
    gitpp::Repository repo(m_test_dir);
    write_file("test.txt", "Hello");
    repo.stage_file("test.txt");
    repo.commit("Initial commit");

    EXPECT_FALSE(repo.is_empty());
}

TEST_F(RepositoryTest, commitWithParent)
{
    gitpp::Repository::create(m_test_dir);
    gitpp::Repository repo(m_test_dir);
    write_file("test.txt", "First");
    repo.stage_file("test.txt");
    repo.commit("First commit");
    write_file("test.txt", "Second");
    repo.stage_file("test.txt");
    repo.commit("Second commit");

    auto history = repo.get_file_history("test.txt");

    EXPECT_EQ(2, history.size());
}

TEST_F(RepositoryTest, getFileHistoryEmptyRepository)
{
    gitpp::Repository::create(m_test_dir);
    gitpp::Repository repo(m_test_dir);

    auto history = repo.get_file_history("nonexistent.txt");

    EXPECT_TRUE(history.empty());
}

TEST_F(RepositoryTest, getFileHistorySingleCommit)
{
    gitpp::Repository::create(m_test_dir);
    gitpp::Repository repo(m_test_dir);
    write_file("test.txt", "Hello");
    repo.stage_file("test.txt");
    repo.commit("Initial commit");

    auto history = repo.get_file_history("test.txt");

    ASSERT_EQ(1, history.size());
    EXPECT_EQ("Initial commit", history[0].message);
    EXPECT_FALSE(history[0].id.empty());
    EXPECT_FALSE(history[0].timestamp.empty());
}

TEST_F(RepositoryTest, getFileHistoryMultipleCommits)
{
    gitpp::Repository::create(m_test_dir);
    gitpp::Repository repo(m_test_dir);
    write_file("test.txt", "First");
    repo.stage_file("test.txt");
    repo.commit("First commit");
    write_file("test.txt", "Second");
    repo.stage_file("test.txt");
    repo.commit("Second commit");
    write_file("test.txt", "Third");
    repo.stage_file("test.txt");
    repo.commit("Third commit");

    auto history = repo.get_file_history("test.txt");

    ASSERT_EQ(3, history.size());
    std::vector<std::string> messages;
    for (const auto &commit : history)
    {
        messages.push_back(commit.message);
    }
    EXPECT_NE(std::find(messages.begin(), messages.end(), "First commit"), messages.end());
    EXPECT_NE(std::find(messages.begin(), messages.end(), "Second commit"), messages.end());
    EXPECT_NE(std::find(messages.begin(), messages.end(), "Third commit"), messages.end());
}

TEST_F(RepositoryTest, getFileHistoryOnlyIncludesCommitsAffectingFile)
{
    gitpp::Repository::create(m_test_dir);
    gitpp::Repository repo(m_test_dir);
    write_file("a.txt", "File A");
    repo.stage_file("a.txt");
    repo.commit("Commit A");
    write_file("b.txt", "File B");
    repo.stage_file("b.txt");
    repo.commit("Commit B");
    write_file("a.txt", "File A updated");
    repo.stage_file("a.txt");
    repo.commit("Commit A2");

    auto history_a = repo.get_file_history("a.txt");
    auto history_b = repo.get_file_history("b.txt");

    ASSERT_EQ(2, history_a.size());
    EXPECT_EQ("Commit A2", history_a[0].message);
    EXPECT_EQ("Commit A", history_a[1].message);
    ASSERT_EQ(1, history_b.size());
    EXPECT_EQ("Commit B", history_b[0].message);
}

TEST_F(RepositoryTest, getFileContentRetrievesCorrectVersion)
{
    gitpp::Repository::create(m_test_dir);
    gitpp::Repository repo(m_test_dir);
    write_file("test.txt", "Version 1");
    repo.stage_file("test.txt");
    repo.commit("First commit");
    write_file("test.txt", "Version 2");
    repo.stage_file("test.txt");
    repo.commit("Second commit");
    auto history = repo.get_file_history("test.txt");
    ASSERT_EQ(2, history.size());

    std::string content_v2 = repo.get_file_content(history[0].id.c_str(), "test.txt");
    std::string content_v1 = repo.get_file_content(history[1].id.c_str(), "test.txt");

    EXPECT_EQ("Version 2", content_v2);
    EXPECT_EQ("Version 1", content_v1);
}

TEST_F(RepositoryTest, getFileContentRoundTrip)
{
    gitpp::Repository::create(m_test_dir);
    gitpp::Repository repo(m_test_dir);
    const std::string original_content = "Hello, World!\nLine 2\nLine 3";
    write_file("test.txt", original_content);
    repo.stage_file("test.txt");
    repo.commit("Test commit");
    auto history = repo.get_file_history("test.txt");
    ASSERT_EQ(1, history.size());

    std::string retrieved = repo.get_file_content(history[0].id.c_str(), "test.txt");

    EXPECT_EQ(original_content, retrieved);
}

} // namespace
