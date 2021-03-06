#include "pfm.h"
#include "stdio.h"
#include <sys/stat.h>
#include <string>
#include <iostream>
PagedFileManager* PagedFileManager::_pf_manager = 0;

PagedFileManager* PagedFileManager::instance() {
    if(!_pf_manager)
        _pf_manager = new PagedFileManager();

    return _pf_manager;
}


PagedFileManager::PagedFileManager() {
}


PagedFileManager::~PagedFileManager() {
}


RC PagedFileManager::createFile(const string &fileName) {
    struct stat info;
    if(stat(fileName.c_str(), &info) == 0){
       return -1;
    }

    FILE* fpCreateFile = fopen(fileName.c_str(), "w");
    if(fpCreateFile == NULL){
         return -1;
    }
    fclose(fpCreateFile);
    return 0;
}


RC PagedFileManager::destroyFile(const string &fileName) {
    struct stat info;
    if(stat(fileName.c_str(), &info) != 0){
        return -1;
    }
    if( remove(fileName.c_str()) !=0 ){
        return -1;
    }
    return 0;
    
}

RC PagedFileManager::openFile(const string &fileName, FileHandle &fileHandle) {
    struct stat info;
    if(stat(fileName.c_str(), &info) != 0){
        return -1;
    }

    if(fileHandle.openFile != NULL){
        return -1;
    }
    
    fileHandle.openFile = fopen(fileName.c_str(), "rb+");
    if(fileHandle.openFile == NULL){
       return -1;
    }

    fileHandle.fileSize = info.st_size;
    return 0;
}


RC PagedFileManager::closeFile(FileHandle &fileHandle) {
    if(fileHandle.openFile == NULL){
        return -1;
    }
    
    fclose(fileHandle.openFile);
    return 0;
}


FileHandle::FileHandle() {
    readPageCounter = 0;
    writePageCounter = 0;
    appendPageCounter = 0;
    fileSize = 0;
    openFile = NULL;
}


FileHandle::~FileHandle() {
    
}


RC FileHandle::readPage(PageNum pageNum, void *data) {
    //We expect pages 0-9 for 10 pages
    unsigned int pos = pageNum*PAGE_SIZE;
    unsigned int totalPages = fileSize/PAGE_SIZE;
    //cout <<"total fileSize is " << fileSize <<endl;
    //cout <<"total Page is " << totalPages <<endl;
    if(pageNum >= totalPages){
        return -1;
    }
 
    fseek(openFile, pos, SEEK_SET);
    fread(data, sizeof(char), PAGE_SIZE, openFile);
    
    readPageCounter += 1;
    return 0;
}


RC FileHandle::writePage(PageNum pageNum, const void *data) {
    unsigned int pos = pageNum*PAGE_SIZE;
    unsigned int totalPages = fileSize/PAGE_SIZE;
    //cout <<"total fileSize is " << fileSize <<endl;
    //cout <<"total Page is " << totalPages <<endl;
    if(pageNum >= totalPages){
        return -1;
    }
    fseek(openFile, pos, SEEK_SET);
    fwrite(data, sizeof(char), PAGE_SIZE, openFile);
    writePageCounter +=1;

    return 0;
}


RC FileHandle::appendPage(const void *data) {
    fseek(openFile, 0, SEEK_END);
    
    fwrite(data, sizeof(char), PAGE_SIZE, openFile);

    fflush(openFile);
    
    fileSize += PAGE_SIZE;
    
    cout <<"file size is " << fileSize <<endl;
    
    appendPageCounter += 1;
    return 0;
}


unsigned FileHandle::getNumberOfPages() {
    return fileSize/PAGE_SIZE;
}


RC FileHandle::collectCounterValues(unsigned &readPageCount, unsigned &writePageCount, unsigned &appendPageCount) {
	readPageCount = readPageCounter;
        writePageCount = writePageCounter;
        appendPageCount = appendPageCounter;
        return 0;
}
