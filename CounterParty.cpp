#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <thrust/device_vector.h>
#include "Bank.cpp"
#include "Swap.cpp"


using namespace std;


class CounterParty{

public:

	string id;
	float hazard_rate;
	//int position; //1 represents long, -1 represents short to the counterparty
	thrust::device_vector<Deal> deals;

	CounterParty(){
       this->id="";
       this->hazard_rate=0;
	}

	CounterParty(string id){
	       this->id=id;
	       this->hazard_rate=0;
		}

	CounterParty(string id,string rate){
       this->id=id;
       this->hazard_rate=stof(rate);
	}











};
