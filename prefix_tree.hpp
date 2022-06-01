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
    using Sequence = std::vector<EdgeType>;
    std::map<Sequence, NodeInfo> words{};

public:
    PrefixTree() : m_root{ std::make_shared<Node>() } {};

    auto Insert(Sequence sequence, NodeInfo info) -> void
    {
        const auto already_exists = Contains(sequence);

        auto current = m_root;
        for (const auto& edge_value : sequence)
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

    auto Get(Sequence query) const -> std::optional<NodeInfo>
    {
        auto current = m_root;
        for (const auto& edge_value : query)
        {
            bool exists = current->m_next.count(edge_value) > 0;
            if (!exists)
                return std::nullopt;
            current = current->m_next.at(edge_value);
        }
        return current->m_info;
    }

    auto Contains(Sequence query) -> bool { return Get(query).has_value(); }

    auto Empty() const -> bool { return m_size == 0; }

    auto Size() const -> std::size_t { return m_size; }

    auto Erase(Sequence sequence) -> void
    {
        if (!Contains(sequence))
            throw std::runtime_error("Erasing key not present in Trie");

        auto node = GetNode_(sequence);
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
     * @param sequence Sequence corresponding to node.
     * @return Pointer to corresponding node.
     */
    auto GetNode_(Sequence query) -> std::shared_ptr<Node>
    {
        auto current = m_root;
        for (const auto& edge_value : query)
            current = current->m_next.at(edge_value);
        return current;
    }

public:
    NodeInfo m_null_info{};

private:
    std::shared_ptr<Node> m_root{};
    std::size_t m_size{};
};
