#include <cassert>
#include <iostream>

#include "prefix_tree.hpp"

int main()
{
    auto tree = PrefixTree<int, int>{};

    auto values1 = { 1, 2, 3 };
    auto info1 = 10;

    auto values2 = { 1, 2 };
    auto info2 = 20;

    auto values3 = { 3, 4 };
    auto info3 = 30;

    tree.Insert(values1, info1);
    tree.Insert(values2, info2);
    tree.Insert(values3, info3);
    // After those operations, the Trie looks like this:
    /*

           ┌──┐
           │  │
           └──┘
        3 /    \ 1
       ┌──┐    ┌──┐
       │  │    │  │
       └──┘    └──┘
    4 /            \ 2
   ┌──┐             ┌──┐
   │30│             │20│
   └──┘             └──┘
                        \ 3
                         ┌──┐
                         │10│
                         └──┘

     */
    // Where the terminal nodes have information associated and can be queried.
    assert(tree.Size() == 3);
    assert(tree.Get(values1) == info1);
    assert(tree.Get(values2) == info2);
    assert(tree.Get(values3) == info3);

    // The intermediate notes can not be queried
    // assert(tree.Get({1, 2})); // Runtime Error
    assert(tree.Contains({ 1 }) == false);

    tree.Erase(values2);
    assert(tree.Contains(values2) == false);
    assert(tree.Contains(values3)); // Other nodes are still ok, even if on the "path"

    // Update a value
    tree.Insert(values2, 50);
    assert(tree.Get(values2) == 50);
}