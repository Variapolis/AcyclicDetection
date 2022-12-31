#include <functional>
#include <iostream>

#include "DirectedGraph.h"

int main()
{
    const std::string filename = "benchmarks/cyclic/c_10240_4.txt";
    std::cout << filename << std::endl;
    DirectedGraph graph = DirectedGraph(filename);
    
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