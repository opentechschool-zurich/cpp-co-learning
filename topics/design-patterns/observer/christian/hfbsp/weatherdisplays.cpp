#include "weatherdisplays.h"


// WeatherData::WeatherData(){
//   temperature = 0;
//   humidity = 0;
//   pressure = 0; 
// }

void WeatherData::registerObserver(Observer* o){
  observer_vec.push_back(o);
}

void WeatherData::removeObserver(Observer* o){
  // for (auto x : observer_vec)
  //   if (x == o)
  //     observer_vec.erase(x, x + 1)
        }

void WeatherData::notifyObservers(){
  for (auto x : observer_vec)
    (*x).update(temperature, humidity, pressure);
};






void WeatherData::setNewValues(float t, float h, float p)
{
  temperature=t;
  humidity=h;
  pressure=p;

  notifyObservers(); 
  
}; 




