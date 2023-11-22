//
// Created by laozhu on 23-11-22.
//

#ifndef TRANSLATOR_NODES_DB_H
#define TRANSLATOR_NODES_DB_H

#include <string>
#include <vector>
#include <iostream>

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

    friend std::ostream &operator<<(std::ostream &os, const NodesDatabase &db) {
        os << "Num nodes: " << db.num_nodes << std::endl;
        os << "Num terminals: " << db.num_terminals << std::endl;
        for (size_t counter = 0; counter < 10; ++counter) {
            os << db.nodes_[counter].name << " (" << db.nodes_[counter].width << ", " << db.nodes_[counter].height
               << ") " << (db.nodes_[counter].terminal ? "True" : "False") << std::endl;
        }
        return os;
    }

private:
    std::vector<node_info_t> nodes_;
};

#endif //TRANSLATOR_NODES_DB_H
