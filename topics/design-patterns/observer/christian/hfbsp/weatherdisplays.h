

class WeatherData : public Subject
{
public:
  WeatherData();
  virtual ~WeatherData();
  void registerObserver(Observer* o);
  void removeObserver(Observer* o);
  void notifyObserver();
  void setNewValues(float, float, float); 
private:
  double temperature;
  double humidity;
  double pressure;
  vector<*Observer> observer_vec; 
};
