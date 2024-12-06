#pragma once
#include <vector>

#ifndef __DATA_MANAGER__
#define __DATA_MANAGER__
class DataManager
{
    private:
    std::vector<int> _stepsX;
    std::vector<int> _stepsY;
    std::vector<int> _pen;
    
    public:
    DataManager();
    void clearData();
    void appendData(int x, int y, int p);
    int size();
    int getX(int i);
    int getY(int i);
    int getP(int i);


};

#endif
