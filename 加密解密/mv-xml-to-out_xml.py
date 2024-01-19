#!/usr/bin/python
import os
import sys

def copyFiles(sourceDir,  targetDir): 
    if sourceDir.find(".svn") > 0: 
        return 
    for file in os.listdir(sourceDir): 
    	
        sourceFile = os.path.join(sourceDir,  file) 
        targetFile = os.path.join(targetDir,  file) 
        print sourceFile
        print targetFile
        if os.path.isfile(sourceFile): 
        	if sourceFile.find(".xml") > 0:
	            if not os.path.exists(targetDir):
	                os.makedirs(targetDir)  
	            if not os.path.exists(targetFile) or(os.path.exists(targetFile) and (os.path.getsize(targetFile) != os.path.getsize(sourceFile))):  
	                    open(targetFile, "wb").write(open(sourceFile, "rb").read()) 
        if os.path.isdir(sourceFile): 
            First_Directory = False 
            copyFiles(sourceFile, targetFile)

copyFiles("./config-game","./out_xml")