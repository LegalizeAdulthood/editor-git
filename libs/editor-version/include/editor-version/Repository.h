#pragma once

#include <boost/stl_interfaces/iterator_interface.hpp>

#include <filesystem>
#include <memory>
#include <string>

namespace version
{

struct Commit
{
    std::string hash;
};

class Repository
{
public:
    class Iterator
        : public boost::stl_interfaces::iterator_interface<Iterator, std::random_access_iterator_tag, Commit, Commit>
    {
    public:
        Iterator();
        explicit Iterator(Repository *repository);
        ~Iterator() = default;

        Commit operator*() const noexcept;
        Iterator &operator+=(std::ptrdiff_t count) noexcept;
        difference_type operator-(const Iterator &other) const;

    private:
        Repository *m_repository{};
    };

    virtual ~Repository() = default;

    virtual bool is_empty() const = 0;

    virtual Iterator begin() = 0;
    virtual Iterator end() = 0;
};

std::shared_ptr<Repository> open_repository(const std::filesystem::path &path);

} // namespace version
