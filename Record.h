//
// Created by Max on 10/06/2023.
//

#ifndef WET2_RECORD_H
#define WET2_RECORD_H


class Record {
public:
    Record(int r_id);
    ~Record() = default;
    int getNumOfPurchases() const;
    void buyRecord();

private:
    int m_r_id;
//    int mNumOfCopies;
    int mNumOfPurchases;
};


#endif //WET2_RECORD_H
