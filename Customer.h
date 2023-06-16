//
// Created by Max on 10/06/2023.
//

#ifndef WET2_CUSTOMER_H
#define WET2_CUSTOMER_H

class Customer {
public:
    Customer(int c_id, int phoneNumber);
    ~Customer() = default;
    const Customer& operator=(const Customer& other) = delete;
    Customer(const Customer& other) = delete;
    int getPhoneNumber() const;
    bool isClubMember() const;
    void makeMember();
    void buyRecord(int t);
    int getID() const;
    void resetExpenses();
    double getExpenses() const;
private:
    int m_c_id;
    int m_phoneNumber;
    bool m_isClubMember;
    double m_monthlyExpenses;
};


#endif //WET2_CUSTOMER_H
