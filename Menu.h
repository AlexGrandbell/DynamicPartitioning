//
// Created by AlexGrandbell on 24-11-27.
//

#ifndef DYNAMICPARTITIONING_MENU_H
#define DYNAMICPARTITIONING_MENU_H

#include <iostream>
#include <fstream>
#include "CPU.h"
#include "RAMwithFirstFit.h"
#include "RAMwithBestFit.h"
#include "RAMwithWorstFit.h"

using namespace std;

//菜单类
class Menu {
public:
    vector<Process> processes;//进程列表
    vector<Process> defaultProcesses;//默认进程列表
    int mode;//1-最先适应法 2-最佳适应法 3-最坏适应法
    int dataMode;//1-默认数据 2-自定义数据 3-文件数据
    int RAMSize;//内存大小

    //构造函数
    Menu():mode(1),RAMSize(256),dataMode(1) {
        //初始化内存
        Process processor1 =  Process(8,0,5);
        Process processor2 =  Process(16,0,4);
        Process processor3 =  Process(64,0,1);
        Process processor4 =  Process(124,0,4);
        Process processor5 =  Process(7,1,5);
        Process processor6 =  Process(16,2,5);
        Process processor7 =  Process(16,10,5);

        defaultProcesses = {processor1, processor2, processor3, processor4, processor5, processor6, processor7};
        processes=defaultProcesses;
    }

    void PrintMenu();
private:
    void chooseMode();//选择三种算法
    void chooseData();//选择数据

    void loadFromDefault();//从默认进程列表加载
    void loadFromInput();//从输入加载
    void loadFromFile();//从文件加载

    void setRAMSize();//设置内存大小

    void run(bool toEnd= true);//运行
};


#endif //DYNAMICPARTITIONING_MENU_H
