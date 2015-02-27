#include <boost/algorithm/string.hpp>
#include <iostream>
#include <thread>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <string.h>



using namespace std;


class CounterParty{

public:

	string id;
	string rating;
	float hazard_rate;
	int position; //1 represents long, -1 represents short to the counterparty


	CounterParty(string id,string rating,string position){
       this->id=id;
       if(boost::iequals("A",rating)){
          hazard_rate=0.02;
       }else if(boost::iequals("B",rating)){
    	   hazard_rate=0.04;
       }else if(boost::iequals("C",rating)){
    	   hazard_rate=0.06;
       }else if(boost::iequals("D",rating)){
    	   hazard_rate=0.08;
       }else if(boost::iequals("E",rating)){
    	   hazard_rate=0.1;
       }

       this->position=atoi(position.c_str());
	}






}
