//============================================================================
// Name        : Assignment_B.cpp
// Author      : chengbin wang
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Bank.cpp"


using namespace std;

int main() {

Bank citi;
citi.createCounterParties("CounterParty.txt");
citi.createFX("FX.txt");
citi.createSwap("Swap.txt");
citi.createMapping("DealMap.txt");





	return 0;
}
