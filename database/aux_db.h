//
// Created by laozhu on 23-11-22.
//

#ifndef TRANSLATOR_DATABASE_AUX_DB_H
#define TRANSLATOR_DATABASE_AUX_DB_H

#include <string>
#include <iostream>

class AuxDatabase {
public:
    std::string nodes_filename;
    std::string nets_filename;
    std::string pl_filename;
    std::string scl_filename;
    std::string wts_filename;

    friend std::ostream &operator<<(std::ostream &os, const AuxDatabase &db) {
        os << "Nodes file: " << db.nodes_filename << std::endl;
        os << "Nets file: " << db.nets_filename << std::endl;
        os << "Pl file: " << db.pl_filename << std::endl;
        os << "Scl file: " << db.scl_filename << std::endl;
        os << "Wts file: " << db.wts_filename << std::endl;
        return os;
    }
};

#endif //TRANSLATOR_DATABASE_AUX_DB_H
