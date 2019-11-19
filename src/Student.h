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
    float toPay = 0;
    string rentBookNumber;
    string reservedBookNumber;



public:
    Student(string Name, string Surname, string Index);
    Student(string Index);

    void payPLN();
    void schangesUpload();

    void borrow();
    void reserve();
    void giveBack();

    void display();
};


#endif //LIBRARY_SYSTEM_STUDENT_H
