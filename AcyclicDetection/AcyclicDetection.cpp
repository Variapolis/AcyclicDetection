#include <functional>
#include <iostream>

#include "DirectedGraph.h"

int main()
{
    std::string input;
    std::cin >> input;
    DirectedGraph graph = DirectedGraph(input);
    
    // std::string h;
    // graph.print();
    // std::cin >> h;
    clock_t t = clock();
    std::cout << (graph.is_cyclic() ? "No" : "Yes") << std::endl;
    t = clock() - t;
    const double elapsed = static_cast<double>(t) / CLOCKS_PER_SEC;
    std::cout << "\nElapsed time = " << elapsed << " seconds";


    return 0;
}