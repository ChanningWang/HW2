#include "CounterParty.cpp";
#include <thrust/device_vector.h>

class Simulate{

public:

	float recovery_rate;
	float flat_rate;
	float initialExchangeRate;
	int CounterParty_Number;
	int Forex_Number;
	int Swap_Number;
	int Swap_Reset;
    int Path;

    thrust::device_vector<double> cva_vector(CounterParty_Number);
        	thrust::device_vector<CounterParty> cp_vector(CounterParty_Number);
        	thrust::device_vector<Forex> fx_vector(Forex_Number);
        	thrust::device_vector<Swap> swap_vector(Swap_Number);

    Simulate(){
    	recovery_rate=stof(Utils::getParam("Config.txt", "recovery_rate"));
    	flat_rate=stof(Utils::getParam("Config.txt", "flat_rate"));
    	initialExchangeRate=stof(Utils::getParam("Config.txt", "EUR/USD"));
    	CounterParty_Number=stoi(Utils::getParam("Config.txt", "CounterParty_Number"));
    	Forex_Number=stoi(Utils::getParam("Config.txt", "Forex_Number"));
    	Swap_Number=stoi(Utils::getParam("Config.txt", "Swap_Number"));
    	Swap_Reset=stoi(Utils::getParam("Config.txt", "Swap_Reset"));
    	Path=stoi(Utils::getParam("Config.txt", "Path"));




    }

   void loadCounterParty(){
	   string line;

	   		std::ifstream fileStream("CounterParty.txt");
	   		std::vector<string> strs;
	        CounterParty cp;

	   		while (getline(fileStream, line, '\n')) {
	   				trim(line);
	   				boost::split(strs, line, boost::is_any_of(","));
	            cp=CounterParty(strs[0],strs[2]);
	            cp_vector[stoi(strs[0])-1]=cp;
	   		}

   }

   void loadDeals(){

   }

   void loadMapping(){

   }

	void run(){



	}
	
	int main() {

		//	Bank citi;
		//	citi.createCounterParties("CounterParty.txt");
		//	citi.createFX("FX.txt");
		//	citi.createSwap("Swap.txt");
		//	citi.createMapping("DealMap.txt");

	//	Curve curve('U');
	//	cout<<curve.getYield(0.5)<<endl;
		//cout<<"hello"<<endl;

		Simulate simulator;
		simulator.loadCounterParty();
		for(int i=0;i<simulator.CounterParty_Number;i++){
			cout<<((CounterParty)simulator.cp_vector[i]).id<<","<<((CounterParty)simulator.cp_vector[i]).hazard_rate<<endl;
		}

	}

};
