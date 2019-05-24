#include "conf_read.h"

#include <iostream>

configuration_t *configuration(const std::string &filename) {
    std::ifstream input(filename);
    std::string line;
    auto *conf_attr = new configuration_t;
    std::map<std::string, std::string *> conf_map{{"file_in",   &conf_attr->file_in},
                                                         {"file_out_alp", &conf_attr->file_out_alp},
                                                         {"file_out_num", &conf_attr->file_out_num},
                                                         {"threads_num",  &conf_attr->threads_num}};

    while (getline(input, line)) {
        line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

        size_t half = line.find(':');
        std::string name = line.substr(0, half);
        std::string value = line.substr(half + 1);
        *conf_map[name] = value;
    }
    input.close();
    return conf_attr;
}
