#include <fstream>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <vector>
#include "database.h"

void database::format(std::string &token) {
    for (auto &ch: token) {
        if (isalpha(ch)) {
            ch = char(tolower(ch));
        }
    }
}

int database::add(const std::string &path_to_txt) {
    std::ifstream in(path_to_txt);
    if (in.fail()) {
        throw std::invalid_argument("Invalid path to file!\n");
    }
    std::string temp;
    std::string res;
    while (!in.eof() && in.good()) {
        getline(in, temp);
        format(temp);
        temp += '\n';
        res.append(temp);
    }
    merged_text.push_back(res);
    return 0;
}

std::vector<std::string> database::search(const std::string &required_info, const size_t count_after) {
    std::string correct_req = required_info;
    format(correct_req);
    std::vector<std::string> res;
    size_t it = 0;
    const size_t size = required_info.size() + count_after;
    for (const auto& str: merged_text) {
        while (it <= str.size()) {
            it = str.find(correct_req, ++it);
            if (it > str.size())
                break;
            res.push_back(str.substr(it, size) + "...");
        }
    }
    return res;
}

std::vector<std::string> database::levenshtein_search(const std::string &required_info, const size_t count_after) {
    std::vector<std::pair<double, std::string>> res;
    std::string correct_req = required_info;
    format(correct_req);
    const size_t size = required_info.size() + count_after;
    const size_t req_size = required_info.size();
    for (auto &str: merged_text) {
        for (size_t it = 0; it < str.size() - req_size; ++it) {
            double uncoincidence = double(edit_dist(str.substr(it, req_size), correct_req))
                    / double(req_size);
            if (uncoincidence < 0.334) {
                res.push_back(std::make_pair(uncoincidence, (str.substr(it, size) + "...\n")));
                it += req_size;
            }
        }
        std::sort(res.begin(), res.end());
    }
    std::vector<std::string> ans;
    ans.resize(res.size());
    for (int i = 0; i < res.size(); ++i) {
        ans[i] = res[i].second;
    }
    return ans;
}

int database::edit_dist(const std::string &s, const std::string &t) {
    if (s.empty())
        return int(t.length());
    else if (t.empty())
        return int(s.length());
    size_t len_s = s.length();
    size_t len_t = t.length();
    std::vector<int> arr1(len_s + 1, 0);
    std::vector<int> arr2(len_s + 1, 0);
    for (int i = 1; i <= len_s; ++i) {
        arr1[i] = i;
    }
    std::vector<int> *p1 = &arr1;
    std::vector<int> *p2 = &arr2;
    for (int j = 1; j <= len_t; ++j) {
        (*p2)[0] = (*p1)[0] + 1;
        for (int i = 1; i <= len_s; ++i) {
            int cost_up = (*p2)[i - 1] + 1;
            int cost_left = (*p1)[i] + 1;
            int cost_diag = (*p1)[i - 1];
            if (s[i - 1] != t[j - 1])
                cost_diag += 1;
            int cost = std::min(cost_up, std::min(cost_left, cost_diag));
            (*p2)[i] = cost;
        }
        std::swap(p1, p2);
    }
    return (*p1)[len_s];
}
