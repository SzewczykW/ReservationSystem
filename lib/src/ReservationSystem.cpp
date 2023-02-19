#include "ReservationSystem.h"

Reservation ReservationSystem::MakeReservation(void)
{
    PrintAvailableRooms();
    return Reservation(0, 0, 0, 0, 0, 0, 0);
}

void ReservationSystem::PrintAvailableRooms()
{
    char buffer[256];
    char room_id[10];
    unsigned int count = 0;

    if (GetStr(buffer, 256, pfile) != NULL)
    {
        while (!feof(pfile) && !ferror(pfile))
        {
            if (strstr(buffer, RESERVATION_STATUS_AVAILABLE) != NULL)
            {

                char* first_comma = static_cast<char*> (memchr(buffer, ',', 10));

                int room_id_length = first_comma - buffer; // get the length of the room id

                memcpy(room_id, buffer, room_id_length);
                room_id[room_id_length] = '\0'; // null terminate the string

                fputs(room_id, stdout);
                fputc('\t', stdout);
                if (count++ % 10 == 9)
                {
                    fputc('\n', stdout);
                }
            }
            if (GetStr(buffer, 256, pfile) != NULL)
            { // get the next line
                continue;
            }
            else
            { // if we reached the end of the file
                break;
            }
        }
    }
    if (count % 10 != 9)
    {
        fputc('\n', stdout);
    }
}

FILE* ReservationSystem::GetFilePointer() {
    return pfile;
}

void ReservationSystem::SetFilePointer(const char* const file_name, const char* const mode) {
    pfile = OpenFile(file_name, mode);
}