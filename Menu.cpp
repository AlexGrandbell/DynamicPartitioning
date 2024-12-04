//
// Created by AlexGrandbell on 24-11-27.
//

#include "Menu.h"

//打印菜单
void Menu::PrintMenu() {
    int choice;
    while (true) {
        cout<<"\n当前算法: ";
        switch (mode) {
            case 1:
                cout<<"最先适应法"<<endl;
                break;
            case 2:
                cout<<"最佳适应法"<<endl;
                break;
            default:
                cout<<"最坏适应法"<<endl;
                break;
        }
        cout<<"当前数据: ";
        switch (dataMode) {
            case 1:
                cout<<"默认数据"<<endl;
                break;
            case 2:
                cout<<"自定义数据"<<endl;
                break;
            default:
                cout<<"文件数据"<<endl;
                break;
        }
        cout<<"当前内存大小: "<<RAMSize<<"KB"<<endl;
        cout<<"/**---------菜单---------**\\"<<endl;
        cout << "1.选择算法" << endl;
        cout << "2.设置数据" << endl;
        cout << "3.设置内存大小"<<endl;
        cout << "4.单步运行" << endl;
        cout << "5.直接运行" << endl;
        cout << "0.退出" << endl;
        cout<<"/-**------菜单结束-------**\\"<<endl;
        cout << "请选择:";
        cin >> choice;
        switch (choice) {
            case 1:
                chooseMode();
                break;
            case 2: {
                chooseData();
                //验证内存大小是否足够运行所有进程，如果不够则重新设置
                int max = 0;
                for (auto &process: processes) {
                    if (process.needSize > max) {
                        max = process.needSize;
                    }
                }
                if (max > RAMSize) {
                    cout << "内存大小不足以运行所有进程，请重新分配内存(至少" <<max<<"KB)"<< endl;
                    setRAMSize();
                }
                break;
            }
            case 3:
                setRAMSize();
                break;
            case 4:
                run(false);
                break;
            case 5:
                run();
                break;
            case 0:
                return;
            default:
                cout << "输入错误，请重新输入" << endl;
        }
    }
}

//选择算法
void Menu::chooseMode() {
    cout << "请选择算法(1-最先适应法 2-最佳适应法 3-最坏适应法):";
    cin >> mode;
}

//选择数据
void Menu::chooseData() {
    cout << "请选择数据(1-默认数据 2-输入数据 3-从文件读取):";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            loadFromDefault();
            break;
        case 2:
            loadFromInput();
            break;
        case 3:
            loadFromFile();
            break;
        default:
            cout << "输入错误，请重新输入" << endl;
    }
}

//从默认数据加载
void Menu::loadFromDefault() {
    processes = defaultProcesses;
    dataMode = 1;
}

//从输入加载
void Menu::loadFromInput() {
    processes.clear();
    int size;
    cout << "请输入进程数量: ";
    cin >> size;
    if (size<=0){
        cout<<"数量不得为0，已重新加载默认数据"<<endl;
        loadFromDefault();
        return;
    }
    for (int i = 0; i < size; ++i) {
        int needSize, createTime, needTime;
        cout << "请依次输入进程" << i << "的大小 创建时间 需要时间: ";
        cin >> needSize >> createTime >> needTime;
        if (needSize<=0 || createTime <0 || needTime<=0){
            cout<<"数据错误，已重新加载默认数据"<<endl;
            loadFromDefault();
            return;
        }
        processes.push_back(Process(needSize, createTime, needTime));
    }
    dataMode = 2;
}

//从文件加载
void Menu::loadFromFile() {
    cout << "\n请在当前可执行文件的文件夹中准备input.txt文件" << endl;
    cout << "文件格式: 第一行为进程数量，接下来每行为一个进程的大小 创建时间 需要时间" << endl;
    cout << "确认后按下回车继续...";
    getchar();//吃掉缓冲区中的回车
    getchar();
    processes.clear();
    string fileName = "input.txt";
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "文件打开失败" << endl;
        return;
    }
    int size;
    file >> size;
    for (int i = 0; i < size; ++i) {
        int needSize, createTime, needTime;
        file >> needSize >> createTime >> needTime;
        processes.push_back(Process(needSize, createTime, needTime));
    }
    dataMode = 3;
    cout << "文件读取成功" << endl;
}

//设置内存大小
void Menu::setRAMSize() {
    cout << "请输入内存大小(KB):";
    cin >> RAMSize;
    if (RAMSize <= 0) {
        cout << "输入错误，请重新输入" << endl;
        RAMSize=256;
        setRAMSize();
    }
    //验证内存大小是否足够运行所有进程
    for(auto &process: processes) {
        if(process.needSize > RAMSize) {
            cout << "内存大小不足以运行所有进程，请重新输入" << endl;
            RAMSize=256;
            setRAMSize();
        }
    }
}

//运行
void Menu::run(bool toEnd) {
    switch (mode) {
        case 1: {
            RAMwithFirstFit ram(RAMSize, processes);
            CPU cpu(&ram);
            cpu.RunToEnd(toEnd);
            break;
        }
        case 2: {
            RAMwithBestFit ram(RAMSize, processes);
            CPU cpu(&ram);
            cpu.RunToEnd(toEnd);
            break;
        }
        default: {
            RAMwithWorstFit ram(RAMSize, processes);
            CPU cpu(&ram);
            cpu.RunToEnd(toEnd);
            break;
        }
    }
}