from  C3Register import C3Register
import os
from datetime import datetime
import csv

class C3File():
    def getInfo(self):
        """Gets the date, time and the device ID and returns this information in a string

        returns:
            str: The info in a string 
        """
        fileTimeStamp = os.path.getctime(self.filename)     # Gets the time of creation of the file without format
        fileDate = datetime.fromtimestamp(fileTimeStamp).strftime('%Y-%m-%d   %H:%M:%S')    # Formats the timestamp
        return ("FECHA Y HORA DEL REPORTE: "+ fileDate + '\n' + "ID DEL DISPOSITIVO: "+ str(self.deviceId) + '\n')
    
    def getRow(self, row: C3Register):
        """ Modifies de row attributes with the fields in the next line of the file
        """
        try:
            line = next(self.reader)

            row.device = int(line[0])
            row.porcOpenValve = int(line[1])
            row.nivelState = line[2]
            row.flow = float(line[3])

        except StopIteration:   # Reached end of the file
            row.device = None

    def getTags(self):
        """ Obtains the Tags in the file
        
        returns:
            str: a formatted string with the Tags 
        """
        tags = next(self.reader)[1:]    # Discars the Device_id Tag
        return self.lineFormat.format(*tags)
    
    def upperLine(self):
        """ Obtains the top borde line of the data table
        """
        return(' ' + ' '.join(["_"*20,"_"*20,"_"*10]) + ' ')
    
    def lowerLine(self):
        """ Obtains the bottom border line of the data table
        """
        return("|"+"|".join(["_"*20,"_"*20,"_"*10])+"|")
    
    def dividerLine(self):
        """ Obtains the divider line between the Tags and the data in
        the data table
        """
        return("|"+"|".join(["_"*20,"_"*20,"_"*10])+"|")
    
    def __init__(self, filename:str):
        self.filename = filename
        self.file = open(self.filename, newline = '')   # Opens the file
        self.reader = csv.reader(self.file, delimiter = ';')    # Creates a Reader object
        self.deviceId = None
        self.lineFormat = "|{:^20}|{:^20}|{:^10}|"  # Format for each line in the table

    def __enter__(self):
        """ context method for the class
        invoqued at the start of a 'with' block
        """
        return self
    
    def __exit__(self, exc_type, exc_value, traceback):
        """ context method for the class
        invoqued at the end of a 'with' block
        """
        self.file.close()