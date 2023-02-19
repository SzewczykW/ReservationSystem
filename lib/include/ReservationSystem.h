#ifndef RESERVATION_SYSTEM_H
#define RESERVATION_SYSTEM_H

#include "Reservation.h"
#include "GetRootProjectPath.h"
#include "FileTools.h"

class ReservationSystem {
    friend FILE* OpenFile(const char* const file_name, const char* const mode);
    public:
        Reservation MakeReservation(void);
        void PrintAvailableRooms();
        FILE* GetFilePointer();
        void SetFilePointer(const char* const file_name, const char* const mode);
    private:
        FILE* pfile;
};
#endif