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

TEST(TestRepository, emptyRepositoryBeginEqualsEnd)
{
    std::shared_ptr repo{version::open_repository(version::test::EXISTING_EMPTY_REPOSITORY)};

    EXPECT_EQ(repo->begin(), repo->end());
}
