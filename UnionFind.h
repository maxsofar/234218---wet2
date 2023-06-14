//
// Created by Max on 10/06/2023.
//

#ifndef WET2_UNIONFIND_H
#define WET2_UNIONFIND_H

#include <utility>
#include "Record.h"

class StackNode {
public:
    StackNode() : m_column(-1), m_height(0), m_numOfRecords(0), m_rank(0), m_r(0) {}
    //fake column to return to user
    int m_column;
    int m_height;
    int m_numOfRecords;
    //real height for union to use
    int m_rank;
    int m_r;
};

//TODO: check if class needed or replace with array
class RecordNode {
public:
    RecordNode() : m_parent(-1) {}
    int m_parent;
};

class UnionFind {
public:
    UnionFind();
    ~UnionFind();
    void init(int* recordsStocks, int numberOfRecords);
    int find(int id, int* relativeHeight);
    bool unionSets(int id1, int id2);
    std::pair<int, int> getPlace(int id);
private:
    StackNode* m_stack;
    //contains an actual parent
    RecordNode* m_record;
};


#endif //WET2_UNIONFIND_H
