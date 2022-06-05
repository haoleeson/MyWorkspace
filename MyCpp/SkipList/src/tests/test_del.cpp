#include "../skip_list/skip_list.h"

using namespace my_skip_list_namespace;

int main() {
    SkipList<int, std::string> skiplist;
    skiplist.insert(3, "Three");
    skiplist.graphical_print();
    skiplist.insert(5, "Five", 2);
    skiplist.graphical_print();
    skiplist.insert(39, "Thirty-nine");
    skiplist.graphical_print();
    skiplist.insert(13, "Thirteen", 1);
    skiplist.graphical_print();
    skiplist.insert(17, "Seventeen");
    skiplist.graphical_print();
    skiplist.insert(58, "Fifty-eight");
    skiplist.graphical_print();
    skiplist.insert(25, "Twenty-five");
    skiplist.graphical_print();

    skiplist.del(39);
    skiplist.graphical_print();
    skiplist.del(58);
    skiplist.graphical_print();
    skiplist.del(17);
    skiplist.graphical_print();
    skiplist.del(3);
    skiplist.graphical_print();
    skiplist.del(25);
    skiplist.graphical_print();
    skiplist.del(5);
    skiplist.graphical_print();
    skiplist.del(13);
    skiplist.graphical_print();
    return 0;
}