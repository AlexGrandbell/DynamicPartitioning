//
// Created by AlexGrandbell on 24-11-26.
//

#include "RAM.h"

//显示内存分配状态
void RAM::ShowMemoryStatus() {
    for(auto &partitionSpace: partitionSpaces) {
        cout<<"分区id："<<partitionSpacesNum[partitionSpace].partitionId<<endl;
        cout<<"起始地址："<<partitionSpacesNum[partitionSpace].startAddress<<endl;
        cout<<"分区大小："<<partitionSpacesNum[partitionSpace].assignedSize<<endl;
        cout<<"是否空闲："<<(partitionSpacesNum[partitionSpace].isFree ? "是" : "否")<<endl;
        if (!partitionSpacesNum[partitionSpace].isFree) {
            cout<<"进程id："<<partitionSpacesNum[partitionSpace].processId<<endl;
        }
        cout<<endl;
    }
}