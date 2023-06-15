//
// Created by Max on 10/06/2023.
//

#include "UnionFind.h"



//#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif

UnionFind::UnionFind() : m_stack(nullptr), m_parent(nullptr)
                          {}

UnionFind::~UnionFind()
{
    delete[] m_stack;
    delete[] m_parent;
}

void UnionFind::init(int* m_recordStocks, int number_of_m_record)
{
    delete[] m_stack;
    delete[] m_parent;
    m_stack = new StackNode[number_of_m_record];
//    m_parent = new RecordNode[number_of_m_record];
    m_parent = new int[number_of_m_record];
    for (int i = 0; i < number_of_m_record; ++i) {
        m_stack[i].m_height = m_recordStocks[i];
        m_stack[i].m_column = i;
        m_parent[i] = i;
    }

}

//path compression find function
int UnionFind::find(int id, int* relativeHeight)
{
    int cur = id;
    int sum = 0;

    while (m_parent[cur] != cur) {
        sum += m_stack[cur].m_r;
        cur = m_parent[cur];
    }

    int root = cur;
    cur = id;

    int toSubtract = 0;
    while (m_parent[cur] != cur) {
        int temp = m_stack[cur].m_r;
        m_stack[cur].m_r = sum - toSubtract;
#ifdef DEBUG
        std::cout <<  cur << "(r_new): "<< m_stack[cur].m_r << std::endl;
#endif
        toSubtract += temp;
        temp = m_parent[cur];
        m_parent[cur] = root;
        cur = temp;

    }

    if (relativeHeight != nullptr)
        *relativeHeight = sum + m_stack[cur].m_r;

    return cur;
}

//weighted union function
bool UnionFind::unionSets(int id1, int id2)
{
    int B = find(id1, nullptr);
    int A = find(id2, nullptr);
    if (B == A)
        return false;

    m_stack[B].m_column = m_stack[A].m_column;

    if (m_stack[A].m_rank >= m_stack[B].m_rank ) {
        m_parent[B] = A;

        m_stack[A].m_rank++;
        m_stack[B].m_r += m_stack[A].m_height - m_stack[A].m_r;
        m_stack[A].m_height += m_stack[B].m_height;
#ifdef DEBUG
        std::cout << "B(r): " << m_stack[B].m_r << std::endl;
        std::cout << "A(h): " << m_stack[A].m_height << std::endl;
#endif

    } else {
        m_parent[A] = B;
        m_stack[B].m_rank++;
        m_stack[B].m_r += m_stack[A].m_height;
        m_stack[A].m_r -= m_stack[B].m_r;
        m_stack[B].m_height += m_stack[A].m_height;

#ifdef DEBUG
        std::cout << "B(r): " << m_stack[B].m_r << std::endl;
        std::cout << "A(r): " << m_stack[A].m_r << std::endl;
        std::cout << "B(h): " << m_stack[B].m_height << std::endl;
#endif
    }

    return true;
}

std::pair<int, int> UnionFind::getPlace(int id) {
    int relativeHeight;
    StackNode stack = m_stack[find(id, &relativeHeight)];
    int column = stack.m_column;

    return std::make_pair(column, relativeHeight);
}

