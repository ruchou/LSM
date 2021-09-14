//
// Created by YanRu Jhou on 2021/9/9.
//

#ifndef LSM_FILESYSTEM_H
#define LSM_FILESYSTEM_H

#include <tuple>
#include <vector>
#include <cassert>

#include "Utilities/ArrayBasic.h"

class FileT {
public:
    std::vector<std::tuple<int, int>> *ram;
    std::vector<std::tuple<int, int>> *disk_cont;
    bool is_new; //indicates whether file has not yet been written
    bool is_open; // indicates whether RAM disk has been populated
    int size; //the size of the file
};

void FilePure(FileT *f, bool isn, bool iso, int len);

void File(FileT *f, bool isn, bool iso, int len);

// Delete the given file
void deleteFile(FileT *f);

// Create a new file of the given size
FileT *createFile(int len);

//Close the given file
void closeFile(FileT *f);

// Open the given file
void openFile(FileT *f);

// Write the contents of the memory-mapped RAM disk to the file system
void writeFile(FileT *f);

// Test whether file is open
bool isOpenFile(FileT *f);

#endif //LSM_FILESYSTEM_H
