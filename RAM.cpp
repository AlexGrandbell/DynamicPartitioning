//
// Created by AlexGrandbell on 24-11-26.
//

#include "RAM.h"

//显示内存分配状态
void RAM::ShowMemoryStatus() {
        cout<<"分区编号:\t";
        for(auto &partitionSpace: partitionAllSpaces) {
            cout<<partitionSpace<<"\t";
        }
        cout<<"\n分区大小:\t";
        for(auto &partitionSpace: partitionAllSpaces) {
            cout << partitionSpacesMap[partitionSpace].assignedSize << "\t";
        }
        cout<<"\n分区起始:\t";
        for(auto &partitionSpace: partitionAllSpaces) {
            cout << partitionSpacesMap[partitionSpace].startAddress << "\t";
        }
        cout<<"\n分区结束:\t";
        for(auto &partitionSpace: partitionAllSpaces) {
            cout << partitionSpacesMap[partitionSpace].startAddress + partitionSpacesMap[partitionSpace].assignedSize - 1 << "\t";
        }
        cout<<"\n分区状态:\t";
        for(auto &partitionSpace: partitionAllSpaces) {
            cout << (partitionSpacesMap[partitionSpace].isFree ? "空" : "有" ) << "\t";
        }
        cout<<"\n进程编号:\t";
        for(auto &partitionSpace: partitionAllSpaces) {
            if (partitionSpacesMap[partitionSpace].isFree) {
                cout<<"-\t";
            }else{
                cout << partitionSpacesMap[partitionSpace].processId << "\t";
            }
        }
        cout<<"\n进程剩余时间:\t";
        for(auto &partitionSpace: partitionAllSpaces) {
            if (partitionSpacesMap[partitionSpace].isFree) {
                cout<<"-\t";
            }else{
                cout << processesMap[partitionSpacesMap[partitionSpace].processId].needTime << "\t";
            }
        }
        cout<<"\n等待进程数量: "<<waitingProcesses.size()<<endl;
        cout<<"未到来进程数量: "<<allProcesses.size()<<endl;
}

//分配内存接口
bool RAM::AllocateMemory(int processId) {
    //遍历空闲分区队列，找到合适的分区。不满足的先放入临时优先队列保存
    while(!partitionFreeSpaces.empty()) {
        int partitionId = partitionFreeSpaces.top();
        partitionFreeSpaces.pop();
        if(partitionSpacesMap[partitionId].assignedSize >= processesMap[processId].needSize) {
            //分配内存
            partitionSpacesMap[partitionId].isFree = false;
            partitionSpacesMap[partitionId].processId = processId;
            //如果分区大小大于进程大小，分割分区，将新的分区放入map，并将编号插入链表
            if (partitionSpacesMap[partitionId].assignedSize > processesMap[processId].needSize) {
                int newStartAddress = partitionSpacesMap[partitionId].startAddress + processesMap[processId].needSize;
                int newAssignedSize = partitionSpacesMap[partitionId].assignedSize - processesMap[processId].needSize;
                partitionSpacesMap[partitionId].assignedSize = processesMap[processId].needSize;//修改原分区大小
                //新建空白分区
                PartitionSpace newPartitionSpace(newStartAddress, newAssignedSize);
                partitionSpacesMap[newPartitionSpace.partitionId] = newPartitionSpace;
                //插入所有分区链表合适位置
                auto it2 = partitionAllSpaces.begin();
                while (it2 != partitionAllSpaces.end()&& partitionSpacesMap[*it2].startAddress < newPartitionSpace.startAddress) {
                    it2++;
                }
                partitionAllSpaces.insert(it2, newPartitionSpace.partitionId);
                //输出分割结果
                cout << "分割分区: 分割分区" << partitionId << "，分区" << partitionId << "大小重新分配为"<< partitionSpacesMap[partitionId].assignedSize << "，新分区" << newPartitionSpace.partitionId<< "大小为" << newPartitionSpace.assignedSize << endl;

            }
            //输出分配结果
            cout << "分配进程: 分配进程" << processId << "到分区" << partitionId << endl;
            //遍历所有map，找到空闲分区并放入优先队列
            //弹出所有
            while (!partitionFreeSpaces.empty()) {
                partitionFreeSpaces.pop();
            }
            for(auto &partitionSpace: partitionSpacesMap) {
                if(partitionSpace.second.isFree) {
                    partitionFreeSpaces.push(partitionSpace.first);
                }
            }
            return true;
        }
    }
    //遍历所有map，找到空闲分区并放入优先队列
    //弹出所有
    while (!partitionFreeSpaces.empty()) {
        partitionFreeSpaces.pop();
    }
    for(auto &partitionSpace: partitionSpacesMap) {
        if(partitionSpace.second.isFree) {
            partitionFreeSpaces.push(partitionSpace.first);
        }
    }
    return false;
}

//回收并合并一次空闲分区
void RAM::RunOnceAndRecycle() {
    bool isRecycle = false;
    //遍历所有分区
    for(auto &partitionSpace: partitionSpacesMap) {
        //如果分区被占用，减少时间
        if(!partitionSpace.second.isFree) {
            processesMap[partitionSpace.second.processId].needTime--;
            //如果时间为0，回收内存
            if(processesMap[partitionSpace.second.processId].needTime == 0) {
                cout<<"回收进程: 进程"<<partitionSpace.second.processId<<"运行完毕后回收，分区号"<<partitionSpace.second.partitionId<<"，分区大小为"<<partitionSpace.second.assignedSize<<endl;
                //修改为空白内存
                partitionSpace.second.isFree = true;
                partitionSpace.second.processId = -1;
                //直接插入空闲分区优先队列合适位置
                partitionFreeSpaces.push(partitionSpace.second.partitionId);
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
void RAM::mergeFreePartitionSpacesOnce() {
    //弹出所有
    while (!partitionFreeSpaces.empty()) {
        partitionFreeSpaces.pop();
    }
    //遍历分区表
    for(auto it = partitionAllSpaces.begin(); it != partitionAllSpaces.end(); it++) {
        //如果是空闲分区
        if(partitionSpacesMap[*it].isFree) {
            //找到下一个分区
            auto nextIt = it;
            nextIt++;
            //如果下一个分区是空闲分区
            if(nextIt != partitionAllSpaces.end() && partitionSpacesMap[*nextIt].isFree) {
                //输出合并结果
                cout<<"合并分区: 合并分区"<<*it<<"和分区"<<*nextIt<<"为分区"<<*it<<endl;
                //合并分区
                partitionSpacesMap[*it].assignedSize += partitionSpacesMap[*nextIt].assignedSize;

                //删除下一个分区
                auto it2 = partitionSpacesMap.find(*nextIt);
                partitionSpacesMap.erase(it2);
                partitionAllSpaces.erase(nextIt);
                it--;//防止多个分区空着漏掉
            }
        }
    }
    //遍历所有map，找到空闲分区并放入优先队列
    for(auto &partitionSpace: partitionSpacesMap) {
        if(partitionSpace.second.isFree) {
            partitionFreeSpaces.push(partitionSpace.first);
        }
    }
}