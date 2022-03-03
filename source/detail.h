#ifndef COURSEWORK_DETAIL_H
#define COURSEWORK_DETAIL_H

#include <string>
#include <cstdlib>
#include <iostream>

namespace detail {
    const std::string PATH_TO_PROJECT = "/home/rodion/CLionProjects/coursework";
    const std::string PATH_TO_SCRIPT = PATH_TO_PROJECT + "/script.py";

    int pdf_to_txt(const std::string &pdf_path, const std::string &out_path = (PATH_TO_PROJECT + "/temp.txt")) {
        std::string command = "python3 " + PATH_TO_SCRIPT + " " + pdf_path + " " + out_path;
        try {
            system(command.c_str());
        }
        catch (...) {
            return 1;
        }
        return 0;
    }

    int start_page() {
        std::cout << "Enter a key to continue\n"
                     "1. Open file\n"
                     "2. Exit\n";
        int temp;
        std::cin >> temp;
        if (temp < 1 || temp > 2) {
            std::cout << "Incorrect input. Please try again.\n";
            temp = start_page();
        }
        return temp;
    }

    std::string get_path() {
        std::cout << "Enter the path to the file\n";
        std::string path;
        std::cin >> path;
        if(path.size() < 4 ){
            throw std::invalid_argument("Invalid path!\n");
        }
        if (path.substr(path.size() - 4) != ".pdf") {
            throw std::invalid_argument("Invalid path!\n");
        }
        return path;
    }

    std::string get_path_to_converted() {
        if (detail::pdf_to_txt(detail::get_path())) {
            throw std::runtime_error("Error with convert file!\n");
        }
        return PATH_TO_PROJECT + "/temp.txt";
    }

    int second_page() {
        std::cout << "1. Add another file\n"
                     "2. Search\n"
                     "3. Find a complete match\n"
                     "4. Exit\n";
        int temp;
        std::cin >> temp;
        if (temp < 1 || temp > 4) {
            std::cout << "Incorrect input. Please try again.\n";
            temp = second_page();
        }
        return temp;
    }

    enum second_page_change {
        ADD = 1,
        SEARCH = 2,
        COMPLETE_MATCH = 3,
        EXIT = 4
    };

    std::string get_required_info() {
        std::cout << "Enter the required information\n";
        std::string res = "";
        std::cin >> res;
        std::string temp;
        getline(std::cin, temp);
        res.append(temp);
        return res;
    }
}

#endif