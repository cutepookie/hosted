#!/usr/bin/python
import os
import sys
import shutil

def copyFiles(sourceDir,  targetDir): 
    for file in os.listdir(sourceDir): 


        sourceFile = os.path.join(sourceDir,  file) 
        targetFile = os.path.join(targetDir,  file) 


        #print sourceFile
        #print targetFile
        if os.path.isfile(sourceFile): 
            if sourceFile.find(".cb") > 0:
                if not os.path.exists(targetDir):
                    os.makedirs(targetDir)  
                print targetFile
                if not os.path.exists(targetFile) or(os.path.exists(targetFile) and (os.path.getsize(targetFile) != os.path.getsize(sourceFile))):  
                    open(targetFile, "wb").write(open(sourceFile, "rb").read()) 
                os.system("rm " + sourceFile )
        
        if os.path.isdir(sourceFile): 
            copyFiles(sourceFile,  targetFile)


copyFiles("./config","../ProjectTK/Resources/config")
#copyFiles("./config","./out")