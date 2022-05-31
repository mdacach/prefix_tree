#pragma once

#include <algorithm>
#include <map>
#include <string>
#include <vector>

template <typename EdgeType, typename NodeInfo>
class PrefixTree
{
private:
    using Sequence = std::vector<EdgeType>;
    std::map<Sequence, NodeInfo> words{};
    std::size_t size{};

public:
    PrefixTree() = default;

    auto Insert(Sequence word, NodeInfo info) -> void
    {
        if (this->Contains(word))
            return;
        ++size;
        words[word] = info;
    }

    auto Get(Sequence query) const -> NodeInfo { return words.at(query); }

    auto Contains(Sequence query) -> bool
    {
        const auto itr = words.find(query);
        return itr != std::end(words);
    }

    auto Empty() const -> bool { return size == 0; }

    auto Size() const -> std::size_t { return size; }

    auto Erase(Sequence word) -> void
    {
        if (!this->Contains(word))
            throw std::runtime_error("Erasing string not present in Trie");

        words.erase(word);
        --size;
    }
};
