//
// Created by AlexGrandbell on 24-11-27.
//

#ifndef DYNAMICPARTITIONING_RAMWITHBESTFIT_H
#define DYNAMICPARTITIONING_RAMWITHBESTFIT_H

#include "RAM.h"

//最佳适应法比较器
struct BestComparator{
    const map<int, PartitionSpace>* comPartitionSpaceNum;

    BestComparator(const std::map<int, PartitionSpace>& partitionSpacesMap): comPartitionSpaceNum(&partitionSpacesMap) {}

    bool operator()(int lhs, int rhs) const {
        return comPartitionSpaceNum->at(lhs).assignedSize > comPartitionSpaceNum->at(rhs).assignedSize;
    }
};

//内存类，按照最佳适应法分配
class RAMwithBestFit: public RAM {
public:
    RAMwithBestFit(int totalSize, vector<Process> processes): RAM(totalSize, processes) {
        //初始化空闲分区链表
        partitionFreeSpaces = priority_queue<int, vector<int>, function<bool(int, int)>>(
                [this](int lhs, int rhs) { return BestComparator(partitionSpacesMap)(lhs, rhs); }
        );
        partitionFreeSpaces.push(0);
    }
};

#endif //DYNAMICPARTITIONING_RAMWITHBESTFIT_H
