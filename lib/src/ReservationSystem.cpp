#include "ReservationSystem.h"
#include "Reservation.h"
#include <iostream>
#include <stdlib.h>

void ReservationSystem (void)
{
    Reservation res = Reservation::MakeReservation();
    std::cout << res.GetRoomId() << std::endl;
    return;
}