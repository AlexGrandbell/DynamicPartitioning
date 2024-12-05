//
// Created by AlexGrandbell on 24-11-26.
//

#ifndef DYNAMICPARTITIONING_RAMWITHFIRSTFIT_H
#define DYNAMICPARTITIONING_RAMWITHFIRSTFIT_H

#include "RAM.h"

//最先适应法比较器
struct StartAddressComparator {
    const map<int, PartitionSpace>* comPartitionSpaceNum;

    StartAddressComparator(const std::map<int, PartitionSpace>& partitionSpacesMap): comPartitionSpaceNum(&partitionSpacesMap) {}

    bool operator()(int lhs, int rhs) const {
        return comPartitionSpaceNum->at(lhs).startAddress > comPartitionSpaceNum->at(rhs).startAddress;
    }
};

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
