#include "../Libs/Graph/Headers/s21_graph.h"
#include "../Libs/Graph/Headers/s21_graph_algorithms.h"
#include <iostream>
#include <memory>
#include <chrono>

namespace s21 {

class Command {
    public:
        virtual ~Command() {}
        virtual void execute() = 0;
};

class SimpleNavigator {
    public:
        void start();
    private:
        Graph graph_;
        GraphAlgorithm graphAlgorithm_;
        std::vector<std::shared_ptr<Command>> commands_;
        std::string menu_ = ""
        "0.load graph from file\n"
        "1.export graph to dot\n"
        "2.depth first search\n"
        "3.breadth first search\n"
        "4.get shortest path between vertices\n"
        "5.get shortest paths between all vertices\n"
        "6.get least spanning tree\n"
        "7.solve traveling salesman problem(ant algorithm)\n"
        "8.solve traveling salesman problem(brute force algrorithm)\n"
        "9.solve traveling salesman problem(branch and bound algorithm)\n"
        "10.solve traveling salesman problem(speed test)\n"
        "11.exit\n";
};

} // namespace s21