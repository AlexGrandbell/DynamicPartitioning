//
// Created by AlexGrandbell on 24-11-27.
//

#ifndef DYNAMICPARTITIONING_RAMWITHWORST_H
#define DYNAMICPARTITIONING_RAMWITHWORST_H

#include "RAM.h"

//内存类，按照最坏适应法分配
class RAMwithWorst: public RAM {
public:
    RAMwithWorst(int totalSize,vector<Process> processes): RAM(totalSize, processes) {
        //初始化空闲分区链表
        partitionFreeSpaces = priority_queue<int, vector<int>, function<bool(int, int)>>([this](int lhs, int rhs) { return WorstSizeComparator(partitionSpacesMap)(lhs, rhs); });
        partitionFreeSpaces.push(0);
//        PartitionSpace::id = 0;
    }
};


#endif //DYNAMICPARTITIONING_RAMWITHWORST_H
