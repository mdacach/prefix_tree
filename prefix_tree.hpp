#pragma once

#include <algorithm>
#include <map>
#include <string>
#include <vector>

template <typename NodeInfo>
class PrefixTree
{
private:
    std::map<std::string, NodeInfo> words{};
    std::size_t size{};

public:
    PrefixTree() = default;

    auto Insert(std::string word, NodeInfo info) -> void
    {
        if (this->Contains(word))
            return;
        ++size;
        words[word] = info;
    }

    auto Get(std::string query) const -> NodeInfo { return words.at(query); }

    auto Contains(std::string query) -> bool
    {
        const auto itr = words.find(query);
        return itr != std::end(words);
    }

    auto Empty() const -> bool { return size == 0; }

    auto Size() const -> std::size_t { return size; }

    auto Erase(std::string word) -> void
    {
        if (!this->Contains(word))
            throw std::runtime_error("Erasing string not present in Trie");

        words.erase(word);
        --size;
    }
};
