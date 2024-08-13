from C3File import C3File
from C3Register import C3Register
import os

class C3Report:
    def readUser(self):
        """ Reads the user name
        """
        self.user = input ("\nINDIQUE NOMBRE DE USUARIO: ")

    def readFileName(self):
        """ Reads the file name
        """
        self.filename = input ("\nINDIQUE NOMBRE DEL ARCHIVO: ")
    def createReport(self):
        """
        Create a report, which includes obtaining the file's creation date,
        reading data from the file, and presenting it on the screen in a tabular form
        """
        self.filename = os.path.join(self.fileroute, self.filename)
        with C3File(self.filename) as file:
            print(f"OPERADOR ACTUAL: {self.user}")

            firstLine = True
            header = file.getTags()

            row = C3Register()
            file.getRow(row)

            while row.device != None:  # While EOF is not reached
                if firstLine:   # Only the first line was read
                    firstLine = False
                    file.deviceId = row.device

                    print(file.getInfo())   # Metadata
                    print(file.upperLine()) # Top border line
                    print(header)   # Tags
                    print(file.dividerLine())   # Divider line

                # Converts the row into a list of strings
                listedRow = [str(row.porcOpenValve), str(row.nivelState), str(row.flow)]
                print(file.lineFormat.format(*listedRow))   # Format the list
                file.getRow(row) # Next Row
            print(file.lowerLine()) # Bottom border line
            
    def __init__(self):
        self.user = None
        # The file path to the data file
        self.fileroute = os.path.join(os.path.dirname(os.getcwd()), "cons_2")
        self.filename = None

        # A flag to determine if a file name is valid or not
        self.validFileName = False

        # A list containing the name of all files in the directory
        self.fileDirectory = os.listdir(self.fileroute)