#include "../skip_list/skip_list.h"

using namespace my_skip_list_namespace;

int main() {
    SkipList<int, std::string> skiplist;
    skiplist.insert(3, "Three");
    skiplist.graphical_print();
    skiplist.insert(5, "Five");
    skiplist.graphical_print();
    skiplist.insert(39, "Thirty-nine");
    skiplist.graphical_print();
    skiplist.insert(13, "Thirteen");
    skiplist.graphical_print();
    skiplist.insert(17, "Seventeen");
    skiplist.graphical_print();
    skiplist.insert(58, "Fifty-eight");
    skiplist.graphical_print();
    skiplist.insert(25, "Twenty-five");
    skiplist.graphical_print();
    return 0;
}