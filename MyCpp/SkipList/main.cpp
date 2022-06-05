#include "src/skip_list/skip_list.h"
#include "src/log/vlog.h"

using namespace my_skip_list_namespace;

void test_insert() {
    log_info("Test insert start.\n");
    SkipList<int, std::string> skiplist;
    skiplist.insert(3, "Three");
    skiplist.insert(5, "Five");
    skiplist.insert(13, "Thirteen");
    skiplist.insert(17, "Seventeen");
    skiplist.insert(39, "Thirty-nine");
    skiplist.insert(58, "Fifty-eight");
    return;
}

void test_graphical_print() {
    log_info("Test graphical print start.\n");
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
    return;
}

int main() {
//    test_insert();
    test_graphical_print();

    return 0;
}