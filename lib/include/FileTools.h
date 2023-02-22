#ifndef FILE_TOOLS_H
#define FILE_TOOLS_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

/**
 * @brief Saffer version of fgets which returns NULL if string starts with newline and checks
 * if string is not too long for buffer, if it is too long, it will be truncated to buff_size-1.
 * @param buff, buff_size, pfile 
 * @return pointer to buff or NUll if string starts with newline
 */
char* GetStr(char* const buff, const  int buff_size, FILE* const pfile);
/**
 * @brief Check whether the file is csv file or not and also if the structure of is as follows:
 * RoomId, RoomType, RoomPrice, RoomStatus, OcupancyStartDate, OcupancyEndDate
 * @param pfile 
 * @return bool value true if file is csv file and strucure is right and false if one of them is not right
 */
bool TestDataFileFormat(FILE* pfile);
/**
 * @brief Opens file and checks if it is opened successfully or not and if not, it will exit the program
 * as it is a fatal error.
 * @param file_name, mode 
 * @return 
 */
FILE* OpenFile(const char* const file_name, const char* const mode);
/**
 * @brief Closes file and checks if it is closed successfully or not and if not, it will 
 * print error message and return false, otherwise it will return true.
 * @param pfile 
 * @return bool value true if file is closed successfully and false if not
 */
bool CloseFile(FILE* pfile);

/**
 * @brief Converts  int to string
 * @param number 
 * @param str 
 * @return 
 */
char* UIntToStr( int number, char* str);

#endif