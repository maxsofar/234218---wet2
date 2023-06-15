//
// Created by Max on 10/06/2023.
//

#ifndef WET2_HASHTABLE_H
#define WET2_HASHTABLE_H

#include <iostream>
#include "Tree.h"

//Hash table with avl tree collision handling
template <class K, class V>
class HashTable {
public:
    HashTable();
    ~HashTable();
    void insert(K key, V value);
    V find(K key);
    void remove(K key);
    void resetExpenses();
private:
    int m_size;
    int m_capacity;
    Tree<K, V>* m_table;
    int hash(K key);
    void deleteTable();
    void resize();
};

template<class K, class V>
HashTable<K, V>::HashTable() : m_size(0), m_capacity(10), m_table(new Tree<K, V>[10])
{}

template<class K, class V>
HashTable<K, V>::~HashTable()
{
    deleteTable();
}

template<class K, class V>
void HashTable<K, V>::deleteTable()
{
    delete [] m_table;
}

template<class K, class V>
int HashTable<K, V>::hash(K key)
{
    return key % m_capacity;
}

template<class K, class V>
void HashTable<K, V>::insert(K key, V value)
{
    if (m_size == m_capacity)
        resize();
    int index = hash(key);
    m_table[index].insert(key, value);
    m_size++;
}

template<class K, class V>
V HashTable<K, V>::find(K key)
{
    int index = hash(key);
    Node<K, V>* node = m_table[index].find(key, m_table[index].getRoot());
    if (node == nullptr)
        return nullptr;
    return node->getValue();
}

template<class K, class V>
void HashTable<K, V>::remove(K key)
{
    int index = hash(key);
    m_table[index].remove(key);
    m_size--;
}

template<class K, class V>
void HashTable<K, V>::resize()
{
    int oldCapacity = m_capacity;
    m_capacity *= 2;
    auto hash = [this](K key){return this->hash(key);};
    auto* newTable = new Tree<K, V>[m_capacity];
    for (int i = 0; i < oldCapacity; ++i)
    {
        m_table[i].inOrder(m_table[i].getRoot(), newTable, hash);
    }
    deleteTable();
    m_table = newTable;
}

template<class K, class V>
void HashTable<K, V>::resetExpenses()
{
    for (int i = 0; i < m_capacity; ++i)
    {
        m_table[i].resetExpenses(m_table[i].getRoot());
    }
}


#endif //WET2_HASHTABLE_H
