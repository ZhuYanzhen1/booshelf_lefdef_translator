//
// Created by laozhu on 23-11-22.
//

#include "cmd_line.h"
#include "../version.h"

#include <filesystem>
#include <fstream>

static const std::string version_string = "Translator " GIT_COMMIT_HASH "\nSoftware Version " SOFTWARE_VERSION
                                          "\n" GCC_VERSION_MAJOR "\nBuilt in " FIRMWARE_BUILD_TIME;

CMDLine::CMDLine(int argc, char **argv) {
    cmd_line_ = new TCLAP::CmdLine("This software is used for translate bookshelf to lef/def.", ' ', version_string);

    /* Define value arguments and add it to the command line */
    bookshelf_path_arg_ =
            new TCLAP::ValueArg<std::string>("b", "bookshelf", "Bookshelf folder of translator", true, "",
                                             "string");
    out_path_arg_ =
            new TCLAP::ValueArg<std::string>("o", "out", "output folder of translator", true, "",
                                             "string");

    cmd_line_->add(bookshelf_path_arg_);
    cmd_line_->add(out_path_arg_);

    /* Parse the argv array */
    cmd_line_->parse(argc, argv);

    bookshelf.set_arg(bookshelf_path_arg_);
    output.set_arg(out_path_arg_);
}

void CMDLine::legality_check() {
    delete_files_in_folder_(out_path_arg_->getValue());
    std::filesystem::create_directory(out_path_arg_->getValue());
    output.file_available = true;
    bookshelf.file_available = check_folder_(bookshelf_path_arg_->getValue());
    if (bookshelf.file_available) {
        std::string aux_file_local;
        for (const auto &entry: std::filesystem::directory_iterator(bookshelf.str())) {
            if (entry.is_regular_file()) {
                if (entry.path().filename().string().find(".aux") != std::string::npos)
                    aux_file_local = entry.path().filename().string();
            }
        }
        if (!check_filename_(bookshelf.str() + "/" + aux_file_local, ".aux")) {
            bookshelf.file_available = false;
            return;
        } else {
            std::vector<std::string> suffixes = {".nodes", ".nets", ".wts", ".pl", ".scl"};

            std::ifstream file(bookshelf.str() + "/" + aux_file_local);
            std::string line;
            std::getline(file, line);
            std::stringstream ss(line);
            std::string item;
            std::vector<std::string> tokens;
            while (ss >> item)
                tokens.push_back(item);
            bool all_files_available = true;
            for (const std::string &token: tokens) {
                for (const std::string &suffix: suffixes)
                    if (token.find(suffix) != std::string::npos)
                        if (!check_filename_(bookshelf.str() + "/" + token, suffix))
                            all_files_available = false;
            }
            if (!all_files_available) {
                bookshelf.file_available = false;
                return;
            }
            aux_file = bookshelf.str() + "/" + aux_file_local;
        }
    }
}

bool CMDLine::check_filename_(const std::string &filename, const std::string &suffix) {
    if (filename.empty())
        return false;
    if (!(filename.size() >= suffix.length() && filename.substr(filename.size() - suffix.length()) == suffix))
        std::cout << "\033[1;33m[Warn]: file " << filename << "suffix is not \"" << suffix << "\"\033[0m" << std::endl;
    std::ifstream file(filename);
    if (file.is_open())
        file.close();
    else {
        std::cout << "\033[1;31m[Error]: Cannot open file " << filename
                  << " Please check if the file exists or if the program has been granted read permission\033[0m"
                  << std::endl;
        return false;
    }
    return true;
}

bool CMDLine::check_folder_(const std::string &folderPath) {
    if (folderPath.empty())
        return false;
    if (std::filesystem::exists(folderPath) && std::filesystem::is_directory(folderPath)) {
        int fileCount = 0;
        for (const auto &entry: std::filesystem::directory_iterator(folderPath)) {
            if (std::filesystem::is_regular_file(entry))
                fileCount++;
        }
        if (fileCount > 1)
            return true;
        else {
            std::cout << "\033[1;31m[Error]: Folder " << folderPath << " doesn't have any file in it\033[0m"
                      << std::endl;
            return false;
        }
    } else {
        std::cout << "\033[1;31m[Error]: Folder " << folderPath << " doesn't exists\033[0m" << std::endl;
        return false;
    }
}

void CMDLine::delete_files_in_folder_(const std::string &folderPath) {
    if (std::filesystem::exists(folderPath) && std::filesystem::is_directory(folderPath)) {
        for (const auto &entry: std::filesystem::directory_iterator(folderPath)) {
            if (std::filesystem::is_regular_file(entry))
                std::filesystem::remove(entry.path());
            else if (std::filesystem::is_directory(entry))
                delete_files_in_folder_(entry.path().string());
        }
    }
}
