#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <chrono>
#include <set>

#include "conf_read.h"
#include "boost/locale.hpp"
#include "boost/filesystem.hpp"
#include "boost/locale/boundary.hpp"

inline std::chrono::high_resolution_clock::time_point get_current_time_fenced()
{
    std::atomic_thread_fence(std::memory_order_seq_cst);
    auto res_time = std::chrono::high_resolution_clock::now();
    std::atomic_thread_fence(std::memory_order_seq_cst);
    return res_time;
}

template<class D>
inline long long to_us(const D& d)
{
    return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
}

std::vector<std::string> read_file(std::string file_name){
    std::vector<std::string> read_line;
    std::string line;
    std::ifstream myfile(file_name);
    if (myfile.is_open()){
        while (getline(myfile,line)){
            read_line.emplace_back(line);
        }
    }
    else std::cerr << "Unable to open file"<<std::endl;
    return read_line;
}

std::vector<std::string> split_lowercase(std::vector<std::string> vector_in){
    namespace ba=boost::locale::boundary;
    std::vector<std::string> vector_out;
    for(std::string text:vector_in){
        std::locale loc = boost::locale::generator().generate("en_US.UTF-8");
        text = boost::locale::to_lower(text, loc);
        ba::segment_index<std::string::const_iterator> map(ba::word,text.begin(),text.end(),loc);
        map.rule(ba::word_any);
        for(ba::ssegment_index::iterator it=map.begin(),e=map.end();it!=e;++it) vector_out.push_back(* it);
    }
    return vector_out;
}

std::map<std::string, int> words_count (std::vector<std::string> vector_in){
    std::map<std::string, int> map_count;

    for (auto& el:vector_in){
        std::map<std::string, int>::iterator it;
        it = map_count.find(el);
        if (it == map_count.end()) {
            int count = int(std::count(vector_in.begin(), vector_in.end(), el));
            map_count.insert(std::pair<std::string, int>(el, count));
        }
    }
    return map_count;
}

void sort_by_alp(std::map<std::string, int> map_in, std::string filename){
    std::ofstream myfile;
    myfile.open(filename);
    for (auto const& pair: map_in) {
        myfile << pair.first << " " << pair.second << "\n";
    }
    myfile.close();
}

void sort_by_num(std::map<std::string, int> mapOfWordCount, std::string filename){
    typedef std::function <bool(std::pair<std::string, int>,
                                std::pair<std::string, int>)> Comparator;

    Comparator compFunctor = [](std::pair<std::string, int> elem1 ,std::pair<std::string, int> elem2)
            {
                return elem1.second < elem2.second;
            };

    std::set<std::pair<std::string, int>, Comparator> setOfWords(
            mapOfWordCount.begin(), mapOfWordCount.end(), compFunctor);

    std::ofstream myfile;
    myfile.open(filename);
    for (std::pair<std::string, int> element : setOfWords) myfile << element.first << " " << element.second << "\n";
    myfile.close();

}

int main(int argc, char* argv[]){
    configuration_t *conf;

    if (argc==2){
        conf = configuration(argv[1]);
    }
    else if (argc==1){
        conf = configuration("config.dat");
    }
    else{
        std::cerr<<"Wrong input"<<std::endl;
    }
    if (conf->threads_num=="1"){
        auto total = get_current_time_fenced();
        auto load = get_current_time_fenced();
        std::vector<std::string> res_vector = read_file("data.txt");
        std::cout<<"Loading: "<<to_us(get_current_time_fenced()-load)<<std::endl;
        auto analyzing = get_current_time_fenced();
        res_vector = split_lowercase(res_vector);
        std::map<std::string, int> res_map = words_count(res_vector);
        sort_by_alp(res_map, conf->file_out_alp);
        sort_by_num(res_map, conf->file_out_num);
        std::cout<<"Analyzing: "<<to_us(get_current_time_fenced()-analyzing)<<std::endl;
        std::cout<<"Total: "<<to_us(get_current_time_fenced()-total)<<std::endl;
    }
    return 0;
}