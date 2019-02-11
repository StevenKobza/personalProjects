import os, fnmatch
from tkinter import *

class MyGUI:
    def __init__(self):
        self.main_window = Tk()
        self.main_window.geometry("900x900+500+50")
        self.main_window.title("Batch Renamer")
        self.mainFrame = Frame(self.main_window, width = 900, height = 900)
        self.mainFrame.place(x = 0, y = 0)
        self.readPathEntry = Entry(self.mainFrame, width = 70, font = ("Arial", 12))
        self.targetPathEntry = Entry(self.mainFrame, width = 70, font = ("Arial", 12))
        self.prefixEntry = Entry(self.mainFrame, width = 50, font = ("Arial", 12))
        self.suffixEntry = Entry(self.mainFrame, width = 50, font = ("Arial", 12))
        self.readPathEntry.place(x = 200, y = 200)
        self.targetPathEntry.place(x = 200, y = 300)
        self.prefixEntry.place(x = 200, y = 400)
        self.suffixEntry.place(x = 200, y = 500)
        self.completedText = StringVar()
        self.readPathLabel = Label(self.mainFrame, text = "Path to read from:", font = ("Arial", 16))
        self.targetPathLabel = Label(self.mainFrame, text = "Path to save to:", font = ("Arial", 16))
        self.prefixLabel = Label(self.mainFrame, text = "Prefix for files:", font = ("Arial", 16))
        self.suffixLabel = Label(self.mainFrame, text = "Suffix of files:", font = ("Arial", 16))
        self.completedLabel = Label(self.mainFrame, textvariable = self.completedText, font = ("Arial", 16))
        self.readPathLabel.place(x = 0, y = 200)
        self.targetPathLabel.place(x = 0, y = 300)
        self.prefixLabel.place(x = 0, y = 400)
        self.suffixLabel.place(x = 0, y = 500)
        self.completedLabel.place(x = 100, y = 600)
        self.batchRenameBut = Button(self.mainFrame, text = "Rename", font = ("Arial", 16), command = self.batchRename)
        self.batchRenameBut.place(x = 700, y = 700)
        
        mainloop()
    
    def batchRename(self):
        readPath = str(self.readPathEntry.get())
        targetPath = str(self.targetPathEntry.get())
        prefix = str(self.prefixEntry.get())
        suffix = str(self.suffixEntry.get())

        listOfFiles = os.listdir(readPath)
        reducedTargetFiles = []
        listOfTargetPathFiles = os.listdir(targetPath)
        listOfFiles.sort()
        listOfTargetPathFiles.sort()

        if (suffix[0] == "."):
            pattern = "*" + suffix
        else:
            pattern = "*." + suffix


        for entry in listOfTargetPathFiles:
            if fnmatch.fnmatch(entry, pattern):
                reducedTargetFiles.append(entry)
        print(reducedTargetFiles)
        
        if (len(reducedTargetFiles) > 0):
            minInt = int(min(reducedTargetFiles)[-8:-4])
            maxInt = int(max(reducedTargetFiles)[-8:-4])
        else:
            maxInt = 0
            minInt = 0

        if (maxInt > 0 and minInt - 0 < len(listOfFiles) and prefix + str(maxInt).zfill(4) + "." + suffix == max(listOfTargetPathFiles)):
            i = maxInt
        else:
            i = 0

        for entry in listOfFiles:
            if fnmatch.fnmatch(entry, pattern):
                i = i+1
                output = prefix + str(i).zfill(4) + "." + suffix
                os.rename(readPath + '\\' + entry, targetPath + "\\" + output)
        self.completedText.set("Completed")

my_gui = MyGUI()
