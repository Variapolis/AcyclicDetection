#pragma once
#include <string>
#include <vector>

class DirectedGraph
{
public:
    int size;
    std::vector<std::vector<int>> adjacency;

    DirectedGraph(int s);

    DirectedGraph(std::string filename);

    void add_edge(int from, int to);

    void remove_edge(int from, int to);

    void print();
    
    std::vector<std::vector<int>> get_adjacency_list();

    bool is_cyclic();

private:
    bool is_cyclic_util(int current, std::vector<bool>& visitedVec, std::vector<bool>& recursionVec, std::vector<int>& recursionStack);
    static void print_recursion_stack(std::vector<int> recursionStack);
    static void print_visited_nodes(std::vector<bool> visitedVec);
};
