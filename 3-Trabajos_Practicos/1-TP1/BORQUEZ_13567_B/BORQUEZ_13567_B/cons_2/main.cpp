/**
 * Main program of the solution to task 2 in Part B of practical assignment #2
 * 
 * This programm handles serial communication with an Arduino UNO Board. It sends data
 * requests to the Arduino, reads the incomming data, and then writes it to a file.
 * The data is retrieved from the Arduino in a Comma Separated Value format and stored
 * in the file in the same format.
 * 
 * The programm is tailored to the specific Arduino UNO firmware and also utilizes
 * specific Windows API functions to handle serial communication
 * 
 * @version 1.0
 * @date 	2023.09.02
 * @author 	Juan Manuel BORQUEZ PEREZ
 * @contact borquez.juan00@gmail.com
 * 
*/
#include "C2File.h"
#include <iostream>
#include <ios>			//Para <streamsize>
#include <limits>		//Para numeric_limits

int main(int argc, char* argv[]) {
    int N;                          //Number of lines or registers to read from Arduino Board
    std::string filename;           //The name of the file in wich the data will be stored

    /*Main component of the programm. It manages the comunication with the Arduino Board,
    parses the incomming data, and controles the file where the data is being stored*/
    C2File dattaLogger = C2File();

    std::cout << "Indicar el numero de registros a leer : ";
    std::cin >> N;

    std::cout << "Indicar el nombre del archivo : ";
    std::cin >> filename;

    std::cout << "Iniciar sketch en la placa arduino...";

    dattaLogger.setN(N);
    dattaLogger.setFilename(filename);
    dattaLogger.createFile();

    std::cout <<"\n\n"<< dattaLogger.readStartingMessage() << std::endl;
    std::cout << "Lectura..." << std::endl;

    dattaLogger.writeFileHeader();

    while(N--){
        dattaLogger.serialRequestCSV();
        dattaLogger.processLine();
        dattaLogger.flushNewLineChar();
    }
    std::cout << "Finalizado" <<std::endl;
    dattaLogger.closeFile();
    dattaLogger.closePort();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    return EXIT_SUCCESS;
}