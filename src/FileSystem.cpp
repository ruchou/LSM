//
// Created by YanRu Jhou on 2021/9/9.
//

#include "../include/FileSystem.h"
#include <iostream>

void FilePure(FileT *f, bool isn, bool iso, int len) {
    assert(
            len == f->size
            && len == f->ram->size()
            && isn == f->is_new && iso == f->is_open
            && len == f->disk_cont->size()
    );
}

void File(FileT *f, bool isn, bool iso, int len) {
    assert(
            f != nullptr
            && f->disk_cont != nullptr
            && f->ram != nullptr
    );

    FilePure(f, isn, iso, len);
}

void deleteFile(FileT *f) {
    File(f, f->is_new, f->is_open, f->size);

    delete f->ram;
    delete f->disk_cont;
    delete f;
}

FileT *createFile(int len) {
    auto *f = new FileT();
    f->ram = new std::vector<std::tuple<int, int>>(len, std::make_tuple(-1, -1));

    f->disk_cont = new std::vector<std::tuple<int, int>>(len, std::make_tuple(-1, -1));

    f->is_open = false;
    f->is_new = true;
    f->size = len;

    File(f, true, false, len);
    return f;
}

void closeFile(FileT *f) {
    assert(f->size >= 0);
    File(f, f->is_new, true, f->size);

    f->is_open = false;

    File(f, f->is_new, false, f->size);
    //TODO ensures f.disk_cont.map == old(f.disk_cont.map)
}


void openFile(FileT *f) {
    File(f, f->is_new, false, f->size);

    arr_copy(f->disk_cont, f->ram, 0, 0, f->size);
    f->is_open = true;

    File(f, f->is_new, true, f->size);
}

void writeFile(FileT *f) {
    File(f, true, true, f->size);

    arr_copy(f->ram, f->disk_cont, 0, 0, f->size);
    f->is_new = false;

    File(f, false, true, f->size);

//TODO
//    ensures f.ram.map == old(f.ram.map)
//    ensures f.disk_cont.map == f.ram.map

}

bool isOpenFile(FileT *f) {
    File(f, f->is_new, f->is_open, f->size);

    bool res = f->is_open;

    File(f, f->is_new, f->is_open, f->size);
    //TODO
    // ensures iso ==> f.ram.map == old(f.ram.map)
    //  ensures f.disk_cont.map == old(f.disk_cont.map)
    assert(res == f->is_open);

    return res;
}






