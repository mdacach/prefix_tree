#include "catch.hpp"

#include "../prefix_tree.hpp"

using namespace std::string_literals;
SCENARIO("Strings can be inserted into Trie")
{
    GIVEN("A default-constructed Trie")
    {
        auto tree = PrefixTree{};

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
            tree.Insert("apple"s);

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
        auto tree = PrefixTree{};

        WHEN("We add a string")
        {
            tree.Insert("apple"s);
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
                tree.Insert("banana"s);
                THEN("Size increases by one again")
                {
                    REQUIRE(tree.Size() == 2);
                }
            }

            WHEN("We add the same string again")
            {
                tree.Insert("apple"s);
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
        auto tree = PrefixTree{};
        tree.Insert("apple"s);
        tree.Insert("banana"s);
        tree.Insert("tomato"s);

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