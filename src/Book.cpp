//
// Created by Łukasz Kolarz on 14/11/2019.
//

#include "Book.h"
#include <iostream>
#include <utility>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdio>
#include <string>

using namespace std;

Book::Book(string tit, string number, int pag) {
    title = move(tit);
    ISBN = move(number);
    pages = pag;
    availability = true;
    reserved = false;
    timeBorrowed = "0";


    fstream file;
    file.open("Books.csv", ios::out | ios::app); //open file for write & seek end of the stream b4 each write
    if (file.is_open()) {
        file << title << ","
             << ISBN << ","
             << pages << ","
             << availability << ","
             << reserved << ","
             << timeBorrowed << ",\n";
        file.close();
    }
    else{
        cout << "Can't add a book!\n";
    }
}

Book::Book(const string& Title, const string& number) {

    fstream file;
    file.open("Books.csv", ios::in);
    vector<string> row;
    string line, temp;
    bool count = false;

    while (getline(file, line)) {
        row.clear();
        while (line.find(',') != string::npos) {
            row.push_back(line.substr(0, line.find(',')));
            line.erase(0, line.find(',') + 1);
        }
        if ((row[0] == Title) | (row[1] == number)) {
            count = true;
            title = row[0];
            ISBN = row[1];
            pages = stoi(row[2]);
            availability = (row[3] == "1");
            reserved = (row[4] == "1");
            timeBorrowed = (row[5]);

            break;
        }
    }
    file.close();
    if (count == 0) { cout << "Record not found!\nTry again!\n";}
}


//set
void Book::setAvailable(bool available) {availability = available;}
void Book::changesUpload() {
    ifstream file;
    ofstream temp;
    file.open("Books.csv", ios::in);
    temp.open("Temp.csv", ios::out);
    vector<string> row;
    string line, tempLine;
    while (getline(file, line)) {
        row.clear();
        tempLine = line;
        while (tempLine.find(',') != -1) {
            row.push_back(tempLine.substr(0, tempLine.find(',')));
            tempLine.erase(0, tempLine.find(',') + 1);
        }
        if (row[0] == title) {
            row[3] = to_string(availability);
            row[4] = to_string(reserved);
            row[5] = timeBorrowed;
            line = row[0] + "," +       //title
                    row[1] + "," +      //ISBN
                    row[2] + "," +      //pages
                    row[3] + "," +      //availability
                    row[4] + "," +      //reserved
                    row[5] + ",";       //time
        }
        temp << line << "\n";

    }
    file.close();
    temp.close();
    remove("Books.csv");
    rename("Temp.csv", "Books.csv");
}

void Book::setReservation(bool reservation) {reserved = reservation;}

//get
string Book::getISBN() {return ISBN;}
bool Book::isAvailable() {return availability;}
bool Book::isReserved() {return reserved;}

void Book::setTime() {
    {
        time_t current;
        struct tm * data;
        char value[80];
        time (&current);
        data =localtime (&current);
        strftime(value,80,"%d.%m.%Y",data);
        string temp(value);
        timeBorrowed = temp + ".";
    }

}

void Book::clearTime() {timeBorrowed = "0";}


string Book::getTitle() {return title;}

string Book::getTimeBorrowed() {return timeBorrowed;}

int subDate(string date){

    vector<int> borrowed;
    while(date.find('.') != string::npos){
        borrowed.push_back(stoi(date.substr(0,date.find('.'))));
        date.erase(0, date.find('.') + 1);

    }

    time_t current;
    struct tm * data;
    char value[80];
    time (&current);
    data =localtime (&current);
    strftime(value,80,"%d.%m.%Y",data);
    string temp(value);
    temp += ".";
    vector<int> returned;
    while(temp.find('.') != string::npos){
        returned.push_back(stoi(temp.substr(0,temp.find('.'))));
        temp.erase(0, temp.find('.')+1);
    }


    return days(returned[0], returned[1], returned[2]) -
           days(borrowed[0], borrowed[1], borrowed[2]);

}


int days(int d, int m, int y) {
    m = (m + 9) % 12;
    y = y - m / 10;
    return 365 * y + y / 4 - y / 100 + y / 400 + (m * 306 + 5) / 10 + (d - 1);
}

