//
// Created by Łukasz Kolarz on 05/11/2019.
//

#include <string>
#include <utility>

using namespace std;

#ifndef LIBRARY_SYSTEM_STUDENT_H
#define LIBRARY_SYSTEM_STUDENT_H


class Student {
private:
    string name , surname, index;
    int toPay = 0 , rentBookNumber = 0, reservedBookNumber = 0 ;


public:
    Student(string Name, string Surname, string Index);
    Student(string Index);


    void display();
};


#endif //LIBRARY_SYSTEM_STUDENT_H
