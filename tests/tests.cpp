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