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
    skiplist.insert(3, "Three");
    skiplist.insert(5, "Five");
    skiplist.insert(39, "Thirty-nine");
    skiplist.insert(13, "Thirteen");
    skiplist.insert(17, "Seventeen");
    skiplist.insert(58, "Fifty-eight");
    skiplist.insert(25, "Twenty-five");
    skiplist.graphical_print();

    std::string file_path_to_dump = "./skip_list_cache.tmp";

    std::cout << "===================  Test dump  ===================" << std::endl;
    skiplist.dump(file_path_to_dump);

    std::cout << std::endl << "Cat dump file:" << std::endl;
    cat_file(file_path_to_dump);
    return 0;
}