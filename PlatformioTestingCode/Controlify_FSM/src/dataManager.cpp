#include "dataManager.h"


DataManager::DataManager()
{
    
}


void DataManager::clearData()
{
    this->_stepsX.clear();
    this->_stepsY.clear();
    this->_pen.clear();
}

void DataManager::appendData(int x, int y, int p)
{
    this->_stepsX.push_back(x);
    this->_stepsY.push_back(y);
    this->_pen.push_back(p);

}


int DataManager::size()
{
    return this->_stepsX.size();
}

int DataManager::getX(int i)
{
    return this->_stepsX.at(i);
}

int DataManager::getY(int i)
{
    return this->_stepsY.at(i);
}

int DataManager::getP(int i)
{
    return this->_pen.at(i);
}