//
// Created by Анастасия Траверсе on 5/24/19.
//


#ifndef LAB_WORDS_CONF_READ_H
#define LAB_WORDS_CONF_READ_H

#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

struct configuration_t{
    std::string file_in;
    std::string file_out_alp;
    std::string file_out_num;
    std::string threads_num;
};

configuration_t *configuration(const std::string &filename);

#endif //LAB_WORDS_CONF_READ_H
