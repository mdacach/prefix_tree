#pragma once

#include <algorithm>
#include <map>
#include <optional>
#include <string>
#include <vector>

/**
 * Prefix Tree (Trie) structure. \n
 * \n
 * Supports insertions and queries efficiently, both runtime and memory-wise. \n
 * This structure is commonly used for String applications (think "word dictionary"), but it
 * can be generalized for queries about "sequences" of values (String is a sequence of chars). \n
 * Refer to: https://en.wikipedia.org/wiki/Trie \n
 * \n
 * @tparam EdgeType Value represented in an edge. In the case of a string application, this value would
 * be a "char", and we would query on "vector of chars". `EdgeType` MUST be valid as a std::map key.
 * @tparam NodeInfo Information to be stored in nodes. Can be any type, include custom structures.
 */
template <typename EdgeType, typename NodeInfo>
class PrefixTree
{
private:
    /**
     * Node inside the Trie. \n
     * \n
     * Stores its edges as pointers to other nodes, through a std::map. \n
     * A node can be created by inserting Keys into the Trie. \n
     * Inserting a Key into the Trie may create "intermediate" (non-terminal) nodes (refer to `Insert`). \n
     *
     */
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

    /**
     * Inserts a new node into the Trie. \n
     * \n
     * If a node with such a key already exists, the information stored there
     * will be overwritten. \n
     * @param key Key the node will represent.
     * @param info Information to store in node.
     */
    auto Insert(const Key& key, NodeInfo info) -> void
    {
        // TODO: optimize this to remove the extra call
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
        }

        current->m_info = std::move(info);
        if (!already_exists)
            ++m_size;
    }

    /**
     * Returns the information associated with such a key as an std::optional. \n
     * \n
     * If the key does not exist, returns std::nullopt. \n
     * @param key Key associated with the node.
     * @return Optional with NodeInfo if exists, std::nullopt if it does not.
     */
    auto Get(const Key& key) const -> std::optional<NodeInfo>
    {
        // TODO: use optional to reference to avoid info copying (Sy Brand's probably)
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

    /**
     * Returns true if node with associated key exists in Trie, false otherwise. \n
     * @param key Key associated with the node.
     * @return Boolean indicating if such node exists or not.
     */
    auto Contains(const Key& key) const -> bool { return Get(key).has_value(); }

    /**
     * Returns true if Trie has no nodes.
     * @return Boolean indicating if Trie has no nodes.
     */
    auto Empty() const -> bool { return m_size == 0; }

    /**
     * Returns the number of *terminal* nodes in the Trie. Refer to Trie definition. \n
     * @return Number of terminal nodes currently in the Trie.
     */
    auto Size() const -> std::size_t { return m_size; }

    /**
     * Erases a node from a Trie. \n
     * \n
     * Specifically, it erases the *information* associated with such a node. \n
     * After erasing x, Get(x) returns std::nullopt and Contains(x) returns false.
     * @param key Node to erase.
     */
    auto Erase(const Key& key) -> void
    {
        // TODO: test if size is updating correctly when we insert into erased position.
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

private:
    std::shared_ptr<Node> m_root{};
    std::size_t m_size{}; // Number of terminal nodes in Trie. It may also be interesting to keep number of ALL nodes.
};
