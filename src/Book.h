//
// Created by Łukasz Kolarz on 14/11/2019.
//

#include <string>
#include <ctime>

using namespace std;

#ifndef LIBRARY_SYSTEM_BOOK_H
#define LIBRARY_SYSTEM_BOOK_H

class Book {
private:
    string title, ISBN;
    int pages;
    bool availability = true, reserved = false;
    string timeBorrowed = "0";

public:
    Book(string title, string ISBN, int pages);                 //constructor to add new record (for root)
    Book(string title);                                         //constructor to find a record

    //set
    void setAvailable(bool available);
    void setReservation(bool reservation);
    void setTime();
    //get
    string getISBN();
    bool isAvailable();
    bool isReserved();
    void changesUpload();
    string getTimeBorrowed();

};


#endif //LIBRARY_SYSTEM_BOOK_H
