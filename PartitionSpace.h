//
// Created by AlexGrandbell on 24-11-26.
//

#ifndef DYNAMICPARTITIONING_PARTITIONSPACE_H
#define DYNAMICPARTITIONING_PARTITIONSPACE_H

//分区空间类
class PartitionSpace {
public:
    int partitionId; //分区id
    static int id; //静态变量，用于生成分区id

    int startAddress; //起始地址
    int assignedSize; //分区大小
    bool isFree; //是否空闲
    int processId; //进程id

    PartitionSpace(int startAddress, int assignedSize): startAddress(startAddress), assignedSize(assignedSize), isFree(true), processId(-1){
        partitionId = id++;
    }
    //新的内存
    PartitionSpace(int startAddress, int assignedSize, bool isFirst): startAddress(startAddress), assignedSize(assignedSize), isFree(true), processId(-1){
        id=0;
        partitionId = id++;
    }
    PartitionSpace(): startAddress(0), assignedSize(0), isFree(true), processId(-1){
        partitionId = 0;
    }
    //重载比较内存大小运算符，以便在优先队列中使用
    bool operator>(const PartitionSpace &other) const {
        return assignedSize > other.assignedSize;
    }
    bool operator<(const PartitionSpace &other) const {
        return assignedSize < other.assignedSize;
    }
};


#endif //DYNAMICPARTITIONING_PARTITIONSPACE_H
