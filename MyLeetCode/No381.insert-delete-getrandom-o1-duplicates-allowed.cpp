/**
 * No381. O(1) 时间插入、删除和获取随机元素 - 允许重复
 * 设计一个支持在平均时间复杂度O(1)下，执行以下操作的数据结构。

注意: 允许出现重复元素。

insert(val)：向集合中插入元素 val。
remove(val)：当 val 存在时，从集合中移除一个 val。
getRandom：从现有集合中随机获取一个元素。每个元素被返回的概率应该与其在集合中的数量呈线性相关。
示例:

// 初始化一个空的集合。
RandomizedCollection collection = new RandomizedCollection();

// 向集合中插入 1 。返回 true 表示集合不包含 1 。
collection.insert(1);

// 向集合中插入另一个 1 。返回 false 表示集合包含 1 。集合现在包含 [1,1] 。
collection.insert(1);

// 向集合中插入 2 ，返回 true 。集合现在包含 [1,1,2] 。
collection.insert(2);

// getRandom 应当有 2/3 的概率返回 1 ，1/3 的概率返回 2 。
collection.getRandom();

// 从集合中删除 1 ，返回 true 。集合现在包含 [1,2] 。
collection.remove(1);

// getRandom 应有相同概率返回 1 和 2 。
collection.getRandom();

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/insert-delete-getrandom-o1-duplicates-allowed
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class RandomizedCollection {
public:
    /** Initialize your data structure here. */
    RandomizedCollection();

    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val);

    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val);

    /** Get a random element from the collection. */
    int getRandom();
private:
    unordered_map<int, unordered_set<int>> mapVal2IndexSet;// 储存val，及可能多个val对应的下标集合
    unordered_map<int, unordered_set<int>>::iterator it;// 迭代器
    vector<int> nums;// 存放val集合的容器
    int size;// 容器大小
};

RandomizedCollection::RandomizedCollection() {
    size = 0;
}

bool RandomizedCollection::insert(int val) {
    nums.push_back(val);
    it = mapVal2IndexSet.find(val);
    if (it == mapVal2IndexSet.end()) {
        mapVal2IndexSet[val].insert(size++);
        return true;
    } else {
        // 重复插入：返回false
        it->second.insert(size++);
        return false;
    }
}

bool RandomizedCollection::remove(int val) {
    it = mapVal2IndexSet.find(val);
    // 不存在，返回false
    if (it == mapVal2IndexSet.end()) {
        return false;
    }
    int firstIndex = *(it->second.begin());
    // 删除首次出现的下标记录(只有一个则直接删除该<val, value>对)
    if (it->second.size() > 1) {
        it->second.erase(firstIndex);
    } else {
        mapVal2IndexSet.erase(val);
    }
    // 则将容器尾部数 --> 覆盖到 第一次出现的数（排除特殊情况：首次出现的数在容器尾部）
    if (firstIndex < --size) {
        // 用容器最后一个数覆盖之
        nums[firstIndex] = nums[size];
        // 更新容器最后一个数的下标(挪位后)
        it = mapVal2IndexSet.find(nums[size]);
        it->second.erase(size);
        it->second.insert(firstIndex);
    }
    // 删除容器最后一个数
    nums.pop_back();
    return true;
}

int RandomizedCollection::getRandom() {
    return size <= 0 ? 0 : nums[rand() % size];
}


int main() {
    RandomizedCollection* obj = new RandomizedCollection();
    int val[] = {1, 1, 2, 4, 5};
    cout << "Insert:" << endl;
    for (int i = 0; i < 5; ++i) {
        cout << obj->insert(val[i]) << endl;
    }
    cout << "getRandom:" << endl;
    for (int i = 0; i < 5; ++i) {
        cout << obj->getRandom() << endl;
    }
    cout << "remove:" << endl;
    for (int i = 0; i < 5; ++i) {
        cout << obj->remove(val[i]) << endl;
    }
    return 0;
}
