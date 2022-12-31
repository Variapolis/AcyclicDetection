#pragma once
#include <iostream>

struct DebugData
{
    std::vector<bool> visitedVec;
    std::vector<bool> recursionVec;
    std::vector<int> recursionStack;

    DebugData() = default;

    void print_recursion_stack() const
    {
        std::cout << std::endl << "\nPath:" << std::endl;
        for (auto reverse_iterator = recursionStack.rbegin(); reverse_iterator != recursionStack.rend();
             ++reverse_iterator)
            std::cout << *reverse_iterator << (reverse_iterator != recursionStack.rend() - 1 ? " -> " : " ");

        std::cout << std::endl << "\nCycle Found:" << std::endl;
        const auto keyItr = std::find(recursionStack.rbegin(), recursionStack.rend(),
                                      recursionStack[0]);
        for (auto reverse_iterator = keyItr; reverse_iterator != recursionStack.rend();
             ++reverse_iterator)
            std::cout << *reverse_iterator << (reverse_iterator != recursionStack.rend() - 1 ? " -> " : " ");
        std::cout << std::endl;
    }

    void print_visited_nodes()
    {
        std::cout << "Visited the following nodes: ";
        for (auto i = 0; i < visitedVec.size(); i++)
        {
            if (visitedVec[i]) std::cout << i << " ";
        }
        std::cout << std::endl;
    }
};
