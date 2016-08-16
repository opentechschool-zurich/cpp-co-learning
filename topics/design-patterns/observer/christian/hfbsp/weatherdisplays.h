#pragma once
#include<iostream>
#include<vector>
#include"interfaces.h"

using namespace std;

class WeatherData : public Subject
{
public:

  void registerObserver(Observer*);
  void removeObserver(Observer*);
  void notifyObservers();
  void setNewValues(float, float, float); 

private:
  double temperature;
  double humidity;
  double pressure;
  vector<Observer*> observer_vec; 
};


class CurrentConditionsDisplay : public Observer, public DisplayElement
{
public:
  CurrentConditionsDisplay(WeatherData weatherD){
    wD = weatherD;
    wD.registerObserver(this); 
  }

  void display(){
    cout << "Current condtions: " << temperature << "C degress and "
         << humidity << "% humidity" << endl; 
  }
  
  void update(double t, double h, double p){

    temperature = t;
    humidity = h;
    cout << "updated" << endl; 
    display(); 
  }



private:
  double temperature;
  double humidity;
  WeatherData wD; 

};


