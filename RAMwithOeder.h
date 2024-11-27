//
// Created by AlexGrandbell on 24-11-26.
//

#ifndef DYNAMICPARTITIONING_RAMWITHOEDER_H
#define DYNAMICPARTITIONING_RAMWITHOEDER_H

#include "RAM.h"

//内存类，按照最先适应法分配
class RAMwithOeder: public RAM {
public:
    list<int> freePartitionSpaces;//空闲分区链表

    RAMwithOeder(int totalSize,vector<Process> processes);

    //分配内存接口
//    bool AllocateMemory(int processId) override;
    //运行一次减少时间接口并回收结束的内存
//    void RunOnceAndRecycle() override;

//protected:
    //合并一次空闲分区
//    void mergeFreePartitionSpacesOnce() override;
};


#endif //DYNAMICPARTITIONING_RAMWITHOEDER_H
