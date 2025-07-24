#include <iostream>
#include <string>
#include <chrono>
#include <limits>
#include <unordered_set>
#include "Graph.h"

/* Macro to explicity print tests that are run along with colorized result. */
#define TEST(EX) (void)((fprintf(stdout, "(%s:%d) %s:", __FILE__, __LINE__,\
                 #EX)) && ((EX && fprintf(stdout, "\t\x1b[32mPASSED\x1b[0m\n"))\
                 || (fprintf(stdout, "\t\x1b[31mFAILED\x1b[0m\n")) ))

bool compare(const double& d1, const double& d2) {
    return std::abs(d1 - d2) <= std::numeric_limits<double>::epsilon();
}

int main() {
    Graph graph("example/small.csv");
    cout << graph.edge_weight("A","C") << "\n";
    auto n = graph.nodes();
    TEST(graph.nodes() == unordered_set<string>({"A", "B", "C", "D", "E", "F", "G"}));
    TEST(graph.num_nodes() == 7);
    TEST(graph.edge_weight("A", "B") == 1);
    TEST(graph.edge_weight("B", "A") == 1);
    TEST(graph.edge_weight("A","C") == 5);
    TEST(graph.edge_weight("F","G") == 5);
    TEST(graph.edge_weight("G","F") == 5);
    TEST(graph.edge_weight("A","X") == -1);
    TEST(graph.num_edges() == 6);
    TEST(graph.neighbors("A") == unordered_set<string>({"B","C"}));
    TEST(graph.num_neighbors("A") == 2);
    TEST(graph.num_neighbors("B") == 3);
    TEST(graph.num_neighbors("X") == 0);
    TEST(graph.neighbors("B") == unordered_set<string>({"A","C","D"}));
    TEST(graph.neighbors("E") == unordered_set<string>({"F"}));
    TEST(graph.neighbors("X") == unordered_set<string>({}));
    vector<tuple<string, string, int>> result {{"A", "B", 1},{"B", "C", 1}};
    auto start = std::chrono::steady_clock::now();
    TEST(graph.shortest_path_weighted("A", "C") == result);
    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    TEST(elapsed.count() <= 1000.0); // microseconds

    start = std::chrono::steady_clock::now();
    TEST(graph.smallest_connecting_threshold("A", "C") == 1);
    end = std::chrono::steady_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    TEST(elapsed.count() <= 1000.0); // microseconds



        TEST(graph.neighbors("A") == unordered_set<string>({"B", "C"}));
    TEST(graph.neighbors("B") == unordered_set<string>({"C", "D", "A"}));
    TEST(graph.neighbors("C") == unordered_set<string>({"A", "B"}));
    TEST(graph.neighbors("D") == unordered_set<string>({"B"}));
    TEST(graph.neighbors("E") == unordered_set<string>({"F"}));
    TEST(graph.neighbors("F") == unordered_set<string>({"E","G"}));
    TEST(graph.neighbors("G") == unordered_set<string>({"F"}));
    TEST(graph.neighbors("X") == unordered_set<string>({}));
    TEST(graph.neighbors("Q") == unordered_set<string>({}));
    TEST(graph.neighbors("q") == unordered_set<string>({}));

    TEST(graph.num_neighbors("A") == 2);
    TEST(graph.num_neighbors("B") == 3);
    TEST(graph.num_neighbors("C") == 2);
    TEST(graph.num_neighbors("D") == 1);
    TEST(graph.num_neighbors("E") == 1);
    TEST(graph.num_neighbors("F") == 2);
    TEST(graph.num_neighbors("G") == 1);
    TEST(graph.num_neighbors("X") == 0);

    TEST(graph.nodes() == unordered_set<string>({"A", "B", "C", "D", "E", "F", "G"}));
    TEST(graph.edge_weight("A", "B") == 1);
    TEST(graph.edge_weight("A", "C") == 5);
    TEST(graph.edge_weight("B", "C") == 1);
    TEST(graph.edge_weight("B", "D") == 1);
    TEST(graph.edge_weight("B", "A") == 1);
    TEST(graph.edge_weight("C", "A") == 5);
    TEST(graph.edge_weight("C", "B") == 1);
    TEST(graph.edge_weight("D", "B") == 1);
    TEST(graph.edge_weight("E", "F") == 4);
    TEST(graph.edge_weight("F", "E") == 4);
    TEST(graph.edge_weight("F", "G") == 5);
    TEST(graph.edge_weight("G", "F") == 5);

    TEST(graph.edge_weight("A", "F") == -1);
    TEST(graph.edge_weight("A", "D") == -1);
    TEST(graph.edge_weight("A", "A") == -1);
    TEST(graph.edge_weight("B", "E") == -1);
    TEST(graph.edge_weight("B", "F") == -1);
    TEST(graph.edge_weight("B", "G") == -1);
    TEST(graph.edge_weight("B", "B") == -1);
    TEST(graph.edge_weight("C", "D") == -1);
    TEST(graph.edge_weight("C", "E") == -1);
    TEST(graph.edge_weight("C", "F") == -1);
    TEST(graph.edge_weight("C", "G") == -1);
    TEST(graph.edge_weight("C", "C") == -1);
    TEST(graph.edge_weight("D", "C") == -1);
    TEST(graph.edge_weight("D", "A") == -1);
    TEST(graph.edge_weight("D", "E") == -1);
    TEST(graph.edge_weight("D", "F") == -1);
    TEST(graph.edge_weight("D", "G") == -1);
    TEST(graph.edge_weight("D", "D") == -1);
    TEST(graph.edge_weight("E", "A") == -1);
    TEST(graph.edge_weight("E", "B") == -1);
    TEST(graph.edge_weight("E", "C") == -1);
    TEST(graph.edge_weight("E", "D") == -1);
    TEST(graph.edge_weight("E", "G") == -1);
    TEST(graph.edge_weight("E", "E") == -1);
    TEST(graph.edge_weight("F", "A") == -1);
    TEST(graph.edge_weight("F", "B") == -1);
    TEST(graph.edge_weight("F", "C") == -1);
    TEST(graph.edge_weight("F", "D") == -1);
    TEST(graph.edge_weight("F", "F") == -1);
    TEST(graph.edge_weight("G", "A") == -1);
    TEST(graph.edge_weight("G", "B") == -1);
    TEST(graph.edge_weight("G", "C") == -1);
    TEST(graph.edge_weight("G", "D") == -1);
    TEST(graph.edge_weight("G", "E") == -1);
    TEST(graph.edge_weight("G", "G") == -1);
    TEST(graph.edge_weight("Z", "X") == -1);
    TEST(graph.edge_weight("E", "X") == -1);
    TEST(graph.edge_weight("Z", "G") == -1);
}

