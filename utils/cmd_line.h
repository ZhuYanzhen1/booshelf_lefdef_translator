//
// Created by laozhu on 23-11-22.
//

#ifndef TRANSLATOR_UTILS_CMD_LINE_H
#define TRANSLATOR_UTILS_CMD_LINE_H

#include "CmdLine.h"

class CMDLine {
public:
    class CMDArg {
    public:
        bool file_available{};

        void set_arg(TCLAP::ValueArg<std::string> *arg) { arg_ = arg; }

        bool available() { return (arg_->isSet() && file_available); }

        std::string str() { return (arg_->isSet() && file_available) ? arg_->getValue() : ""; }

    private:
        TCLAP::ValueArg<std::string> *arg_{};
    };

    CMDLine(int argc, char **argv);

    void legality_check();

    CMDArg bookshelf, output;
    std::string aux_file;

private:
    TCLAP::CmdLine *cmd_line_;
    TCLAP::ValueArg<std::string> *bookshelf_path_arg_{}, *out_path_arg_{};

    static bool check_filename_(const std::string &filename, const std::string &suffix);

    static bool check_folder_(const std::string &folderPath);

    static void delete_files_in_folder_(const std::string &folderPath);
};

#endif //TRANSLATOR_UTILS_CMD_LINE_H
