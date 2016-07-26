
class Observer
{
public:
  Observer();
  virtual ~Observer();
  virtual void update(double temp, double humidity, double pressure) = 0; 
};

class Subject
{
public:
  Subject();
  virtual void registerObserver(Observer* o) = 0;
  virtual void removeObserver(Observer* o) = 0;
  virtual void notifyObserver(); 
  virtual ~Subject();

};

class DisplayElement
{
public:
  DisplayElement();
  virtual ~DisplayElement();
  virtual void display(); 
};
