#include "pfm.h"
#include "stdio.h"


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
    //checks if file does not exist
    FILE * fpCreateFile = fopen(fileName.c_str(), "r");
    if (fpCreateFile== NULL) {
        //if it does create file
        fclose(fpCreateFile);
        fpCreateFile = fopen(fileName.c_str(), "w");
        if(fpCreateFile == NULL){
            //did not create file
            return -1;
        }
        return 0;
    } else {
        //don't create file
        printf("File already exists");
    }
    fclose(fpCreateFile);
    return -1;
}


RC PagedFileManager::destroyFile(const string &fileName) {
    //checks if file does not exist
    FILE * fpDestroyFile = fopen(fileName.c_str(), "r");
    if(fpDestroyFile == NULL) {
        //if it does not, do nothing
        printf("File does not exist");
        return -1;
    } else  {
        //else it destroys
        fclose(fpDestroyFile);
        remove(fileName.c_str());
    }
    return 0;
}


RC PagedFileManager::openFile(const string &fileName, FileHandle &fileHandle) {
    //opens file
    if(fileHandle.openFile != NULL){
        //file is already opened
        return -1;
    }
    //checks if it exists
    FILE * fpOpenFile = fopen(fileName.c_str(), "r+");
    if (fpOpenFile == NULL) {
        printf ("Failed to open file");
        return -1;
    } else {
        fileHandle.openFile = fpOpenFile;
        //filesize
    }

    return 0;
}


RC PagedFileManager::closeFile(FileHandle &fileHandle) {
    if(fileHandle.openFile == NULL){
        //file was never opened
        return -1;
    }
    FILE * fpCloseFile = fileHandle.openFile;
    if (fpCloseFile == NULL ){
         printf("Failed to close file");
         return -1;
    } else {
         fclose(fileHandle.openFile);
         fileHandle.openFile = NULL;
    }
    fclose(fpCloseFile);
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
    
    return -1;
}


RC FileHandle::writePage(PageNum pageNum, const void *data) {
    return -1;
}


RC FileHandle::appendPage(const void *data) {
    return -1;
}


unsigned FileHandle::getNumberOfPages() {
    return -1;
}


RC FileHandle::collectCounterValues(unsigned &readPageCount, unsigned &writePageCount, unsigned &appendPageCount) {
	return -1;
}
