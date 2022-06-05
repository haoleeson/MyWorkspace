/**
 * SkipList节点类（节点数据结构）
 */

#ifndef SKIP_LIST_NODE_H
#define SKIP_LIST_NODE_H

#include <cassert> // use its assert() for checking new

namespace my_skip_list_namespace {

/**
 * Skip List Node Class
 * @tparam K
 * @tparam V
 */
    template<typename K, typename V>
    class Node {
//    friend class SkipList<K, V>;// 申明友元类
    public:
        Node();
        Node(int level);
        Node(K key, V val, int level);
        ~Node();
        bool operator <(const Node<K, V>& another);
        K getKey() const;
        V getVal() const;

    private:
        inline void init_next_nodes(int level);

    public:
        int _level;
        K _key;
        V _val;
        Node<K, V>* _prev_node;    // preview node, only in the 1 level
        Node<K, V>** _next_nodes;
    };

    template<typename K, typename V>
    Node<K, V>::Node() : _prev_node(nullptr), _next_nodes(nullptr) {}

    template<typename K, typename V>
    Node<K, V>::Node(int level) : _prev_node(nullptr), _level(level) {
        init_next_nodes(level);
    }

    template<typename K, typename V>
    Node<K, V>::Node(K key, V val, int level) : _prev_node(nullptr), _key(key), _val(val), _level(level) {
        init_next_nodes(_level);
    }

    template<typename K, typename V>
    Node<K, V>::~Node() {
        if (_next_nodes) {
            _prev_node = nullptr;
            for (int i = 0; i < _level; ++i) {
                _next_nodes[i] = nullptr;
            }
            delete[] _next_nodes;
            _next_nodes = nullptr;
        }
    }

    template<typename K, typename V>
    bool Node<K, V>::operator <(const Node<K, V>& another) {
        return _key < another._key;
    }

    template<typename K, typename V>
    K Node<K, V>::getKey() const {
        return _key;
    }

    template<typename K, typename V>
    V Node<K, V>::getVal() const {
        return _val;
    }

    template<typename K, typename V>
    void Node<K, V>::init_next_nodes(int level) {
        _next_nodes = new Node<K, V>* [level];
        for (int i = 0; i < level; ++i) {
            _next_nodes[i] = nullptr;
        }
        assert(_next_nodes);
    }

}
#endif //SKIP_LIST_NODE_H
