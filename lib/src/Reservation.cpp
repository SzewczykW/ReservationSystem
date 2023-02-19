#include "Reservation.h"

FILE* Reservation::pfile = OpenFile(DATA_PATH, "rb");

Reservation Reservation::MakeReservation(void)
{
    Reservation::PrintAvailableRooms();
    return Reservation(0,0,0,0,0,0,0);
}

void Reservation::PrintAvailableRooms() {

    char buffer[256];
    char room_id[10];
    unsigned int count = 0;

    if(GetStr(buffer, 256, pfile) != NULL) {
        while (!feof(pfile) && !ferror(pfile)) {
            if ( strstr(buffer, RESERVATION_STATUS_AVAILABLE) != NULL ) {

                char* first_comma = static_cast<char*> ( memchr(buffer, ',', 10) );

                int room_id_length = first_comma - buffer; // get the length of the room id

                memcpy(room_id, buffer, room_id_length); 
                room_id[room_id_length] = '\0'; // null terminate the string

                fputs(room_id, stdout);
                fputc('\t', stdout);
                if (count++ % 10 == 9) {
                    fputc('\n', stdout);
                }
            }
            if(GetStr(buffer, 256, pfile) != NULL) { // get the next line
                continue;
            }
            else { // if we reached the end of the file
                break;
            }
        }
    }
    if (count % 10 != 9) {
        fputc('\n', stdout);
    }
}