#include <iostream>
#include "DirectedGraph.h"
#include <fstream>
#include <filesystem>
#include <map>

int extract_graph_type(std::string filename)
{
    size_t startPos = filename.find('_');
    size_t endPos = filename.find('.');
    bool isAcyclic = filename[startPos-1] == 'a';
    return std::stoi(filename.substr(startPos + 1, endPos - startPos - 3)) + isAcyclic;
}

void print_time_map(const std::map<int, int>& time_map)
{
    for (auto element : time_map)
    {
        bool isCyclic = element.first % 40;
        std::string value = (isCyclic == 0 ? "Cyclic " : "Acyclic ") + std::to_string(element.first - isCyclic);
        std::cout << value << ":\t" << element.second << "ms" << std::endl;
    }
}

void run(std::string fpath)
{
    std::map<int, int> cyclicTimeMap;
    DebugData data = DebugData();
    for (const auto& entry : std::filesystem::recursive_directory_iterator(fpath))
    {
        // File Setup.
        if(!entry.is_regular_file()) continue;
        std::cout << "==========\tTrying to open: " << entry.path() << "\t==========" << std::endl;
        DirectedGraph directedGraph = DirectedGraph(entry.path().string());
        clock_t t = clock();
        bool isCyclic = directedGraph.is_cyclic(data);

        // Running algorithm and timing.
        t = clock() - t;
        const int elapsed = t;
        int graphType = extract_graph_type(entry.path().string());
        if (cyclicTimeMap.find(graphType) == cyclicTimeMap.end()) cyclicTimeMap.insert(std::pair(graphType, elapsed));
        else cyclicTimeMap[graphType] = cyclicTimeMap[graphType] + elapsed / 2;

        // Printing Output data per graph.
        data.print_visited_nodes();
        std::cout << "Graph Type: " << (isCyclic ? "No (Cyclic)" : "Yes (Acyclic)") << std::endl;
        if(isCyclic) data.print_recursion_stack();
        std::cout << "\nElapsed time = " << elapsed << " ms" << std::endl;
        std::cout << "Finished with: " << entry.path() << "\t==========" << std::endl;
    }
    //Printing averaged data per graph size and type.
    std::cout << "\n==========\t Time Results: \t==========" << std::endl;
    print_time_map(cyclicTimeMap);
}

int main()
{
    while(true)
    {
        std::cout << "Press any key to run." << std::endl;
        std::cin.get();
        const std::string filename = "benchmarks";
        run(filename);
    }
}
