#include <editor-version/Repository.h>

#include <test_data.h>

#include <gtest/gtest.h>

TEST(TestRepository, openExisting)
{
    std::shared_ptr repo{version::open_repository(version::test::EXISTING_REPOSITORY)};

    EXPECT_TRUE(repo);
}

TEST(TestRepository, openNonExisting)
{
    EXPECT_THROW(version::open_repository(version::test::NONEXISTING_REPOSITORY), std::runtime_error);
}
