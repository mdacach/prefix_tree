#pragma once

class PrefixTree
{
private:
    std::vector<std::string> words{};

public:
    PrefixTree() = default;

    auto Insert(std::string word) -> void { words.push_back(word); }

    auto Contains(std::string query) -> bool
    {
        return std::find(std::begin(words), std::end(words), query) != std::end(words);
    }

    auto Empty() const -> bool { return true; }
  
    auto Size() const -> std::size_t { return 0; }
};
