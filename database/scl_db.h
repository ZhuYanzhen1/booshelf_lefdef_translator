#ifndef MBIST_CLUSTER_DATABASE_SCL_DB_H
#define MBIST_CLUSTER_DATABASE_SCL_DB_H

#include <iostream>
#include <string>
#include <vector>

class SclDatabase {
public:
    struct superset_t {
        int coordinate;
        int height;
        int sitewidth;
        int sitespacing;
        char siteorient;
        char sitesymmetry;
        int subroworigin;
        int numsites;
    };
    struct superset_all_t {
        int num_rows;
        std::vector<superset_t> scl_instance;
    };

    superset_all_t &get_value() { return scl_instances_; }

    friend std::ostream &operator<<(std::ostream &os, const SclDatabase &scl) {
        int counter = 1;
        os << "numrow:" << scl.scl_instances_.num_rows << std::endl;
        os << std::endl;
        for (const superset_t counter_scl: scl.scl_instances_.scl_instance) {
            counter++;
            os << std::endl;
            os << "coordinate: " << counter_scl.coordinate << std::endl;
            os << "height: " << counter_scl.height << std::endl;
            os << "sitewidth: " << counter_scl.sitewidth << std::endl;
            os << "sitespacing: " << counter_scl.sitespacing << std::endl;
            os << "siteorient: " << counter_scl.siteorient << std::endl;
            os << "sitesymmetry: " << counter_scl.sitesymmetry << std::endl;
            os << "subroworigin: " << counter_scl.subroworigin << std::endl;
            os << "numsities: " << counter_scl.numsites << std::endl;
        }

        return os;
    }

private:
    superset_all_t scl_instances_;
};

#endif
