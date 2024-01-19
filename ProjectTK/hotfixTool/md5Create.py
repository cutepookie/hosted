# encoding=utf-8
import hashlib
import json
import os
import shutil
import xml.dom.minidom


########################################
def mycopyfile(srcfile, dstfile):
    print srcfile
    print dstfile
    if not os.path.isfile(srcfile):
        print "%s not exist!" % (srcfile)
    else:
        fpath, fname = os.path.split(dstfile)  # 分离文件名和路径
        if not os.path.exists(fpath):
            os.makedirs(fpath)  # 创建路径
        shutil.copyfile(srcfile, dstfile)  # 复制文件
        print "copy %s -> %s" % (srcfile, dstfile)


########################################
def GetAllFilePath(path):
    try:  # 如果path是一个文件的完整名称，os.listdir会抛出错误
        fl = os.listdir(path)
    except Exception as e:
        fl = []
    finally:
        return fl


######################################
def Get_Md5_Of_File(filename):
    if not os.path.isfile(filename):
        return
    myhash = hashlib.md5()
    f = file(filename, 'rb')
    while True:
        b = f.read(8096)
        if not b:
            break
        myhash.update(b)
    f.close()
    return myhash.hexdigest()


########################################
def getallfile(path):
    allfile = []
    fl = GetAllFilePath(path)
    if len(fl) != 0:
        fl = list(map(lambda x: path + '\\' + x, fl))
        allfile = allfile + fl
        for f in fl:
            allfile = allfile + getallfile(f)
    return allfile


########################################################
def save_to_file(file_name, contents):
    fh = open(file_name, 'w')
    fh.write(contents)
    fh.close()


########################################
# 字节bytes转化kb\m\g
def formatSize(bytes):
    try:
        bytes = float(bytes)
        kb = bytes / 1024
    except:
        print("传入的字节格式不对")
        return "Error"

    return "%f" % (kb)


########################################
# 获取文件大小
def getDocSize(path):
    try:
        size = os.path.getsize(path)
        return formatSize(size)
    except Exception as err:
        print(err)


########################################
def main():
    print "###################################"
    print 'create begin.......'

    myArg1 = "..\\Resources"

    myArg2 = "res"
    myArg3 = "1.2.0"
    result = getallfile(myArg1)
    md5str = ''
    xmltitle = '<?xml version="1.0" encoding="UTF-8"?>\r\n<res svnversion="6510" version="' + myArg3 + '" >\r\n'
    xmlend = '</res>'
    xmlRowbegin = '<file name="'
    xmlRowMid = '" md5="'
    xmlRowEnd = '" />'
    jsonFileName = "serverVersion.json"
    with open(jsonFileName) as load_f:
        load_dict = json.load(load_f)
    serverVersion = load_dict["serverVersion"]
    perSize = load_dict["perSize"]
    lastVersionStr = serverVersion[len(serverVersion) - 2]
    versionStr = serverVersion[len(serverVersion) - 1]
    if os.path.exists(myArg2 + versionStr + '.xml'):
        print "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
        print "fix serverVersion.json[Add serverVersion]"
        print "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
        raw_input("Press <enter>")
        return

    isExistsLastVersion = os.path.exists(myArg2 + lastVersionStr + '.xml')
    list = []
    for num in range(0,len(serverVersion)-1):
        lastVersionStr2 = serverVersion[num]
        xmlDic = dict()

        if isExistsLastVersion:
            # 打开xml文档
            dom = xml.dom.minidom.parse(myArg2 + lastVersionStr2 + '.xml')
            # 得到文档元素对象
            root = dom.documentElement
            bb = root.getElementsByTagName('file')
            for _node in bb:
                xmlDic[_node.getAttribute("name")] = _node.getAttribute("md5")
            list.append(xmlDic)
    
    
    for fpath in result:
        if not os.path.isfile(fpath):
            continue
        pathname = str(fpath)[len(myArg1):]
        _md5 = str(Get_Md5_Of_File(fpath))

        num2 = 0
        isHaveFile = False
        for num2 in reversed(range(0,len(serverVersion)-1)):
            isBreak = False
            for key in list[num2]:
                if key == pathname:
                    isHaveFile = True
                    if list[num2][key] != _md5:
                        mycopyfile(fpath, fpath.replace("Resources", "out"))
                        md5str = md5str + xmlRowbegin + pathname + xmlRowMid + _md5 + xmlRowEnd + '\n'
                    else:
                        isBreak = True
                    break
            if isBreak:
                break

        #如果都没有找到说明是新增的文件
        if not isHaveFile:
            md5str = md5str + xmlRowbegin + pathname + xmlRowMid + _md5 + xmlRowEnd + '\n'
            if isExistsLastVersion:
                mycopyfile(fpath, fpath.replace("Resources", "out"))
            
    if isExistsLastVersion:
        zip_command = r"C:\Haozip\HaoZipC.exe  a  -tzip %s.zip ..\out\*" % (myArg2 + versionStr)
        if os.system(zip_command) == 0:
            print("Successful!")
            if len(perSize) == len(serverVersion):
                perSize[len(perSize) - 1] = getDocSize(r"%s.zip" % (myArg2 + versionStr))
            else:
                perSize.append(getDocSize(r"%s.zip" % (myArg2 + versionStr)))
            with open(jsonFileName, "w") as dump_f:
                json.dump(load_dict, dump_f)
        shutil.rmtree(r"..\out")      

    f= open(myArg2 + versionStr + '.xml',"w+")
    f.write(xmltitle + md5str + '\r\n' + xmlend)
    f.close()

    print '#####################################'
    print 'create md5 xml success!'


main()
