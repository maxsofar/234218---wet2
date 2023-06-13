//
// Created by Max on 10/06/2023.
//

#include "UnionFind.h"

UnionFind::UnionFind() : m_stack(nullptr), m_record(nullptr)
                          {}

UnionFind::~UnionFind()
{
    delete[] m_stack;
    delete[] m_record;
}

void UnionFind::init(int* m_recordStocks, int number_of_m_record)
{
    m_stack = new StackNode[number_of_m_record];
    m_record = new RecordNode[number_of_m_record];
    for (int i = 0; i < number_of_m_record; ++i) {
        m_stack[i].m_height = m_recordStocks[i];
        m_stack[i].m_column = i;
        m_record[i].m_parent = i;
    }

}

//path compression find function
int UnionFind::find(int id, int* relativeHeight)
{
    int cur = id;
    int sum = 0;

    while (m_record[cur].m_parent != cur) {
        sum += m_stack[cur].m_r;
        cur = m_record[cur].m_parent;
    }

    sum += m_stack[cur].m_r;

    int root = cur;
    cur = id;

    int toSubtract = 0;
    while (m_record[cur].m_parent != cur) {
        int temp = m_stack[cur].m_r;
        m_stack[cur].m_r = sum - toSubtract;
        toSubtract += temp;
        temp = m_record[cur].m_parent;
        m_record[cur].m_parent = root;
        cur = temp;
    }

    if (relativeHeight != nullptr)
        *relativeHeight = sum;

    return cur;
}

//weighted union function
void UnionFind::unionSets(int id1, int id2)
{
    int B = find(id1, nullptr);
    int A = find(id2, nullptr);
    if (B == A)
        return;

    m_stack[B].m_column = m_stack[A].m_column;

    if (m_stack[B].m_rank <= m_stack[A].m_rank) {
        m_record[B].m_parent = A;

        m_stack[A].m_rank++;
        m_stack[B].m_r += m_stack[A].m_height - m_stack[A].m_r;
        m_stack[A].m_height += m_stack[B].m_height;

    } else {
        m_record[A].m_parent = B;
        m_stack[B].m_rank++;
        m_stack[B].m_r += m_stack[A].m_height;
        m_stack[A].m_r -= m_stack[B].m_r;
        m_stack[B].m_height += m_stack[A].m_height;

    }

}

std::pair<int, int> UnionFind::getPlace(int id) {
    int relativeHeight;
    StackNode stack = m_stack[find(id, &relativeHeight)];
    int column = stack.m_column;

    return std::make_pair(column, relativeHeight);
}

