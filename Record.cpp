//
// Created by Max on 10/06/2023.
//

#include "Record.h"

Record::Record(int r_id) : m_r_id(r_id), mNumOfPurchases(0){}

void Record::buyRecord()
{
    mNumOfPurchases++;
}

int Record::getNumOfPurchases() const
{
    return mNumOfPurchases;
}
