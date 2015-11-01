/*
* Introduction in classes
*/

#include <iostream>
#include <string>
#include <exception>
#include <vector>

using namespace std;
vector <int> midistream_1 = { 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, };

//------------------------------------------------------------------------------
class Midi_data {
public:   
	// constructor
    Midi_data();
	// member-functions
    vector <int> data_bit= { 0, 0, 0, 0, 0, 0, 0, 0};
private:
	int start_bit = '0';       
    int stop_bit = '1';
    bool data_valid = false;
};


class Midi_stream {
public: 
    // constructor (vgl. line 36)
    Midi_stream();   
    // member-functions
    Midi_data get_next_data();     
    void putback(Midi_data m);    
private:
    bool data_in_buffer;       
    Midi_data buffer_for_Midi_data;     
};


// Constructor ----------------------------------------------------------------
Midi_data::Midi_data(): data_valid(false)  
{
}

Midi_stream::Midi_stream(): data_in_buffer(false)
{
}


// Member-functions ------------------------------------------------------------
Midi_data Midi_stream::get_next_data()
{
    char bit;
	vector <char> stream(100);
    // read bits from vector (or from cin)
    cin >> bit;   

	// check for start


    // reads in


    // check for end
	
	
	// data valid 

}

//------------------------------------------------------------------------------

Midi_stream stream;        

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------

int main()
{
    try
    {
      //
	  
    
	  
    }
  catch (exception& e) {
    cerr << "error: " << e.what() << '\n';  
    return 1;
  }
  catch (...) {
    cerr << "Oops: unknown exception!\n";  
    return 2;
  }
}


