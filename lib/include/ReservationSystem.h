#ifndef RESERVATION_SYSTEM_H
#define RESERVATION_SYSTEM_H

#include "Reservation.h"
#include "FileTools.h"

class ReservationSystem {
    public:
        ReservationSystem();
        void PrintAvailableRooms();
        FILE* GetFilePointer();
        void SetFilePointer(const char* const file_name, const char* const mode);
    private:
        FILE* _pFile;
};
#endif