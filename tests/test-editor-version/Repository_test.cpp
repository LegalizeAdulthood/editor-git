#include <editor-version/Repository.h>

#include <test_data.h>

#include <gtest/gtest.h>

TEST(TestRepository, openExisting)
{
    std::shared_ptr repo{version::open_repository(version::test::EXISTING_EMPTY_REPOSITORY)};

    EXPECT_TRUE(repo);
}

TEST(TestRepository, openNonExisting)
{
    EXPECT_THROW(version::open_repository(version::test::NON_EXISTING_REPOSITORY), std::runtime_error);
}

TEST(TestRepository, openExistingEmpty)
{
    std::shared_ptr repo{version::open_repository(version::test::EXISTING_EMPTY_REPOSITORY)};

    EXPECT_TRUE(repo->is_empty());
}

TEST(TestRepository, createSetsUserNameEmail)
{
    std::filesystem::remove_all(version::test::SCRATCH_DIR);
    std::filesystem::create_directory(version::test::SCRATCH_DIR);

    std::shared_ptr repo{version::create_repository(version::test::SCRATCH_DIR)};

    ASSERT_TRUE(repo);
    EXPECT_EQ("Utah C++ Editor Version", repo->get_config_string("user.name"));
    EXPECT_EQ("utahcpp@example.com", repo->get_config_string("user.email"));
}
