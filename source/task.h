#ifndef COURSEWORK_TASK_H
#define COURSEWORK_TASK_H

#include <iostream>
#include "database.h"
#include "detail.h"

void dialog_box(database& base) {
    switch (detail::second_page()) {
        case detail::second_page_change::ADD :
            base.add(detail::get_path_to_converted());
            dialog_box(base);
            break;
        case detail::second_page_change::SEARCH : {
            auto vec = base.levenshtein_search(detail::get_required_info(), 128);
            for (auto str: vec) {
                std::cout << "-----------------------------------------------------------\n"
                          << str;
            }
        }
            dialog_box(base);
            break;
        case detail::second_page_change::COMPLETE_MATCH : {
            auto vec = base.search(detail::get_required_info(), 128);
            for (auto str: vec) {
                std::cout << "----------------------------------------------------------\n"
                          << str << std::endl;
            }
        }
            dialog_box(base);
            break;
        case detail::second_page_change::EXIT :
            return;
        default:
            throw std::runtime_error("Error in dialog box!\n");
    }
}

void task() {
    if (detail::start_page() != 1) {
        return;
    }
    database base;
    base.add(detail::get_path_to_converted());
    dialog_box(base);
}

#endif