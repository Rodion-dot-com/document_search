#ifndef COURSEWORK_DATABASE_H
#define COURSEWORK_DATABASE_H

#include <vector>

class database
{
public:
    static void format(std::string &token);
    int add(const std::string &path_to_txt);
    std::vector<std::string> search(const std::string &required_info, const size_t count_after);
    std::vector<std::string> levenshtein_search(const std::string &required_info, const size_t count_after);
    static int edit_dist(const std::string &s, const std::string &t);

private:
    std::vector<std::string>merged_text;
};

#endif
