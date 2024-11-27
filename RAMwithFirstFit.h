//
// Created by AlexGrandbell on 24-11-26.
//

#ifndef DYNAMICPARTITIONING_RAMWITHFIRSTFIT_H
#define DYNAMICPARTITIONING_RAMWITHFIRSTFIT_H

#include "RAM.h"

//内存类，按照最先适应法分配
class RAMwithFirstFit: public RAM {
public:
    RAMwithFirstFit(int totalSize, vector<Process> processes): RAM(totalSize, processes) {
        //初始化空闲分区链表
        partitionFreeSpaces = priority_queue<int, vector<int>, function<bool(int, int)>>([this](int lhs, int rhs) { return StartAddressComparator(partitionSpacesMap)(lhs, rhs); });
        partitionFreeSpaces.push(0);
    }
};

#endif //DYNAMICPARTITIONING_RAMWITHFIRSTFIT_H
