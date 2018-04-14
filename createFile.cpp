#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

int createFile(const string &fileName)
{
    ifstream file_exists;
    file_exists.open(fileName);
    if(file_exists.is_open() == false){
     	cout << "file doesn't exist:";
        ofstream file;
        file.open(fileName);
            if(file.is_open() == false){
            cout << "file " << fileName << " is unsuccessfully created\n";
            return -1;
        }
        else{
            cout << "file " << fileName << " is successfully created\n";
        }
        file.close(); 
    }
    else{
        cout << "file exists: canceling *createFile* operation\n";
    }
    return 0;
}

int destroyFile(const string &fileName)
{

    if( remove(fileName.c_str()) !=0 ){
        cout << "failed to delete file:" << fileName;
    }
    else
    cout << "File "<< fileName <<" successfully deleted\n";
    return 0;
}

/*int openFile(const string &fileName, FileHandle &fileHandle){
    fstream file;
    file.open(fileName, fileHandle )
    return 0;
}*/
/*closeFile(FileHandle &fileHandle)
{
    return 0;
}*/

int main(){
    createFile("boom_boom_boom");
    createFile("lolcats");
    destroyFile("boom_boom_boom");
    //openFile("boom_boom_boom", ios::out);
    return 0;
}