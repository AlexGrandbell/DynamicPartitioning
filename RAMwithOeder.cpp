//
// Created by AlexGrandbell on 24-11-26.
//

#include "RAMwithOeder.h"

//初始化内存
RAMwithOeder::RAMwithOeder(int totalSize,vector<Process> processes): RAM(totalSize, processes) {
    //初始化空闲分区链表
    freePartitionSpaces.push_back(0);
}

//分配内存接口
bool RAMwithOeder::AllocateMemory(int processId) {
    //遍历空闲分区链表
    for(auto it = freePartitionSpaces.begin(); it != freePartitionSpaces.end(); it++) {
        //找到合适的分区
        if(partitionSpacesNum[*it].assignedSize >= processesNum[processId].needSize) {
            //分配内存
            partitionSpacesNum[*it].isFree = false;
            partitionSpacesNum[*it].processId = processId;
            //如果分区大小大于进程大小，分割分区，将新的分区放入map，并将编号插入链表
            if(partitionSpacesNum[*it].assignedSize > processesNum[processId].needSize) {
                int newStartAddress = partitionSpacesNum[*it].startAddress + processesNum[processId].needSize;
                int newAssignedSize = partitionSpacesNum[*it].assignedSize - processesNum[processId].needSize;
                partitionSpacesNum[*it].assignedSize = processesNum[processId].needSize;//修改原分区大小
                //新建空白分区
                PartitionSpace newPartitionSpace(newStartAddress, newAssignedSize);
                partitionSpacesNum[newPartitionSpace.partitionId] = newPartitionSpace;
                //插入分区合适位置
                auto it2 = partitionSpaces.begin();
                while(it2 != partitionSpaces.end() && partitionSpacesNum[*it2].startAddress < newPartitionSpace.startAddress) {
                    it2++;
                }
                partitionSpaces.insert(it2, newPartitionSpace.partitionId);
                //插入空闲分区链表到合适位置
                auto it3 = it;
                it3++;
                freePartitionSpaces.insert(it3, newPartitionSpace.partitionId);
                //输出分割结果
                cout<<"分割分区: 分割分区"<<*it<<"，分区"<<*it<<"大小重新分配为"<<partitionSpacesNum[*it].assignedSize<<"，新分区"<<newPartitionSpace.partitionId<<"大小为"<<newPartitionSpace.assignedSize<<endl;
            }
            //输出分配结果
            cout<<"分配进程: 分配进程"<<processId<<"到分区"<<*it<<endl;
            //从空闲分区链表中删除
            freePartitionSpaces.erase(it);
            return true;
        }
    }
    return false;
}

//运行一次减少时间接口
void RAMwithOeder::RunOnceAndRecycle() {
    bool isRecycle = false;
    //遍历所有分区
    for(auto &partitionSpace: partitionSpacesNum) {
        //如果分区被占用，减少时间
        if(!partitionSpace.second.isFree) {
            processesNum[partitionSpace.second.processId].needTime--;
            //如果时间为0，回收内存
            if(processesNum[partitionSpace.second.processId].needTime == 0) {
                cout<<"回收进程: 进程"<<partitionSpace.second.processId<<"运行完毕后回收，分区号"<<partitionSpace.second.partitionId<<"，分区大小为"<<partitionSpace.second.assignedSize<<endl;
                //修改为空白内存
                partitionSpace.second.isFree = true;
                partitionSpace.second.processId = -1;
                //插入空闲分区链表合适位置
                auto it = freePartitionSpaces.begin();
                while(it != freePartitionSpaces.end() && *it < partitionSpace.first) {
                    it++;
                }
                freePartitionSpaces.insert(it, partitionSpace.first);
                isRecycle = true;
            }
        }
    }
    //如果回收了内存
    if(isRecycle) {
        //合并空闲分区
        mergeFreePartitionSpacesOnce();
    }else{
        cout<<"此次无回收进程"<<endl;
    }
}

//合并一次连续的空闲分区
void RAMwithOeder::mergeFreePartitionSpacesOnce() {
    //遍历分区表
    for(auto it = partitionSpaces.begin(); it != partitionSpaces.end(); it++) {
        //如果是空闲分区
        if(partitionSpacesNum[*it].isFree) {
            //找到下一个分区
            auto nextIt = it;
            nextIt++;
            //如果下一个分区是空闲分区
            if(nextIt != partitionSpaces.end() && partitionSpacesNum[*nextIt].isFree) {
                //输出合并结果
                cout<<"合并分区: 合并分区"<<*it<<"和分区"<<*nextIt<<"为分区"<<*it<<endl;
                //合并分区
                partitionSpacesNum[*it].assignedSize += partitionSpacesNum[*nextIt].assignedSize;
                //删除下一个分区
                auto it2 = partitionSpacesNum.find(*nextIt);
                partitionSpacesNum.erase(it2);
                //删除空闲分区链表中的下一个分区
                freePartitionSpaces.remove(*nextIt);
                partitionSpaces.erase(nextIt);
                it--;//防止多个分区空着漏掉
            }
        }
    }
}