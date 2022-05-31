#include "catch.hpp"

#include "../prefix_tree.hpp"

using namespace std::string_literals;
SCENARIO("Strings can be inserted into Trie")
{
    GIVEN("A default-constructed Trie")
    {
        auto tree = PrefixTree<int>{};

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
            tree.Insert("apple"s, 0);

            THEN("Trie now contains such string")
            {
                REQUIRE(tree.Contains("apple"s));
            }
        }

        WHEN("We do not insert a string")
        {
            THEN("Trie doesn't contain such string")
            {
                REQUIRE(tree.Contains("apple"s) == false);
            }
        }
    }
}

SCENARIO("Size is kept updated")
{
    GIVEN("A default-constructed Trie")
    {
        auto tree = PrefixTree<int>{};

        WHEN("We add a string")
        {
            tree.Insert("apple"s, 0);
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
                tree.Insert("banana"s, 0);
                THEN("Size increases by one again")
                {
                    REQUIRE(tree.Size() == 2);
                }
            }

            WHEN("We add the same string again")
            {
                tree.Insert("apple"s, 0);
                THEN("Size does not change")
                {
                    REQUIRE(tree.Size() == 1);
                }
            }

            WHEN("We remove a string")
            {
                tree.Erase("apple"s);
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
        auto tree = PrefixTree<int>{};
        tree.Insert("apple"s, 0);
        tree.Insert("banana"s, 0);
        tree.Insert("tomato"s, 0);

        WHEN("We remove a string")
        {
            tree.Erase("banana"s);
            THEN("Trie does not contain such string anymore")
            {
                REQUIRE(tree.Contains("banana"s) == false);
            }
        }

        WHEN("We remove a string which is not there")
        {
            THEN("An exception is thrown")
            {
                REQUIRE_THROWS(tree.Erase("table"s));
            }
        }
    }
}

SCENARIO("Trie stores information in each node")
{
    GIVEN("A Trie with some strings and information")
    {
        auto tree = PrefixTree<int>{};
        tree.Insert("apple"s, 10);
        WHEN("You query a string")
        {
            THEN("You have access to the information of that node")
            {
                REQUIRE(tree.Get("apple"s) == 10);
            }
        }
    }
}

SCENARIO("We can parameterize the information stored in each node")
{
    GIVEN("A Trie storing double")
    {
        auto double_tree = PrefixTree<double>{};
        WHEN("We insert a string associated with a double")
        {
            const auto string = "apple"s;
            double_tree.Insert(string, 10.0);
            THEN("We can get the double out of it")
            {
                REQUIRE(double_tree.Get(string) == 10.0);
            }
        }
    }

    GIVEN("A Trie storing a pair")
    {
        auto pair_tree = PrefixTree<std::pair<int, double>>{};
        WHEN("We insert a string associated with a pair")
        {
            const auto string = "apple"s;
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
        auto custom_tree = PrefixTree<MyData>{};
        WHEN("We insert a string associated with a pair")
        {
            const auto my_data = MyData{ 5, 10.0, "flower"s };
            const auto string = "apple"s;
            custom_tree.Insert(string, my_data);
            THEN("We can get the pair out of it")
            {
                REQUIRE(custom_tree.Get(string) == my_data);
            }
        }
    }
}