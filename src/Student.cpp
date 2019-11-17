//
// Created by Łukasz Kolarz on 05/11/2019.
//

#include "Student.h"
#include "Book.h"
#include <fstream>
#include <iostream>
#include <vector>


Student::Student(string Name, string Surname, string Index) {
    name = move(Name);
    surname = move(Surname);
    index = move(Index);

    fstream file;
    file.open("Students.csv", ios::out | ios::app); //open file for write & seek end of the stream b4 each write
        if (file.is_open()) {
            file << index << ","
                 << surname << ","
                 << name << ","
                 << rentBookNumber << ","
                 << toPay << ","
                 << reservedBookNumber << ","
                 << timeBorrow << ",\n";
            file.close();
        }
        else{
            cout << "Can't add an user\n";
        }

}

Student::Student(string Index) {
    fstream file;
    file.open("Students.csv", ios::in);
    vector<string> row;
    string line, temp;
    int count = 0;

    while(getline(file, line)) {
        row.clear();
        while (line.find(',') != -1) {
            row.push_back(line.substr(0, line.find(',')));
            line.erase(0, line.find(',') + 1);
        }
        if(row[0] == Index){
            count = 1;
            index = row[0];
            surname = row[1];
            name = row[2];
            rentBookNumber = stoi(row[3]);
            toPay = stoi(row[4]);
            reservedBookNumber = row[5];
            break;
        }
    }
    file.close();
    if(count == 0){
        cout << "Record not found!\nAdd new one\n\n";
        string Name, Surname;
        cout << "Insert your first name:\n";
        cin >> Name;
        cout << "Insert your surname:\n";
        cin >> Surname;
        Student(Name, Surname, Index);
    }
}

void Student::display(){
    if(!index.empty()) {
        cout << index << "\n"
             << surname << "\n"
             << name << "\n"
             << rentBookNumber << "\n"
             << reservedBookNumber << "\n"
             << toPay << "\n";
    }
}

void Student::borrow() {
    string title;
    cout << "Please, insert title of the book you want to borrow:\n";
    cin >> title;
    Book borrowed(title);
    if (borrowed.isAvailable()) {
        borrowed.setTime();
        borrowed.setAvailable(false);
        rentBookNumber = borrowed.getISBN();
        borrowed.changesUpload();
    }
    else{cout << "Not available at the moment!\n";}
}