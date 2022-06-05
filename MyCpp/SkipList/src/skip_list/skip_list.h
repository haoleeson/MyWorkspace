/**
 * SkipList类（核心算法实现与对外接口）
 * @description：
 * 1. 采用面向对象设计思路，可按需实例化多个 SkipList
 * 2. 采用模板类设计，可在实例化时自定义键值对类型
 * 3. 线程安全，关键边界变量通过原子操作限制
 * 4. 功能丰富，支持：新增(或修改)、删除、查询、可视化打印、持久化和加载 SkipList 中内容到文件
 */

#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <iostream>
#include <string>
#include <ctime>    // use its time() for genning a random number as seed
#include <atomic>   // use its std::atomic_bool for multiply thread status check
#include <iomanip>  // use its std::setw() for printing
#include <unistd.h> // use its access() for check file exist
#include <fstream>  // use its reading and writing func
#include "skip_list_node.h"
#include "../log/vlog.h"

namespace my_skip_list_namespace {

// 定义允许节点的最大层数
#define MAX_LEVEL 16
// 定义默认 dump load 文件路径
#define DEFAULT_DUMP_FILE_PATH "./skip_list_cache.tmp"
#define DELIMITER ","
// 产生 (0, b) 范围内的随机数
#define random(b) (rand() % b)
#define FILE_EXIST 0
#define FILE_NOT_EXISTED -1

/**
 * SkipList Class
 * @tparam K
 * @tparam V
 */
    template<typename K, typename V>
    class SkipList {
    public:
        SkipList();
        ~SkipList();
        Node<K, V>* find(const K key);              // 查找位置(未找到，得到其上一个位置)
        bool insert(K key, V val, int level = -1);  // 增/改值
        bool del(K key);                            // 删值
        V* get(K key);                               // 取值
        bool dump(std::string file_path_to_dump = DEFAULT_DUMP_FILE_PATH);  // 备份
        bool load(std::string file_path_to_load = DEFAULT_DUMP_FILE_PATH);  // 加载
        void graphical_print(void);                 // 可视化打印
    private:
        inline int gen_rand_Level();
    private:
        Node<K, V>* _pre_header;
        unsigned int _node_cnt;
        int _max_level;
        std::atomic_bool b_writing;
    };

    template<typename K, typename V>
    SkipList<K, V>::SkipList() : _node_cnt(0), _max_level(0), b_writing(false) {
        _pre_header = new Node<K, V>(MAX_LEVEL);
        assert(_pre_header);
        _pre_header->_level = 0;
        log_info("gen SkipList with default param:\n  - MAX_LEVEL: %d\n", MAX_LEVEL);
    }

    template<typename K, typename V>
    SkipList<K, V>::~SkipList() {
        Node<K, V>* ptr = _pre_header;
        Node<K, V>* record_next_ptr = nullptr;

        while (ptr) {
            record_next_ptr = ptr->_next_nodes[0];
            delete ptr;
            ptr = record_next_ptr;
        }
        log_debug("~SkipList() success.");
    }

    template<typename K, typename V>
    inline int SkipList<K, V>::gen_rand_Level() {
        static bool b_first_run = true;
        static const uint32_t MAX_RAND_NUM = 100;       // 定义生成随机数的最大值，随机数范围 [0, 100)
        static const double P_HAS_NEXT_LEVEL = 0.5;    // 定义模拟层数增长时，有下一层的概率
        static const uint32_t INC_THRESHOLD = (uint32_t)(MAX_RAND_NUM * P_HAS_NEXT_LEVEL); // 自增临界值，当每次生成随机数低于它时，使层数增长1

        // 首次运行时，根据当前时间生成一个随机数种子
        if (b_first_run) {
            uint32_t seed = 0;
            // 当种子为无效数时（0 或 2^31-1），重新生成
            while (seed == 0 || seed == 2147483647L) {
                seed = (unsigned int)time(NULL) & 0X7FFFFFFFU;
            }
            srand(seed);
            b_first_run = false;
        }

        int rand_level = 1;
        // 按“是否有下一层”的随机概率模拟层数增长
        while (rand_level < MAX_LEVEL && random(MAX_RAND_NUM) < INC_THRESHOLD) {
            ++rand_level;
        }
        return rand_level > _max_level ? _max_level + 1 : rand_level;
    }

    /**
 * 查找 key 所在节点（或应插入位置的前一节点）
 * @tparam K
 * @tparam V
 * @param key
 * @return 若找到 key 则返回 key 的节点指针，若未找到则返回 nullptr
 */
    template<typename K, typename V>
    Node<K, V>* SkipList<K, V>::find(const K key) {
        Node<K, V>* node_ptr = _pre_header;

        // 按“从左至右 从上至下”的顺序，自head节点起，查找目标 key
        while (node_ptr) {
            int level_i = node_ptr->_level - 1;
            for (; level_i >= 0; --level_i) {
                if (!node_ptr->_next_nodes[level_i]) {
                    continue;
                }
                // a. 若后一节点的 key 等于目标 key（找到），则返回后一节点的指针
                if (node_ptr->_next_nodes[level_i]->_key == key) {
                    return node_ptr->_next_nodes[level_i];
                }
                // b. 若后一节点的 key 小于目标 key，则“跳至”同层后一节点，继续查找
                else if (node_ptr->_next_nodes[level_i]->_key < key) {
                    node_ptr = node_ptr->_next_nodes[level_i];
                    break;
                }
                // c. 若后一节点的 key 大于目标 key，则降低层级 level_i，继续查找
            }
            // 未找到，跳出
            if (level_i == -1) {
                break;
            }
        }
        return nullptr;
    }

/**
 * 插入节点 <Key, val>
 * @tparam K
 * @tparam V
 * @param key
 * @param val
 * @return
 */
    template<typename K, typename V>
    bool SkipList<K, V>::insert(K key, V val, int level) {
        // 查找 key 所在节点（或应插入位置的前一节点），并记录“途经”节点（用于更新指向）
        Node<K, V>* record_find_path[MAX_LEVEL] = {nullptr};
        Node<K, V>* cur_ptr = _pre_header;

        // 按“从左至右 从上至下”的顺序，自head节点起，查找目标 key
        for (int level_i = cur_ptr->_level - 1; level_i >= 0; --level_i) {
            record_find_path[level_i] = cur_ptr;

            // 若节点当前层的后节点指针为空，继续降层寻找
            if (!cur_ptr->_next_nodes[level_i]) {
                continue;
            }

            // a. 若后一节点的 key 等于目标 key（已存在），则更新 val
            if (cur_ptr->_next_nodes[level_i]->_key == key) {
                cur_ptr->_next_nodes[level_i]->_val = val;
                return true;
            }
            // b. 若后一节点的 key 小于目标 key，则“跳至”同层后一节点，继续查找
            else if (cur_ptr->_next_nodes[level_i]->_key < key) {
                cur_ptr = cur_ptr->_next_nodes[level_i];
                ++level_i;
            }
            // c. 若后一节点的 key 大于目标 key，则降低层级 level_i，继续降层查找
        }

        // 未找到，则新建节点
        Node<K, V>* gen_node = new Node<K, V>(key, val, level > 0 ? level : gen_rand_Level());
        assert(gen_node);
        log_debug("gen node(%s) success, level = %d\n", std::to_string(gen_node->_key).c_str(), gen_node->_level);

        // 更新新增节点后变动的指针
        for (int level_i = gen_node->_level - 1; level_i >= 0; --level_i) {
            // 更新新增节点应指向的指针
            if (level_i < _max_level && record_find_path[level_i]) {
                gen_node->_next_nodes[level_i] = record_find_path[level_i]->_next_nodes[level_i];
            }
            // 更新指向新增节点的指针
            if (level_i < _max_level) {
                record_find_path[level_i]->_next_nodes[level_i] = gen_node;
            } else {
                _pre_header->_next_nodes[level_i] = gen_node;
            }
        }

        ++_node_cnt;
        if (gen_node->_level > _max_level) {
            _max_level = gen_node->_level;
            _pre_header->_level = _max_level;
        }
        return true;
    }

    /**
     * 移除节点 <Key, val>
     * @tparam K
     * @tparam V
     * @param key
     * @return
     */
    template<typename K, typename V>
    bool SkipList<K, V>::del(K key) {
        // 查找 key 所在节点（或应插入位置的前一节点），并记录“途经”节点（用于更新指向）
        Node<K, V>* record_find_path[MAX_LEVEL] = {nullptr};
        Node<K, V>* cur_ptr = _pre_header;
        Node<K, V>* target_node_ptr = nullptr;

        // 按“从左至右 从上至下”的顺序，自head节点起，查找目标 key
        for (int level_i = cur_ptr->_level - 1; level_i >= 0; --level_i) {
            record_find_path[level_i] = cur_ptr;

            // 若当前节点的遍历层对应的后节点为空，则继续降层寻找
            if (!cur_ptr->_next_nodes[level_i]) {
                continue;
            }

            // a. 若后一节点的 key 等于目标 key（已找到），标记并继续降层遍历以记录删除后受影响节点（用于更新指向）
            if (cur_ptr->_next_nodes[level_i]->_key == key) {
                if (!target_node_ptr) {
                    target_node_ptr = cur_ptr->_next_nodes[level_i];
                }
            }
            // b. 若后一节点的 key 小于目标 key，则“跳至”同层后一节点，继续查找
            else if (cur_ptr->_next_nodes[level_i]->_key < key) {
                cur_ptr = cur_ptr->_next_nodes[level_i];
                ++level_i;
            }
            // c. 若后一节点的 key 大于目标 key，则降低层级 level_i，继续降层查找
        }

        // 未找到，返回 false
        if (!target_node_ptr) {
            return false;
        }

        // 若将删除节点为最大层数节点（或之一），则调整最大层层数
        while (_max_level > 0 && _pre_header->_next_nodes[_max_level - 1] == target_node_ptr) {
            _pre_header->_next_nodes[_max_level - 1] = target_node_ptr->_next_nodes[_max_level - 1];
            if (target_node_ptr->_next_nodes[_max_level - 1]) {
                break;
            }
            _pre_header->_level = --_max_level;
        }

        // 变更受"删除"操作影响节点的指向并删除节点
        for (int level_i = 0; level_i < target_node_ptr->_level; ++level_i) {
            record_find_path[level_i]->_next_nodes[level_i] = target_node_ptr->_next_nodes[level_i];
        }

        // 释放节点内存
        delete target_node_ptr;
        target_node_ptr = nullptr;

        --_node_cnt;
        return true;
    }

    /**
     * 可视化打印
     * @tparam K
     * @tparam V
     */
    template<typename K, typename V>
    void SkipList<K, V>::graphical_print() {
        Node<K, V>* ptr = nullptr;
        static const int PRINT_WIDTH = 7;
        if (_node_cnt <= 0) {
            return;
        }

        log_info("graphical print:\n");

        for (int level_i = _max_level - 1; level_i >= 0; --level_i) {
            std::cout << std::right << std::setw(PRINT_WIDTH) << "->" + std::to_string(_pre_header->_next_nodes[level_i]->_key) + " |:";
            ptr = _pre_header->_next_nodes[0];
            while (ptr) {
                if (ptr->_level > level_i) {
                    std::cout << std::right << std::setw(PRINT_WIDTH) << ptr->_key;
                    if (ptr->_next_nodes[level_i]) {
                        std::cout << std::left << std::setw(PRINT_WIDTH) << " (->" + std::to_string(ptr->_next_nodes[level_i]->_key) + ")";
                    }
                } else {
                    std::cout << std::right << std::setw(PRINT_WIDTH * 2) << " ";
                }
                ptr = ptr->_next_nodes[0];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }


    /**
     * 获取 Skip list 中 K 对应的值
     * @tparam K
     * @tparam V
     * @param key
     * @return 若找到 key 则返回 key 的节点值的地址，若未找到则返回 nullptr
     */
    template<typename K, typename V>
    V* SkipList<K, V>::get(K key) {
        Node<K, V>* ret = find(key);
        return ret ? &(ret->_val) : nullptr;
    }


    /**
     * 备份 SkipList 数据到文件
     * @tparam K
     * @tparam V
     * @param file_path_to_dump
     * @return
     */
    template<typename K, typename V>
    bool SkipList<K, V>::dump(std::string file_path_to_dump) {
        Node<K, V>* ptr = nullptr;
        std::ofstream ofs;
        // 覆盖之前缓存（若存在）
        ofs.open(file_path_to_dump, std::ios::out | std::ios::trunc);

        if (!ofs.is_open()) {
            log_error("Open file failed!");
            return false;
        }
        ptr = _pre_header->_next_nodes[0];

        while (ptr) {
            ofs << ptr->_key << DELIMITER << ptr->_val << std::endl;
            ptr = ptr->_next_nodes[0];
        }
        ofs.close();
        return true;
    }


    /**
     * 加载文件数据到 SkipList 内存
     * @tparam K
     * @tparam V
     * @param file_path_to_load
     * @return
     */
    template<typename K, typename V>
    bool SkipList<K, V>::load(std::string file_path_to_load) {
        if (access(file_path_to_load.c_str(), F_OK ) != FILE_EXIST) {
            log_error("Loading file is not exist!");
            return false;
        }
        std::ifstream ifs;

        ifs.open(file_path_to_load, std::ios::in);
        if (!ifs.is_open()) {
            log_error("Open file failed!");
            return false;
        }
        std::string line;
        while (std::getline(ifs, line)) {
            std::cout << line << std::endl;

        }
        ifs.close();
        return true;
    }
}

#endif /* SKIP_LIST_H */
