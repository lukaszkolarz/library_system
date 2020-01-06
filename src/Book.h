//
// Created by Łukasz Kolarz on 14/11/2019.
//

#include <string>

using namespace std;

#ifndef LIBRARY_SYSTEM_BOOK_H
#define LIBRARY_SYSTEM_BOOK_H

class Book {
private:
    string title, ISBN;
    int pages;
    bool availability, reserved;
    string timeBorrowed;

public:
    Book(string title, string ISBN, int pages);                        //constructor to add new record (for root)
    explicit Book(const string& title, const string& number = "0");    //constructor to find a record

    //set
    void setAvailable(bool available);
    void setReservation(bool reservation);
    void setTime();
    void clearTime();
    //get
    string getISBN();
    bool isAvailable();
    bool isReserved();
    void changesUpload();
    string getTimeBorrowed();
    string getTitle();
};


#endif //LIBRARY_SYSTEM_BOOK_H
