#ifndef ICCAD_PROJECT_DATABASE_PL_DB_H_
#define ICCAD_PROJECT_DATABASE_PL_DB_H_

#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>

class PlDatabase {
public:
    struct CellInfo {
        int loc_xy[2];
        std::string orientation;
        int fixed;
    };

    std::unordered_map<std::string, CellInfo> &get_map_info() {
        return dream_pl_map_;
    }

private:
    std::unordered_map<std::string, CellInfo> dream_pl_map_{};
};

#endif// ICCAD_PROJECT_DATABASE_PL_DB_H_
