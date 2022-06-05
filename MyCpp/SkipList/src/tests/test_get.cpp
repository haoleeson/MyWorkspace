#include "../skip_list/skip_list.h"

using namespace my_skip_list_namespace;

template<typename K, typename V>
static void print_key_value(K key, V* val) {
    if (!val) {
        std::cout << "The key " << key << " does not exist!" << std::endl;
    } else {
        std::cout << "Get the value of " << key << " is : " << *val << std::endl;
    }
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
    std::cout << "Test get value:" << std::endl;
    print_key_value(5, skiplist.get(5));
    print_key_value(7, skiplist.get(7));
    print_key_value(13, skiplist.get(13));
    print_key_value(404, skiplist.get(404));
    return 0;
}