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

    friend std::ostream &operator<<(std::ostream &os, const PlDatabase &db) {
        size_t counter = 0;
        for (const auto &cell: db.dream_pl_map_) {
            counter++;
            os << cell.first << " (" << cell.second.loc_xy[0] << ", " << cell.second.loc_xy[1] << ") "
               << cell.second.orientation << " " << cell.second.fixed << std::endl;
            if (counter == 10)
                break;
        }
        return os;
    }

private:
    std::unordered_map<std::string, CellInfo> dream_pl_map_{};
};

#endif// ICCAD_PROJECT_DATABASE_PL_DB_H_
