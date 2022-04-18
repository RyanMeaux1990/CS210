import re
import string
import pandas as pd

def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

    #Doubles and returns the V value received 
def DoubleValue(v):
    return v * 2

def CountOccuranceOfWord(word):
    file = open("..\CS210_Project_Three_Input_File.txt", "r")
    print("OPen ")
    #read content of file to string
    data = file.read()

    #get number of occurrences of the substring in the string
    occurrences = data.count(word)
    file.close()
    return occurrences


def GetFileDataInDict():
    # Open the file in read mode
    text = open("..\CS210_Project_Three_Input_File.txt", "r")
  
# Create an empty dictionary
    d = dict()
  
# Loop through each line of the file
    for line in text:

        # Remove the leading spaces and newline character
        line = line.strip()
        # Convert the characters in line to 
        # lowercase to avoid case mismatch
        line = line.lower()
  
        # Split the line into words
        words = line.split(" ")
  
        # Iterate over each word in line
        for word in words:
            # Check if the word is already in dictionary
            if word in d:
                # Increment count of word by 1
                d[word] = d[word] + 1
            else:
                # Add the word to dictionary with count 1
                d[word] = 1
        #text.close()
       # return d
def CountAllWords():
    d = GetFileDataInDict()
    print d
    
    


def CreateHistogram():

    df4 = pd.DataFrame(
    {
        "a": np.random.randn(1000) + 1,
        "b": np.random.randn(1000),
        "c": np.random.randn(1000) - 1,
    },
    columns=["a", "b", "c"],
)


    plt.figure();

    df4.plot.hist(alpha=0.5);
