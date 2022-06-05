#include "../skip_list/skip_list.h"

using namespace my_skip_list_namespace;

static void cat_file(const std::string& file_path) {
    if (access(file_path.c_str(), F_OK ) != FILE_EXIST) {
        log_error("Catting file is not exist!");
        return;
    }
    std::ifstream ifs;

    ifs.open(file_path, std::ios::in);
    if (!ifs.is_open()) {
        log_error("Open file failed!");
        return;
    }
    std::string line;
    while (std::getline(ifs, line)) {
        std::cout << line << std::endl;
    }
    ifs.close();
}


int main() {
    SkipList<int, std::string> skiplist;

    std::cout << std::endl << "Cat load file:" << std::endl;
    std::string file_path_to_load = "./skip_list_cache.tmp";
    cat_file(file_path_to_load);

    std::cout << "===================  Test load  ===================" << std::endl;
    skiplist.load(file_path_to_load);
    skiplist.graphical_print();
    return 0;
}