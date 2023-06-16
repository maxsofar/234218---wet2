//
// Created by Max on 10/06/2023.
//

#ifndef WET2_RECORD_H
#define WET2_RECORD_H

class Record {
public:
    Record();
    ~Record() = default;
    const Record& operator=(const Record& other) = delete;
    Record(const Record& other) = delete;
    int getNumOfPurchases() const;
    void buyRecord();

private:
    int m_numOfPurchases;
};


#endif //WET2_RECORD_H
