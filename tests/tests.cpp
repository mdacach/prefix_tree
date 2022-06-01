#include "catch.hpp"

#include "../prefix_tree.hpp"

// For generalization, we must now use a vector instead of a string

// Utility function to convert a string literal into a vector of char
std::vector<char> operator""_vc(const char* string, std::size_t length)
{
    std::vector<char> as_chars;
    for (std::size_t i = 0; i < length; ++i)
        as_chars.push_back(string[i]);
    return as_chars;
}

using namespace std::string_literals;
SCENARIO("Strings can be inserted into Trie")
{
    GIVEN("A default-constructed Trie")
    {
        auto tree = PrefixTree<char, int>{};

        WHEN("No strings were inserted yet")
        {
            THEN("Trie is empty, and size is zero")
            {
                REQUIRE(tree.Empty());
                REQUIRE(tree.Size() == 0);
            }
        }

        WHEN("We insert a string")
        {
            tree.Insert("apple"_vc, 0);

            THEN("Trie now contains such string")
            {
                REQUIRE(tree.Contains("apple"_vc));
            }
        }

        WHEN("We do not insert a string")
        {
            THEN("Trie doesn't contain such string")
            {
                REQUIRE(tree.Contains("apple"_vc) == false);
            }
        }
    }
}

SCENARIO("Size is kept updated")
{
    GIVEN("A default-constructed Trie")
    {
        auto tree = PrefixTree<char, int>{};

        WHEN("We add a string")
        {
            tree.Insert("apple"_vc, 0);
            THEN("Size increases by one")
            {
                REQUIRE(tree.Size() == 1);
            }

            THEN("Trie is not empty anymore")
            {
                REQUIRE(tree.Empty() == false);
            }

            WHEN("We add a second string")
            {
                tree.Insert("banana"_vc, 0);
                THEN("Size increases by one again")
                {
                    REQUIRE(tree.Size() == 2);
                }
            }

            WHEN("We add the same string again")
            {
                tree.Insert("apple"_vc, 0);
                THEN("Size does not change")
                {
                    REQUIRE(tree.Size() == 1);
                }
            }

            WHEN("We remove a string")
            {
                tree.Erase("apple"_vc);
                THEN("Size decreases by one")
                {
                    REQUIRE(tree.Size() == 0);
                }
            }
        }
    }
}

SCENARIO("Strings can be removed from Trie")
{
    GIVEN("A Trie with some strings inserted")
    {
        auto tree = PrefixTree<char, int>{};
        tree.Insert("apple"_vc, 0);
        tree.Insert("banana"_vc, 0);
        tree.Insert("tomato"_vc, 0);

        WHEN("We remove a string")
        {
            tree.Erase("banana"_vc);
            THEN("Trie does not contain such string anymore")
            {
                REQUIRE(tree.Contains("banana"_vc) == false);
            }
        }

        WHEN("We remove a string which is not there")
        {
            THEN("An exception is thrown")
            {
                REQUIRE_THROWS(tree.Erase("table"_vc));
            }
        }
    }
}

SCENARIO("Trie stores information in each node")
{
    GIVEN("A Trie with some strings and information")
    {
        auto tree = PrefixTree<char, int>{};
        tree.Insert("apple"_vc, 10);
        WHEN("You query a string")
        {
            THEN("You have access to the information of that node")
            {
                REQUIRE(tree.Get("apple"_vc) == 10);
            }
        }
    }
}

SCENARIO("We can parameterize the information stored in each node")
{
    GIVEN("A Trie storing double")
    {
        auto double_tree = PrefixTree<char, double>{};
        WHEN("We insert a string associated with a double")
        {
            const auto string = "apple"_vc;
            double_tree.Insert(string, 10.0);
            THEN("We can get the double out of it")
            {
                REQUIRE(double_tree.Get(string) == 10.0);
            }
        }
    }

    GIVEN("A Trie storing a pair")
    {
        auto pair_tree = PrefixTree<char, std::pair<int, double>>{};
        WHEN("We insert a string associated with a pair")
        {
            const auto string = "apple"_vc;
            pair_tree.Insert(string, std::pair<int, double>(5, 10.0));
            THEN("We can get the pair out of it")
            {
                REQUIRE(pair_tree.Get(string) == std::pair<int, double>(5, 10.0));
            }
        }
    }

    GIVEN("A Trie storing a custom structure")
    {
        struct MyData
        {
            int a{};
            double b{};
            std::string c{};

            bool operator==(const MyData& rhs) const { return a == rhs.a && b == rhs.b && c == rhs.c; }
        };
        auto custom_tree = PrefixTree<char, MyData>{};
        WHEN("We insert a string associated with a pair")
        {
            const auto my_data = MyData{ 5, 10.0, "flower"s };
            const auto string = "apple"_vc;
            custom_tree.Insert(string, my_data);
            THEN("We can get the pair out of it")
            {
                REQUIRE(custom_tree.Get(string) == my_data);
            }
        }
    }
}

SCENARIO("We can parameterize on the edges")
{
    // A "word" is just a sequence of "char"
    // We can generalize this idea to support any sequence
    GIVEN("A Trie with integer values as edges")
    {
        auto tree = PrefixTree<int, int>{};
        WHEN("We add a vector of integers")
        {
            tree.Insert({ 1, 2, 3, 4 }, 10);
            THEN("It creates a node")
            {
                REQUIRE(tree.Contains({ 1, 2, 3, 4 }));
            }
        }
    }
}

SCENARIO("Insertion creates non-terminal nodes")
{
    GIVEN("An empty Trie")
    {
        auto tree = PrefixTree<char, int>{};
        WHEN("We insert a big word")
        {
            tree.Insert("banana"_vc, 10);
            THEN("We also create the intermediate non-terminal nodes")
            {
                REQUIRE(tree.Contains("b"_vc));
                REQUIRE(tree.Contains("ba"_vc));
                REQUIRE(tree.Contains("banan"_vc));
            }
        }
    }
}