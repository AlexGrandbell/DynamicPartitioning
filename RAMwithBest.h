//
// Created by AlexGrandbell on 24-11-27.
//

#ifndef DYNAMICPARTITIONING_RAMWITHBEST_H
#define DYNAMICPARTITIONING_RAMWITHBEST_H

#include "RAM.h"

//内存类，按照最佳适应法分配
class RAMwithBest: public RAM {
public:
    RAMwithBest(int totalSize,vector<Process> processes): RAM(totalSize, processes) {
        //初始化空闲分区链表
        partitionFreeSpaces = priority_queue<int, vector<int>, function<bool(int, int)>>(
                [this](int lhs, int rhs) { return BestComparator(partitionSpacesMap)(lhs, rhs); }
        );
        partitionFreeSpaces.push(0);
    }
};

#endif //DYNAMICPARTITIONING_RAMWITHBEST_H
