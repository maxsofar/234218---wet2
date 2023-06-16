//
// Created by Max on 10/06/2023.
//

#include "Record.h"

Record::Record() : m_numOfPurchases(0){}

void Record::buyRecord()
{
    m_numOfPurchases++;
}

int Record::getNumOfPurchases() const
{
    return m_numOfPurchases;
}
