#encoding=utf-8
import os,sys
import md5
import hashlib
 
########################################
def GetAllFilePath(path):
    try:    #如果path是一个文件的完整名称，os.listdir会抛出错误
        fl=os.listdir(path)
    except Exception as e:
        fl=[]
    finally:
        return fl
######################################
def Get_Md5_Of_File(filename):
    if not os.path.isfile(filename):
        return
    myhash = hashlib.md5()
    f = file(filename,'rb')
    while True:
        b = f.read(8096)
        if not b :
            break
        myhash.update(b)
    f.close()
    return myhash.hexdigest()
######################################## 
def getallfile(path):
		allfile=[]
		fl=GetAllFilePath(path)
		if len(fl)!=0:
				fl=list(map(lambda x:path+'\\'+x,fl))
				allfile=allfile+fl
				for f in fl:
						allfile=allfile+getallfile(f)
		return allfile
########################################################
def save_to_file(file_name, contents):
    fh = open(file_name, 'w')
    fh.write(contents)
    fh.close()
########################################
def main():
		print "###################################"
		print 'create begin.......'
		#print sys.argv[0]
		#print sys.argv[1]
		#print sys.argv[2]
		#print sys.argv[3]
		#1.2.0
		#result= getallfile('.\Resources')
		result= getallfile(sys.argv[1])
		md5str = ''
		xmltitle='<?xml version="1.0" encoding="UTF-8"?>\r\n<res svnversion="6510" version="'+ sys.argv[3] +'" >\r\n'
		xmlend = '</res>'
		xmlRowbegin = '<file name="'
		xmlRowMid = '" md5="'
		xmlRowEnd = '" />'
		for fpath in result:
				if not os.path.isfile(fpath):
						continue
				#print(fpath)
				#print(Get_Md5_Of_File(fpath))
				pathname = str(fpath)[len(sys.argv[1]):]
				md5str = md5str + xmlRowbegin + pathname + xmlRowMid + str(Get_Md5_Of_File(fpath)) + xmlRowEnd + '\n'
		#print(md5str)
		save_to_file(sys.argv[2]+'.xml',xmltitle + md5str +'\r\n' + xmlend)
		print '#####################################'
		print 'create md5 xml success!'
#print Get_Md5_Of_Folder(os.getcwd())
main()








