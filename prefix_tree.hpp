#pragma once

#include <algorithm>
#include <map>
#include <optional>
#include <string>
#include <vector>

template <typename EdgeType, typename NodeInfo>
class PrefixTree
{
private:
    class Node
    {
        using Edges = std::map<EdgeType, std::shared_ptr<Node>>;

    public:
        Edges m_next{};                   // Possible paths from this node
        std::optional<NodeInfo> m_info{}; // Information associated with this node
    };
    using Key = std::vector<EdgeType>;

public:
    PrefixTree() : m_root{ std::make_shared<Node>() } {};

    auto Insert(const Key& key, NodeInfo info) -> void
    {
        const auto already_exists = Contains(key);

        auto current = m_root;
        for (const auto& edge_value : key)
        {
            bool exists = current->m_next.count(edge_value) > 0;
            if (!exists)
            {
                // Intermediate node did not exist, so we must create it now
                auto temp = std::make_shared<Node>();
                current->m_next[edge_value] = temp;
                current = temp;
            }
            else
            {
                current = current->m_next.at(edge_value);
            }

            current->m_info = info;
        }

        if (!already_exists)
            ++m_size;
    }

    auto Get(const Key& key) const -> std::optional<NodeInfo>
    {
        auto current = m_root;
        for (const auto& edge_value : key)
        {
            bool exists = current->m_next.count(edge_value) > 0;
            if (!exists)
                return std::nullopt;
            current = current->m_next.at(edge_value);
        }
        return current->m_info;
    }

    auto Contains(const Key& key) const -> bool { return Get(key).has_value(); }

    auto Empty() const -> bool { return m_size == 0; }

    auto Size() const -> std::size_t { return m_size; }

    auto Erase(const Key& key) -> void
    {
        if (!Contains(key))
            throw std::runtime_error("Erasing key not present in Trie");

        auto node = GetNode_(key);
        auto& info = node->m_info;
        if (info)
            --m_size;
        info = std::nullopt;
    }

private:
    /**
     * Returns a reference to an existing node in the Trie. \n
     * \n
     * To be used internally only. \n
     * REQUIRES: That the node exists.
     * @param sequence Key corresponding to node.
     * @return Pointer to corresponding node.
     */
    auto GetNode_(const Key& key) -> std::shared_ptr<Node>
    {
        auto current = m_root;
        for (const auto& edge_value : key)
            current = current->m_next.at(edge_value);
        return current;
    }

public:
    NodeInfo m_null_info{};

private:
    std::shared_ptr<Node> m_root{};
    std::size_t m_size{};
};
