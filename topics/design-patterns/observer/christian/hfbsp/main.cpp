// main.cpp: observer pattern as in head first design patterns book
#include<iostream>
#include"interfaces.h"
#include"weatherdisplays.h"

using namespace std; 

int main()
{

  WeatherData wdata;
  wdata.setNewValues(23.0, 45.0, 40.0);

  CurrentConditionsDisplay currentDisplay(wdata);
  
  wdata.setNewValues(23.0, 30.0, 46.0);
  wdata.setNewValues(23.0, 35.0, 46.0);

  
  return 0;
}

