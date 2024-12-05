//
// Created by AlexGrandbell on 24-11-27.
//

#ifndef DYNAMICPARTITIONING_RAMWITHWORSTFIT_H
#define DYNAMICPARTITIONING_RAMWITHWORSTFIT_H

#include "RAM.h"

//最坏适应法比较器
struct WorstSizeComparator {
    const map<int, PartitionSpace>* comPartitionSpaceNum;

    WorstSizeComparator(const std::map<int, PartitionSpace>& partitionSpacesMap): comPartitionSpaceNum(&partitionSpacesMap) {}

    bool operator()(int lhs, int rhs) const  {
        return comPartitionSpaceNum->at(lhs).assignedSize < comPartitionSpaceNum->at(rhs).assignedSize;
    }
};

//内存类，按照最坏适应法分配
class RAMwithWorstFit: public RAM {
public:
    RAMwithWorstFit(int totalSize, vector<Process> processes): RAM(totalSize, processes) {
        //初始化空闲分区链表
        partitionFreeSpaces = priority_queue<int, vector<int>, function<bool(int, int)>>([this](int lhs, int rhs) { return WorstSizeComparator(partitionSpacesMap)(lhs, rhs); });
        partitionFreeSpaces.push(0);
    }
};


#endif //DYNAMICPARTITIONING_RAMWITHWORSTFIT_H
