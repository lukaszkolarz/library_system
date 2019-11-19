#include <iostream>
#include "src/Student.h"
#include "src/Book.h"

#include <ctime>
#include <string>


std::string sprawdz_godzine()
{
    time_t czas;
    struct tm * data;
    char godzina[80];
    time (&czas);
    data =localtime (&czas);
    strftime (godzina,80,"%d.%m.%Y, %H:%M",data);
    return godzina;
}




int main() {

    //Book ksiazka("Pan Samochodzik i Templariusze", "200", 250);
    //Book ksiega("Wladca Pierscieni");
    //ksiega.setTime();
   // ksiega.setAvailable(true);
   // ksiega.setReservation(false);
    //ksiega.changesUpload();




    //Student pierwszy("2137");
    //pierwszy.display();


    Student osoba("234");
    //osoba.borrow();
    osoba.giveBack();



    return 0;
}
