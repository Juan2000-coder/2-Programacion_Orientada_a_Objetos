#ifndef _C2FILE_H
#define _C2FILE_H
/**
 * Header file for the main class to be used in the project
 * 
 * @version 1.0
 * @date 	2023.09.02
 * @author 	Juan Manuel BORQUEZ PEREZ
 * @contact borquez.juan00@gmail.com
 * 
*/
#include <string>
#include <windows.h>   //Contains the methods to use a Windows API to manage serial communication
#include <iostream>
#include <fstream>
#include <tchar.h>

class C2File {
  private:
    int N;                //Number of register to be read from the Arduino Board

    std::string filename; //Name of the file where the data will be stored

    HANDLE portHandler;   //A handle to the COM Port

    std::fstream file;    //A stream to the file

    DCB serialParameters = { 0 }; //Initial parameters of Serial Communication

    char request = 'c';   //Requesto Code to get data from the Arduino Board in a CSV format

    char buffer[100];     //Buffer to store incomming data from serial PORT

  public:

    /*Initial Methods*/
    C2File();

    void setFilename(std::string filename);

    void setN(int N);

    void serialRequestCSV();

    /*Methods to manage serial comunication*/

    void serialConfig();

    void serialRead(char* receiver, DWORD numberOfBytesToRead);

    void serialReadLine();

    std::string parseLine();

    void processLine();

    std::string readStartingMessage();

    char* getBuffer();

    char* getBufferCurrentPosition();

    char getBufferLastChar();

    void bufferFlush();

    void serialWrite(char* request);

    void closePort();

    /*Methods to manage the file*/

    void createFile();
    
    void fileWriteLine(std::string line);

    void writeFileHeader();

    void flushNewLineChar();

    void closeFile();

};
#endif
