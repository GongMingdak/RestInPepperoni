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
    FILE * fpCreateFile = fopen(fileName.c_str, "r");
    if (fpCreateFile== NULL) {
        fclose(fpCreateFile);
        file = fopen(fileName.c_str, "w");
    } else { 
        printf(fileName.c_str + " already exists");
    }
    fclose(fileName.c_str);
    return 0;
}


RC PagedFileManager::destroyFile(const string &fileName) {
    FILE * fpDestroyFile = openFile(fileName.c_str, "r");
    if(fpDestroyFile == NULL) {
        fprint (fileName.c_str + " does not exist");
    } else  {
        fclose(fpDestroyFile);
        remove(fileName.c_str);
    }
    return 0;
}


RC PagedFileManager::openFile(const string &fileName, FileHandle &fileHandle) {
    FILE * fpOpenFile = fopen(fileName.c_str, fileHandle);
    if (fpOpenFile == NULL) {
        fprint ("Failed to open " + fileName.c_str);
        return -1;
    }

    return 0;
}


RC PagedFileManager::closeFile(FileHandle &fileHandle) {
    FILE * fpCloseFile = openFile(fileHandle.c_str, "r");
    if (fpCloseFile == NULL ){
         fprint("Failed to close " + fileHandle);
         return -1;
    } else {
         fclose(fileHandle);
    }
    return 0;
}


FileHandle::FileHandle() {
	readPageCounter = 0;
	writePageCounter = 0;
	appendPageCounter = 0;
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
