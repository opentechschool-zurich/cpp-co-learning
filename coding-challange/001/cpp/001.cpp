#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cmath>

class Operator
{
private:
	std::vector<char> ops{'+', '-', '*', '/'};
	std::vector<char> actualOps{'+', '+', '+', '+'};
	int value;
	
	/**
	 * value is integer, make a numerical system base4 and fill ops in it
	 */
	void add(int val){
		/** add value */
		value += val;
		int tempVal = value;
		assert( tempVal < 64 );
		actualOps.at(3) = ops.at(tempVal/16);
		tempVal %= 16;
		actualOps.at(2) = ops.at(tempVal/4);
		tempVal %= 4;
		actualOps.at(1) = ops.at(tempVal);
	}
public:
	Operator():value(0){
	};
	~Operator(){
	};
	
	/**
	 * @brief get the 
	 * @retval actualOps vector with operators
	 */
	std::vector<char> get(){
		return actualOps;
	};

	/** @brief operator overload */
	void operator+=(int val){
		Operator::add(val);
	};
	/** @brief operator overload */
	void operator++(int){
		Operator::add(1);
	}
};


/**
 * @brief calc Result
 * 
 * B -> brackets
 * O -> orders
 * D -> division        > first
 * M -> multiplication  > second
 * A -> addition        > third
 * S -> subtraction     > fourth
 * 
 */
float calcResult(std::vector<int> numbers, std::vector<char> operators ){
	
	float result = 0;
	unsigned int pos = 0;
	std::vector<std::pair<char,int>> calc;
	std::vector<std::pair<char,int>> calcProcessed;

	for ( unsigned int pos=0; pos < numbers.size() ; pos++ ){
		calc.push_back(std::make_pair(operators.at(pos), numbers.at(pos)));
		std::cout << operators.at(pos) << numbers.at(pos);
	}
	std::cout << " : ";

	/**
	 * for the first
	 */
	for (  pos=0; pos < calc.size() ; pos++ ){
		if(calc.at(pos).first == '*' || calc.at(pos).first == '/'){
			calcProcessed.push_back(calc.at(pos-1));
			calcProcessed.push_back(calc.at(pos));
			calc.erase(calc.begin()+pos-1, calc.begin()+pos+1);
			break;
		}
	}
	/**
	 * for the second
	 */
	for (  pos=0; pos < calc.size() ; pos++ ){
		if(calc.at(pos).first == '*' || calc.at(pos).first == '/'){
			calcProcessed.push_back(calc.at(pos));
			calc.erase(calc.begin()+pos, calc.begin()+pos+1);
			break;
		}
	}
	/**
	 * and the rest
	 */
	for (auto rest: calc){
		calcProcessed.push_back(rest);
	}

	for (auto c: calcProcessed){
		if(c.first == '+'){
			result += c.second ;
		}
		else if(c.first == '-'){
			result -= c.second;
		}
		else if(c.first == '*'){
			result *= c.second;
		}
		else if(c.first == '/'){
			result /= c.second;
		}
	}
	return result;
}


int main(int argc, char *argv[])
{
	Operator op;
	std::vector<int> numbers;

	for( int count = 1; count < argc; count++ ){
		numbers.push_back( atoi(argv[count]) );
	}

	for (int runs=0; runs < std::pow(4,3); runs++){
		std::cout << "result:" << calcResult(numbers, op.get()) << std::endl;
		op+=1;
	}

	return 1;
}
