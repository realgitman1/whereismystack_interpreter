#include <iostream>
#include <stdio.h>
#include <vector>
#include <typeinfo>
#include <fstream>
using namespace std;

vector<string> memory{"1","1"};
vector<string>dummymemory = memory;

class Interpreter {
public :
	vector<string> output;
	
	void parse(const string& line){
		
		
	
		int length = line.length();
		
		string currentstring = "";

		for (int i=0; i<length; i++){

			char current = line[i];
			
			if((!isdigit(current)) && (current != '+') && (current != '-') &&(current != '*') && (current != '/') && (current != '=')){
				currentstring += current;
			}	

			if(isspace(current)) continue;

			if(isdigit(current)) continue;
			
			if(current == '=') {
    				if (memory.size() >= 2) {
        				string secondLast = memory[memory.size() - 2];
        				string last = memory.back();

        				string combined = secondLast + last;

					if(currentstring != ""){
						output.push_back(combined + currentstring);
						currentstring.clear();
					} else{

						output.push_back(combined);
					}
					
        				dummymemory = memory;
        				memory.clear();
       	 				memory = dummymemory;
        
        				memory.push_back(combined);
					continue;

   				} else if (!memory.empty()) {
        				output.push_back(memory.back());
    				}
    					continue;
				}

			if(current == '^'){
				
				for(string s : output){
					cout << s << endl;								
				}

				break;

			}
			
			if (current == '?') {
    				if (i + 2 >= line.length()) {
        				cerr << "Error: Not enough arguments for '?'" << endl;
        				return;
    				}

    				int temp1 = line[i + 1] - '0';
    				int temp2 = line[i + 2] - '0';
				
				int difftemp = temp2 - temp1;
				 

				if(difftemp< 2){
					
					cerr << "The difference between two numbers cannot be less than 2";
					continue;
				}

    				if (temp1 >= 0 && temp1 <= temp2 && temp2 <= memory.size()) {
        	
       				int sum;
        			for (auto it = memory.begin() + temp1; it != memory.begin() + temp2; ++it) {
            				sum += stoi(*it);
        			}
				
				int sum127 = sum % 128;
				
				string stringsum = to_string(sum127);

        			memory.push_back(stringsum);
        			i += 2;
				}

				else { 
        				cerr << "Error: Memory out of range or invalid slice range" << endl;
        				return;
    				}
			}

			if (current == 'r') {
    					
				if (memory.size() >= 2) {
     		
        			swap(memory[memory.size() -1], memory[memory.size() - 2]);
    				}
    				continue;
			}
				
			int temp1 = stoi(memory.back());
			int temp2 = stoi(memory[memory.size()-2]);


			switch(current){
				case '+':
					{int temp3 = temp1 + temp2;
					memory.push_back(to_string(temp3));
					break;
					}						
						
				case '-':
					{
					int temp3 = temp2 - temp1;
					if(temp3<0){
						memory.push_back(to_string(-temp3));
					}
					else{
						memory.push_back(to_string(temp3));
					}
						break;
					}
					case '*':
						memory.push_back(to_string(temp1 * temp2));
						break;
					case '/':
						if(temp2 != 0){
							memory.push_back(to_string(temp1 / temp2));
								break;
						}else{
							printf("Error: Division by zero has occurred.");		
							return;
						}
			}
			
			continue;
		}
	}
		
};

int main() {
	
	Interpreter aplusbequalc;;
	
	ifstream inputFile("input.txt");

	if(!inputFile.is_open()){
		cerr << "Error : cannot open a file !!!" << endl;
		return 1;
	}

	string line;

	while(getline(inputFile, line)){
		aplusbequalc.parse(line);
	}

	return 0;

}
