//
// Created by AlexGrandbell on 24-11-26.
//

#include "RAM.h"

//显示内存分配状态
void RAM::ShowMemoryStatus() {
        cout<<"分区编号:\t";
        for(auto &partitionSpace: partitionSpaces) {
//            cout<<partitionSpacesNum[partitionSpace].partitionId<<"\t";
            cout<<partitionSpace<<"\t";
        }
        cout<<"\n分区大小:\t";
        for(auto &partitionSpace: partitionSpaces) {
            cout<<partitionSpacesNum[partitionSpace].assignedSize<<"\t";
        }
        cout<<"\n分区起始:\t";
        for(auto &partitionSpace: partitionSpaces) {
            cout<<partitionSpacesNum[partitionSpace].startAddress<<"\t";
        }
        cout<<"\n分区结束:\t";
        for(auto &partitionSpace: partitionSpaces) {
            cout<<partitionSpacesNum[partitionSpace].startAddress + partitionSpacesNum[partitionSpace].assignedSize-1<<"\t";
        }
        cout<<"\n分区状态:\t";
        for(auto &partitionSpace: partitionSpaces) {
            cout<<(partitionSpacesNum[partitionSpace].isFree ? "空":"有" )<<"\t";
        }
        cout<<"\n进程编号:\t";
        for(auto &partitionSpace: partitionSpaces) {
            if (partitionSpacesNum[partitionSpace].isFree) {
                cout<<"-\t";
            }else{
                cout<<partitionSpacesNum[partitionSpace].processId<<"\t";
            }
        }
        cout<<"\n进程剩余时间:\t";
        for(auto &partitionSpace: partitionSpaces) {
            if (partitionSpacesNum[partitionSpace].isFree) {
                cout<<"-\t";
            }else{
                cout<<processesNum[partitionSpacesNum[partitionSpace].processId].needTime<<"\t";
            }
        }
        cout<<"\n等待进程数量:\t";
        cout<<waitingProcesses.size()<<"\t";
        cout<<endl;
}