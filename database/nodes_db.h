//
// Created by laozhu on 23-11-22.
//

#ifndef TRANSLATOR_DATABASE_NODES_DB_H
#define TRANSLATOR_DATABASE_NODES_DB_H

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

    size_t nodes_num, terminals_num;

    std::vector<node_info_t> &get_nodes() {
        return nodes_;
    }

    friend std::ostream &operator<<(std::ostream &os, const NodesDatabase &db) {
        os << "Num nodes: " << db.nodes_num << std::endl;
        os << "Num terminals: " << db.terminals_num << std::endl;
        for (size_t counter = 0; counter < 10; ++counter) {
            os << db.nodes_[counter].name << " (" << db.nodes_[counter].width << ", " << db.nodes_[counter].height
               << ") " << (db.nodes_[counter].terminal ? "True" : "False") << std::endl;
        }
        return os;
    }

private:
    std::vector<node_info_t> nodes_;
};

#endif // TRANSLATOR_DATABASE_NODES_DB_H
