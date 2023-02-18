
#include "Reservation.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>

Reservation Reservation::MakeReservation(void)
{
    Reservation::PrintAvailableRooms();
    return Reservation(0,0,0,0,0,0,0,0);
}

void Reservation::PrintAvailableRooms()
{
    FILE* fp = fopen( "../../data/ExempData" , "rb");
    if (fp == NULL)
    {
        std::cout << "Error: File not found" << std::endl;
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    if(fgets(buffer, 256, fp) != NULL)
    {
        while (!feof(fp) && !ferror(fp))
        {
            fputs(buffer, stdout);
            if(fgets(buffer, 256, fp))      continue;
            else                            break;
        }
    }
}