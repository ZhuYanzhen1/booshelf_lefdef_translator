//
// Created by laozhu on 23-11-29.
//

#ifndef TRANSLATOR_DATABASE_NETS_DB_H
#define TRANSLATOR_DATABASE_NETS_DB_H

#include <string>
#include <vector>
#include <iostream>

class NetsDatabase {
public:
    struct pin_t {
        std::string name;
        std::string in_out;
        double pos_x;
        double pos_y;
    };
    struct net_t {
        std::string name;
        size_t pin_num;
        std::vector<pin_t> pins;
    };

    size_t net_num, pin_num;

    std::vector<net_t> &get_nets() {
        return nets_;
    }

    friend std::ostream &operator<<(std::ostream &os, const NetsDatabase &db) {
        os << "Num nets: " << db.net_num << std::endl;
        os << "Num pins: " << db.pin_num << std::endl;
        for (size_t counter = 0; counter < (db.nets_.size() > 10 ? 10 : db.nets_.size()); ++counter) {
            if (db.nets_[counter].pin_num > 10)
                continue;
            os << db.nets_[counter].name << " (" << db.nets_[counter].pin_num << ") {" << std::endl;
            for (size_t pin_counter = 0; pin_counter < db.nets_[counter].pin_num; ++pin_counter) {
                os << "\t" << db.nets_[counter].pins[pin_counter].name << " "
                   << db.nets_[counter].pins[pin_counter].in_out << " ("
                   << db.nets_[counter].pins[pin_counter].pos_x << ", "
                   << db.nets_[counter].pins[pin_counter].pos_y << ")" << std::endl;
            }
            os << "}" << std::endl;
        }
        return os;
    }

private:
    std::vector<net_t> nets_;
};

#endif //TRANSLATOR_DATABASE_NETS_DB_H
