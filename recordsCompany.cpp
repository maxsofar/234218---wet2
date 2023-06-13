//
// Created by Max on 10/06/2023.
//

#include "recordsCompany.h"
#include <utility>

//O(1)
RecordsCompany::RecordsCompany() : m_numberOfRecords(0)
{}

//O(n + m) m = number_of_records
StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records)
{
    if (number_of_records < 0)
        return INVALID_INPUT;

    m_numberOfRecords = number_of_records;
    delete[] m_records;
    m_records = new std::shared_ptr<Record>[number_of_records];

    //TODO: ALLOCATION ERROR

    for (int i = 0; i < number_of_records; ++i) {
        //TODO: probably shared ptr not needed here
        m_records[i] = std::make_shared<Record>(i, records_stocks[i]);
    }

    m_recordsUF.init(records_stocks, number_of_records);
    return SUCCESS;
}

//O(1) on average / approximated
StatusType RecordsCompany::addCostumer(int c_id, int phone)
{
    if (c_id < 0 || phone < 0)
        return INVALID_INPUT;

    //TODO: ALREADY EXISTS, ALLLOCATION ERROR

    std::shared_ptr<Customer> customer = std::make_shared<Customer>(c_id, phone);
    m_customers.insert(c_id, customer);

    return SUCCESS;
}

Output_t<int> RecordsCompany::getPhone(int c_id)
{
    if (c_id < 0)
        return Output_t<int>(INVALID_INPUT);

    std::shared_ptr<Customer> customer = m_customers.find(c_id);
    if (customer == nullptr)
        return Output_t<int>(DOESNT_EXISTS);

    return Output_t<int>(customer->getPhoneNumber());
}

Output_t<bool> RecordsCompany::isMember(int c_id)
{
    if (c_id < 0)
        return Output_t<bool>(INVALID_INPUT);

    std::shared_ptr<Customer> customer = m_customers.find(c_id);
    if (customer == nullptr)
        return Output_t<bool>(DOESNT_EXISTS);

    return Output_t<bool>(customer->isClubMember());
}

//-------------------------------------------------------------

//O(log n)
StatusType RecordsCompany::makeMember(int c_id)
{
    if (c_id < 0)
        return INVALID_INPUT;

    std::shared_ptr<Customer> customer = m_customers.find(c_id);
    if (customer == nullptr)
        return DOESNT_EXISTS;

    if (customer->isClubMember())
        return FAILURE;

    customer->makeMember();
    m_clubMembers.insert(customer->getID(), customer);

    return SUCCESS;
}

StatusType RecordsCompany::buyRecord(int c_id, int r_id)
{
    if (c_id < 0 || r_id < 0)
        return INVALID_INPUT;

    if (r_id >= m_numberOfRecords)
        return DOESNT_EXISTS;

    std::shared_ptr<Customer> customer = m_customers.find(c_id);
    if (customer == nullptr)
        return DOESNT_EXISTS;

    customer->buyRecord(m_records[r_id]->getNumOfPurchases());
    m_records[r_id]->buyRecord();

    return SUCCESS;

}

StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double amount)
{
    if (c_id1 < 0 || c_id2 < c_id1 || amount <= 0)
        return INVALID_INPUT;


    m_clubMembers.addPrize(c_id1, c_id2, amount);

    return SUCCESS;
}

Output_t<double> RecordsCompany::getExpenses(int c_id)
{
    if (c_id < 0)
        return Output_t<double>(INVALID_INPUT);

    std::pair<double, bool> expenses = m_clubMembers.sumUpExtra(c_id);
    if (!expenses.second)
        return Output_t<double>(DOESNT_EXISTS);
    else {
        //TODO: seems like not needed
//        if (expenses.first < 0)
//            return 0;
        return expenses.first;
    }
}

//-------------------------------------------------------------

//O(log * m)
StatusType RecordsCompany::putOnTop(int r_id1, int r_id2)
{
    if (r_id1 < 0 || r_id2 < 0)
        return INVALID_INPUT;

    if (r_id1 >= m_numberOfRecords || r_id2 >= m_numberOfRecords)
        return DOESNT_EXISTS;

    //TODO: allocation error

    m_recordsUF.unionSets(r_id1, r_id2);

    return SUCCESS;
}

StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight)
{
    if (r_id < 0 || column == nullptr || hight == nullptr)
        return INVALID_INPUT;

    if (r_id >= m_numberOfRecords)
        return DOESNT_EXISTS;

    std::pair<int, int> column_height = m_recordsUF.getPlace(r_id);

    *column = column_height.first;
    *hight = column_height.second;


    return SUCCESS;
}




