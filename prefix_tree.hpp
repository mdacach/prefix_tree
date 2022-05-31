#pragma once

#include <algorithm>
#include <string>
#include <vector>

class PrefixTree
{
private:
    std::vector<std::string> words{};
    std::size_t size{};

public:
    PrefixTree() = default;

    auto Insert(std::string word) -> void
    {
        if (this->Contains(word))
            return;
        ++size;
        words.push_back(word);
    }

    auto Contains(std::string query) -> bool
    {
        return std::find(std::begin(words), std::end(words), query) != std::end(words);
    }

    auto Empty() const -> bool { return true; }

    auto Size() const -> std::size_t { return size; }

    auto Erase(std::string word) -> void
    {
        if (!this->Contains(word))
            throw std::runtime_error("Erasing string not present in Trie");

        words.erase(std::remove(std::begin(words), std::end(words), word), std::end(words));
        --size;
    }
};
