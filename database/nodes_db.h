//
// Created by laozhu on 23-11-22.
//

#ifndef TRANSLATOR_NODES_DB_H
#define TRANSLATOR_NODES_DB_H

#include <string>
#include <vector>

class NodesDatabase {
public:
    struct node_info_t {
        std::string name;
        double width;
        double height;
        bool terminal;
    };

    size_t num_nodes, num_terminals;

    std::vector<node_info_t> &get_nodes() {
        return nodes_;
    }

private:
    std::vector<node_info_t> nodes_;
};

#endif //TRANSLATOR_NODES_DB_H
