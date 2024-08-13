#include "C2File.h"

/**
 * @brief Constructor for the main class
*/

C2File::C2File(){
    this->serialConfig();
    memset(this->buffer,'\0', sizeof(this->buffer));
}

/**
 * @brief Sets the name of the file where the data will be stored
 * @param filename - the name of the file
*/

void C2File::setFilename(std::string filename) {
    this->filename = filename;
}

/**
 * @brief Sets the number of registers to be read from the Arduino Board
 * @param N - the number of registers
*/
void C2File::setN(int N) {
    this->N = N;
}

/**
 * @brief Sends a data request to the Arduino Board
*/
void C2File::serialRequestCSV() {
    this->serialWrite(&this->request);
}

/**
 * @brief Configures the Parameters for the Serial Communication
*/
void C2File::serialConfig(){
    this->portHandler = CreateFile(
        TEXT("COM3"),                  //Serial PORT
        GENERIC_READ | GENERIC_WRITE,  //Openned for both reading and writing
        0,                             //Non shared Port
        NULL,                          //For Default behavior
        OPEN_EXISTING,                 //Open the Serial Port if it exist only (can't creat it)
        FILE_ATTRIBUTE_NORMAL,         //Default Attribute for files
        NULL                           //Set to NULL by default
    );

    if (this->portHandler == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open serial port." << std::endl;
    }

    /*Sets the parameter for serial communication*/
    this->serialParameters.DCBlength = sizeof(this->serialParameters);
    this->serialParameters.BaudRate = CBR_19200;
    this->serialParameters.ByteSize = 8;
    this->serialParameters.StopBits = ONESTOPBIT;
    this->serialParameters.Parity = NOPARITY;

    if (!SetCommState(this->portHandler, &(this->serialParameters))) {
        std::cerr << "Error setting serial port state." << std::endl;
        CloseHandle(this->portHandler);
    }
}

/**
 * @brief Reads a specified number of bytes from serial port and stores them in a variable
 * @param receiver - A variable to store the bytes read
 * @param numberOfBytesToRead - The number of characters/Bytes to read
*/
void C2File::serialRead(char* receiver, DWORD numberOfBytesToRead){
    DWORD bytesRead;
    if (!ReadFile(this->portHandler, receiver, numberOfBytesToRead, &bytesRead, NULL)) {
        std::cerr << "Error reading from serial port." << std::endl;
        CloseHandle(this->portHandler);
    }
}

/**
 * @brief Reads a register or line ('\n' terminated string) from the Arduino Board
*/
void C2File::serialReadLine(){
    this->serialRead(this->getBufferCurrentPosition(), 1);
    while(this->getBufferLastChar() != '\n'){
        this->serialRead(this->getBufferCurrentPosition(), 1); //Reads one character at a time
    }
}

/**
 * @brief Parses each line read from the serial PORT and replaces ',' with ';'
 * @return The parsed String to be written in the file
*/
std::string C2File::parseLine(){
    short int i = -1;
    std::string line = std::string(this->buffer);
    while ((i = line.find(',', i + 1)) != std::string::npos){
        line[i] = ';';
    }
    return line;
}

/**
 * @brief Process an incoming line of data from the Arudino Board
*/
void C2File::processLine(){
    this->serialReadLine();
    this->fileWriteLine(this->parseLine());
    this->bufferFlush();
}

/**
 * @brief Reads the initial message in the Arduino sketch
 * @return receiver - A string with the initial message received
*/
std::string C2File::readStartingMessage(){
    std::string startingMessage;
    for (short int i = 0; i < 4; i++){
        this->serialReadLine();
    }
    startingMessage = std::string(this->getBuffer());
    this->bufferFlush();
    return startingMessage;
}

/**
 * @brief Obtains a pointer to the last non null character in the buffer
 * @return a pointer to the last non null character in the buffer
*/
char* C2File::getBufferCurrentPosition(){
    return (this->buffer + strlen(this->buffer));
}

/**
 * @brief Obtains the contain in the buffer
 * @return An array with the characters in the buffer
*/
char* C2File::getBuffer(){
    return this->buffer;
}

/**
 * @brief Obtains the last non null character in the buffer
 * @return the las character in the buffer
*/
char C2File::getBufferLastChar(){
    return this->buffer[strlen(this->buffer)-1];
}

/**
 * @brief Sets the buffer to '\0' in all the positions
*/
void C2File::bufferFlush(){
    /*Esta también hay que cambiarla*/
    memset(this->buffer, '\0', strlen(this->buffer));
}

/**
 * @brief Writes a given array of characters to the serial port
 * @param request - an array of characters or a pointer to the initial character
*/
void C2File::serialWrite(char *request){
    DWORD bytesWritten;
    if (!WriteFile(this->portHandler, request, sizeof(request), &bytesWritten, NULL)) {
        std::cerr << "Error writing to serial port." << std::endl;
        CloseHandle(this->portHandler);
    }
}

/**
 * @brief Closes the serial Port
*/
void C2File::closePort(){
    CloseHandle(this->portHandler);
}

/**
 * @brief Creates the file where the data will be store or opens it if it already exists
*/
void C2File::createFile(){
    this->file.open(this->filename, std::ios::out);
    if (!this->file){
        std::cerr << "Error opening file"<<std::endl;
    }
}

/**
 * @brief Stores a line in the file
 * @param line - a strig with the data to be stored
*/
void C2File::fileWriteLine(std::string line){
    this->file << line;
}

/**
 * @brief Writes the Header of the file
*/
void C2File::writeFileHeader(){
    std::string Header = "dispositivo_id;porcentaje_valvula;estado_nivel;caudal\n";
    this->fileWriteLine(Header);
}

/**
 * @brief It flushes the remaining '\n' after each incoming data line in the serial port
*/
void C2File::flushNewLineChar(){
    this->serialRead(this->buffer, 2); //There are 2 new line character after each line
    this->bufferFlush();
}

/**
 * @brief Closes the file
*/
void C2File::closeFile(){
    this->file.close();
}