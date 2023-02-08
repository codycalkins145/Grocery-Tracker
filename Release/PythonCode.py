import re
import string


# Function for reading CS210_Project_Three_Input_File.txt
# and returning relevant information
def ItemsAndFrequency():
    # Opens text file for reading
    f = open('CS210_Project_Three_Input_File.txt', 'r')
    itemDict = dict() # Dictionary for storing text file contents

    for line in f: # Iterates through each line in the text file
        line = line.strip() # Strips leading and trailing whitespace
        items = line.split(" ") # Creates a list containing all items in the text file

        # Iterates through each item in the items list
        for item in items: 
            # Adds to the item's dictionary value if it is already in the dictionary
            if item in itemDict: 
                itemDict[item] = itemDict[item] + 1
            # Adds item to dictionary and assigns a value of 1 if not already in dictionary
            else:
                itemDict[item] = 1
    # Iterates through each item in the dictionary
    for key in list(itemDict.keys()): 
        # Returns "Item: Frequency" for output in C++
        print(str(key) + ": " + str(itemDict[key])) 

    f.close() # Closes text file

# Function for receiving specific item name from C++ and returning frequency value
def SingleItemFreq(v):
    f = open('CS210_Project_Three_Input_File.txt', 'r')
    itemDict = dict()

    for line in f:
        line = line.strip()
        items = line.split(" ")

        for item in items:
            if item in itemDict:
                itemDict[item] = itemDict[item] + 1
            else:
                itemDict[item] = 1

    for key in list(itemDict.keys()):
        # Sets item to lowercase for comparing to user input from C++
        keyLower = key.lower() 

        # Checks if input received from Python is the same as the 
        # item at the current dictionary position
        if v == keyLower:
            # Sets variable equal to item's dictionary value
            amount = itemDict[key] 
            break # Ends loop
        
        else:
            # Sets return equal to -1 if item is not in the dictionary.
            # This value is used to prompt user to try again in C++.
            amount = -1

    f.close()

    return amount # Sends variable value to C++

# Function for reading from CS210_Project_Three_Input_File.txt
# and creating frequency.dat
def ItemHistogram():
    f = open('CS210_Project_Three_Input_File.txt', 'r')
    w = open('frequency.dat', 'w') # Opens, or creates, frequency.dat for writing
    itemDict = dict()

    for line in f:
        line = line.strip()
        items = line.split(" ")

        for item in items:
            if item in itemDict:
                itemDict[item] = itemDict[item] + 1
            else:
                itemDict[item] = 1
    
    for key in list(itemDict.keys()):
        # Writes each dictionary item and it's value into frequency.dat,
        # formatted as "Item 0"
        w.write(str(key) + " " + str(itemDict[key]) + "\n")

    f.close()
    w.close()



    
