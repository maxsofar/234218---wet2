//
// Created by Max on 10/06/2023.
//

#include "recordsCompany.h"

using std::shared_ptr;

RecordsCompany::RecordsCompany() : m_records(nullptr), m_numberOfRecords(0)
{}

RecordsCompany::~RecordsCompany()
{
    delete[] m_records;
}

StatusType RecordsCompany::newMonth(int* records_stocks, int number_of_records)
{
    if (number_of_records < 0)
        return INVALID_INPUT;

    m_numberOfRecords = number_of_records;
    delete[] m_records;

    try {
        m_records = new int[number_of_records];
        for (int i = 0; i < number_of_records; ++i) {
            m_records[i] = 0;
        }
        m_recordsUF.init(records_stocks, number_of_records);
    } catch (std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    }
    m_clubMembers.resetExpenses(m_clubMembers.getRoot());

    return SUCCESS;
}

StatusType RecordsCompany::addCostumer(int c_id, int phone)
{
    if (c_id < 0 || phone < 0)
        return INVALID_INPUT;

    shared_ptr<Customer> customer = m_customers.find(c_id);
    if (customer != nullptr)
        return ALREADY_EXISTS;


    customer = std::make_shared<Customer>(c_id, phone);
    try {
        m_customers.insert(c_id, customer);
    } catch (std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    }

    return SUCCESS;
}

Output_t<int> RecordsCompany::getPhone(int c_id)
{
    if (c_id < 0)
        return {INVALID_INPUT};

    shared_ptr<Customer> customer = m_customers.find(c_id);
    if (customer == nullptr)
        return {DOESNT_EXISTS};

    return {(customer->getPhoneNumber())};
}

Output_t<bool> RecordsCompany::isMember(int c_id)
{
    if (c_id < 0)
        return {INVALID_INPUT};

    shared_ptr<Customer> customer = m_customers.find(c_id);
    if (customer == nullptr)
        return {DOESNT_EXISTS};

    return {(customer->isClubMember())};
}

//-------------------------------------------------------------

StatusType RecordsCompany::makeMember(int c_id)
{
    if (c_id < 0)
        return INVALID_INPUT;

    shared_ptr<Customer> customer = m_customers.find(c_id);
    if (customer == nullptr)
        return DOESNT_EXISTS;

    if (customer->isClubMember())
        return ALREADY_EXISTS;

    customer->makeMember();
    try {
        m_clubMembers.insert(customer->getID(), customer);
    } catch (std::bad_alloc& e) {
        return ALLOCATION_ERROR;
    }

    return SUCCESS;
}

StatusType RecordsCompany::buyRecord(int c_id, int r_id)
{
    if (c_id < 0 || r_id < 0)
        return INVALID_INPUT;

    if (r_id >= m_numberOfRecords)
        return DOESNT_EXISTS;

    shared_ptr<Customer> customer = m_customers.find(c_id);
    if (customer == nullptr)
        return DOESNT_EXISTS;

    customer->buyRecord(m_records[r_id]);
    m_records[r_id]++;

    return SUCCESS;

}

StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double amount)
{
    if (c_id1 < 0 || c_id2 < c_id1 || amount <= 0)
        return INVALID_INPUT;

    if (c_id1 == c_id2)
        return SUCCESS;
    m_clubMembers.addPrize(c_id1, c_id2, amount);

    return SUCCESS;
}

Output_t<double> RecordsCompany::getExpenses(int c_id)
{
    if (c_id < 0)
        return {INVALID_INPUT};

    double expenses = 0;
    if (!m_clubMembers.sumUpExtra(c_id, &expenses))
        return {DOESNT_EXISTS};
    else
        return {expenses};
}

//-------------------------------------------------------------

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2)
{
    if (r_id1 < 0 || r_id2 < 0)
        return INVALID_INPUT;

    if (r_id1 >= m_numberOfRecords || r_id2 >= m_numberOfRecords)
        return DOESNT_EXISTS;

    if (!m_recordsUF.unionSets(r_id1, r_id2))
        return FAILURE;

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

