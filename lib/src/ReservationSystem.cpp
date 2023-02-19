#include "ReservationSystem.h"
#include "Reservation.h"
#include <iostream>
#include <cstdlib>

void ReservationSystem (void)
{
    if (TestDataFileFormat(Reservation::GetFilePointer()) == false ) {
        std::cout << "Error: Data file format is incorrect" << std::endl;
        exit(EXIT_FAILURE);
    }
    Reservation res = Reservation::MakeReservation();
    std::cout << res.GetRoomId() << std::endl;
    return;
}