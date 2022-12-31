#include "DirectedGraph.h"

#include <fstream>
#include <iostream>
#include <xmemory>

DirectedGraph::DirectedGraph(int s): size(s), adjacency(s)
{
}

DirectedGraph::DirectedGraph(std::string filename)
{
    std::ifstream file;
    file.open(filename);
    std::string line;
    if (file.fail() || file.eof()) std::cout << "Failed to open file" << std::endl;
    std::getline(file, line);
    size = std::stoi(line);
    adjacency.resize(size);
    while (!file.eof())
    {
        std::getline(file, line);
        if (line.empty()) continue;
        int left, right;
        size_t pos = line.find(' ');
        left = std::stoi(line.substr(0, pos));
        right = std::stoi(line.substr(pos + 1, line.length()));
        add_edge(left, right);
    }
    file.close();
}

void DirectedGraph::add_edge(int from, int to)
{
    adjacency.at(from).push_back(to);
}

void DirectedGraph::remove_edge(int from, int to)
{
    std::remove(adjacency.at(from).begin(), adjacency.at(from).end(), to);
}

void DirectedGraph::print()
{
    for (auto i = 0; i < adjacency.size(); i++)
    {
        std::cout << i << " contains ";
        for (auto j = 0; j < adjacency[i].size(); j++)
        {
            std::cout << adjacency[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> DirectedGraph::get_adjacency_list()
{
    return adjacency;
}

bool DirectedGraph::is_cyclic()
{
    std::vector<bool> visitedVec(size);
    std::vector<bool> recursionVec(size);
    std::vector<int> recursionStack(0);

    for (auto i = 0; i < size; i++)
        if (!visitedVec[i] && is_cyclic_util(i, visitedVec, recursionVec, recursionStack))
        {
            recursionStack.push_back(i);
            print_visited_nodes(visitedVec);
            print_recursion_stack(recursionStack);
            return true;
        }
    return false;
}

bool DirectedGraph::is_cyclic_util(int current, std::vector<bool>& visitedVec, std::vector<bool>& recursionVec,
                                   std::vector<int>& recursionStack)
{
    visitedVec[current] = true;
    recursionVec[current] = true;

    for (const int nodeVal : adjacency[current])
        if ((!visitedVec[nodeVal] && is_cyclic_util(nodeVal, visitedVec, recursionVec, recursionStack)) ||
            recursionVec[nodeVal])
        {
            recursionStack.push_back(nodeVal);
            return true;
        }
    recursionVec[current] = false;
    return false;
}

void DirectedGraph::print_recursion_stack(std::vector<int> recursionStack)
{
    std::cout << std::endl << "\nPath:" << std::endl;
    for (auto reverse_iterator = recursionStack.rbegin(); reverse_iterator != recursionStack.rend();
         ++reverse_iterator)
        std::cout << *reverse_iterator << (reverse_iterator != recursionStack.rend() - 1 ? " -> " : " ");

    std::cout << std::endl << "\nCycle Found:" << std::endl;
    const std::vector<int>::reverse_iterator keyItr = std::find(recursionStack.rbegin(), recursionStack.rend(),
                                                                recursionStack[0]);
    for (auto reverse_iterator = keyItr; reverse_iterator != recursionStack.rend();
         ++reverse_iterator)
        std::cout << *reverse_iterator << (reverse_iterator != recursionStack.rend() - 1 ? " -> " : " ");
    std::cout << std::endl;
}

void DirectedGraph::print_visited_nodes(std::vector<bool> visitedVec)
{
    std::cout << "Visited the following nodes: ";
    for (auto i = 0; i < visitedVec.size(); i++)
    {
        if (visitedVec[i]) std::cout << i << " ";
    }
    std::cout << std::endl;
}
