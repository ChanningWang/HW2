#include "Forex.cpp"



class Swap: public Deal{

public:
	float notional;
	float fixed_leg;
	int tenor;
	char currency;

};
