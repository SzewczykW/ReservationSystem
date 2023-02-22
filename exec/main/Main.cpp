#include "ReservationSystem.h"

int main(void)
{
    ReservationSystem menu; 
    menu.PrintAvailableRooms();
    CloseFile(menu.GetFilePointer());
    Reservation* res = Reservation::MakeReservation(1, 105, menu.GetFilePointer());
    free(res);
    return 0;
}