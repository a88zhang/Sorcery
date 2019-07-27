//
// Created by Tim Liu on 2019-07-22.
//
#include <vector>
#include <iostream>

#ifndef SORCERY_SUBJECT_H
#define SORCERY_SUBJECT_H

template <typename InfoType, typename StateType> class Observer;

template <typename InfoType, typename StateType> class Subject {
    std::vector<Observer<InfoType, StateType>*> observers;
    StateType state;
    InfoType info;
protected:
    void setState(StateType newS);
public:
    void attach(Observer<InfoType, StateType> *o);
    void detach(Observer<InfoType, StateType> *o);
    void notifyObservers();
    InfoType getInfo() const;
    void setInfo(InfoType);
    StateType getState() const;
    ~Subject() = 0;
};

#endif //SORCERY_SUBJECT_H