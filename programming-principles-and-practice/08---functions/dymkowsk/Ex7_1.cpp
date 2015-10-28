#include<iostream>
#include<string>
#include<vector> 
#include<algorithm> //sort

using namespace std;

class Person{ 
      private:
        string name;
	int age;

     

      public:

        Person(string n, int a)
	{ 
	   name = n;
	   age = a;
	}

        /*
          Here we are overloading operator <
          Operator < is a two-body operator first parameter is this

          keyword this
          ============ 
          Keyword "this" is a special keyword it referers to the current instance of the class
          (current instance : maybe a better name can be find, anyway it is equivalent of self in Python) 
          To be more precise "this" is a pointer to the current instance
          
          expression ->
          this expression is used when we have a pointer to the object
          by using -> we can call methods of class on the particular object or attributes of the  object 
          here we access attribute name of the object which is pointed by pointer this 
         
          Person a
          ========
          This is a second parameter of our operator <

   
        */
        bool operator<(const Person & a){
         
           // First we compare names. In case we have the same names we start to compare ages of persons. 
           // If  this->age<a.age is true then the current object is first otherwise the Person a is first    
           if (this->name<a.name){
               return true;    
           }           
           if (this->name==a.name && this->age<a.age ){
              return true;
           }
           return false;

        }


        // I set attributes to private so I need getters
        string get_name() const { //const here means that get_name function will not change atributes of "this" object 
           return this->name;
        } 
   
        int get_age() const {
           return this->age;
        }

}; 


/*
    equivalent definition of operator < as a standalone function
    =====================================================
    This is a standalone function, it is not a part of the class  Person
    This version takes two input parameters which are both of type Person

    bool operator<(const Person & a, const  Person & b)
    {
        if (a.get_name()<b.get_name()){
           return true;    
        }           
        if (a.get_name()==b.get_name() && a.get_age()<b.get_age() ){
           return true;
        }
        return false;
    } 
*/

// printing funciton used for the first solution
void printvectors(const vector<string>& v1, const vector<int> v2){

	int size = v1.size(); 
        for (int i = 0; i < size ; i++)
        {
            cout<<"("<<v1[i]<<", "<<v2[i]<<")\n";
        }  
}

// printing function used for the second solution
void printvectors(const vector<Person>& v){

	int size = v.size(); 
        for (int i = 0; i < size ; i++)
        {
            cout<<"("<<v[i].get_name()<<", "<<v[i].get_age()<<")\n";
        }  


}


int main()
{

        
	/* first solution
        vector<string> name {"Piotr", "Marc", "Steven", "John", "Maria"};
	vector<int> age {35, 20, 17, 54, 27};

       
        
	vector<string> name_old = name;
	vector<int> age_old = age;
	

	sort(name.begin(), name.end());	
	
	for(int i = 0; i < name.size(); ++i)
	{
	string name_i = name[i];
	for(int j = 0; j < age.size(); ++j)
	{
		if(name_old[j] == name_i)
			{  
				age[i] = age_old[j];
				
				continue;
			}	
	}	
	}
        cout<<"Before sorting"<<"\n";
	printvectors(name_old, age_old);
        cout<<"After sorting"<<"\n";
        printvectors(name, age);

        */ 

        //second attempt 
        vector<string> name {"Piotr", "Marc", "Steven", "Piotr", "Maria"};
	vector<int> age {35, 20, 17, 54, 27};

        vector<Person> People;

	for(int i=0; i< name.size(); ++i)
            People.push_back(Person(name[i],age[i]));

        vector<Person> People_unsorted= People;

        // here we do a simple test if our implementation of operator < works
        Person a (name[1], age[1]);
	Person b (name[2], age[2]);

        cout <<"Let's test implementation of <.\n";
	if (a<b){
         cout<<"Test of operator < is successfull (we got Marc<Steven)!\n";
        }
        else{
        cout<<"Test of operator < failed ( we got Mark>Steven)! \n";
       }
       
       sort(People.begin(),People.end());
       cout<<"Before sorting"<<"\n";
       printvectors(People_unsorted);
       cout<<"After sorting"<<"\n";
       printvectors(People);
	
	return 0; 
}


