//
// Created by Max on 10/06/2023.
//

#include "Customer.h"

Customer::Customer(int c_id, int phoneNumber) : m_c_id(c_id), m_phoneNumber(phoneNumber), m_isClubMember(false),
                                                m_monthlyExpenses(0) {}

int Customer::getPhoneNumber() const
{
    return m_phoneNumber;
}

bool Customer::isClubMember() const
{
    return m_isClubMember;
}

void Customer::makeMember()
{
    m_isClubMember = true;
}

void Customer::buyRecord(int t)
{
    if (m_isClubMember)
        m_monthlyExpenses += 100 + t;
}

int Customer::getID() const
{
    return m_c_id;
}

void Customer::resetExprenses()
{
    m_monthlyExpenses = 0;
}

double Customer::getExpenses() const
{
    return m_monthlyExpenses;
}
