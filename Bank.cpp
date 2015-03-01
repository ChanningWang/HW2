#include "Curve.cpp"
using namespace std;

class Bank {

public:
	long long counterParty_number;
	long long fx_number;
	long long swap_number;

	Bank() {
		string number_str = Utils::getParam("Config.txt",
				"CounterParty_Number");
		counterParty_number = stol(number_str);
		number_str = Utils::getParam("Config.txt", "Forex_Number");
		fx_number = stol(number_str);
		number_str = Utils::getParam("Config.txt", "Swap_Number");
		swap_number = stol(number_str);
	}

	void createMapping(string file) {
		int remainder = -1;

		remove(file.c_str());
		std::fstream fs(file, ios::out | ios::app | ios::binary);
		string line;

		NumberDistribution distribution_A(1, counterParty_number * 16 / 31);
		RandomNumberGenerator generator_A;
		Generator AGenerator(generator_A, distribution_A);
		generator_A.seed(std::time(0)); // seed with the current time

		NumberDistribution distribution_B(counterParty_number * 16 / 31+1, counterParty_number * 24 / 31);
		RandomNumberGenerator generator_B;
		Generator BGenerator(generator_B, distribution_B);
		generator_B.seed(std::time(0)); // seed with the current time

		NumberDistribution distribution_C(counterParty_number * 24 / 31+1, counterParty_number * 28 / 31);
		RandomNumberGenerator generator_C;
		Generator CGenerator(generator_C, distribution_C);
		generator_C.seed(std::time(0)); // seed with the current time

		NumberDistribution distribution_D(counterParty_number * 28 / 31+1, counterParty_number * 30 / 31);
		RandomNumberGenerator generator_D;
		Generator DGenerator(generator_D, distribution_D);
		generator_D.seed(std::time(0)); // seed with the current time

		NumberDistribution distribution_E(counterParty_number * 30 / 31+1, counterParty_number );
		RandomNumberGenerator generator_E;
		Generator EGenerator(generator_E, distribution_E);
		generator_E.seed(std::time(0)); // seed with the current time

		for (int i = 1; i <= fx_number; i++) {
			remainder = i % 31;
			if (remainder >= 0 && remainder <= 15) {
				line=stringMapping(AGenerator(), i, 'F');
			}else if(remainder >= 16 && remainder <= 23){
				line=stringMapping(BGenerator(), i, 'F');

			}else if(remainder >= 24 && remainder <= 27){
				line=stringMapping(CGenerator(), i, 'F');

			}else if(remainder >= 28 && remainder <= 29){
				line=stringMapping(DGenerator(), i, 'F');

			}else if(remainder ==30){
				line=stringMapping(EGenerator(), i, 'F');

			}
			fs << line;
		}
		for (int i = 1; i <= swap_number; i++) {
			remainder = i % 31;
						if (remainder >= 0 && remainder <= 15) {
							line=stringMapping(AGenerator(), i, 'S');
						}else if(remainder >= 16 && remainder <= 23){
							line=stringMapping(BGenerator(), i, 'S');

						}else if(remainder >= 24 && remainder <= 27){
							line=stringMapping(CGenerator(), i, 'S');

						}else if(remainder >= 28 && remainder <= 29){
							line=stringMapping(DGenerator(), i, 'S');

						}else if(remainder ==30){
							line=stringMapping(EGenerator(), i, 'S');

						}
						fs << line;
		}
		fs.close();
	}

	void createCounterParties(string file) {
		remove(file.c_str());
		std::fstream fs(file, ios::out | ios::app | ios::binary);
		string line;

		for (int i = 1; i <= counterParty_number; i++) {
			if (i >= 1 && i <= counterParty_number * 16 / 31) {
				line = stringCounterParty(i, 'A');
			} else if (i > counterParty_number * 16 / 31
					&& i <= counterParty_number * 24 / 31) {
				line = stringCounterParty(i, 'B');
			} else if (i > counterParty_number * 24 / 31
					&& i <= counterParty_number * 28 / 31) {
				line = stringCounterParty(i, 'C');
			} else if (i > counterParty_number * 28 / 31
					&& i <= counterParty_number * 30 / 31) {
				line = stringCounterParty(i, 'D');
			} else if (i > counterParty_number * 30 / 31
					&& i <= counterParty_number) {
				line = stringCounterParty(i, 'E');
			}

			fs << line;
		}
		fs.close();

	}

	void createFX(string file) {
		remove(file.c_str());
		std::fstream fs(file, ios::out | ios::app | ios::binary);
		string line;
		NumberDistribution distribution(800000, 1200000);
		RandomNumberGenerator generator;
		Generator numberGenerator(generator, distribution);
		generator.seed(std::time(0)); // seed with the current time

		for (int i = 1; i <= fx_number; i++) {
			if (i >= 1 && i <= fx_number * 2 / 5) {
				line = stringFX(i, numberGenerator(), 1);
			} else {
				line = stringFX(i, numberGenerator(), -1);
			}

			fs << line;
		}
		fs.close();

	}

	void createSwap(string file) {
		remove(file.c_str());
		std::fstream fs(file, ios::out | ios::app | ios::binary);
		string line;
		NumberDistribution distribution_notional(800000, 1200000);
		RandomNumberGenerator generator_notional;
		Generator notionalGenerator(generator_notional, distribution_notional);
		generator_notional.seed(std::time(0)); // seed with the current time

		NumberDistribution distribution_Fleg(2, 8);
		RandomNumberGenerator generator_Fleg;
		Generator fLegGenerator(generator_Fleg, distribution_Fleg);
		generator_Fleg.seed(std::time(0)); // seed with the current time

		NumberDistribution distribution_tenor(2, 50);
		RandomNumberGenerator generator_tenor;
		Generator tenorGenerator(generator_tenor, distribution_tenor);
		generator_tenor.seed(std::time(0)); // seed with the current time

		int position=0;
		char currency='U';

		for (int i = 1; i <= swap_number; i++) {
			if (i >= 1 && i <= swap_number * 11 / 20) {
				position=1;
			} else {
				position=-1;
			}
			if(i%2==0){
				currency='U';
			}else{
				currency='E';
			}

			line = stringSwap(i, currency, notionalGenerator(),
									fLegGenerator() / 100.0, tenorGenerator(), position);


			fs << line;
		}
		fs.close();

	}

	string stringCounterParty(int ID, char rating) {
		std::ostringstream os;
		float hazard_rate = 0;
		if (rating == 'A') {
			hazard_rate = 0.02;
		} else if (rating == 'B') {
			hazard_rate = 0.04;
		} else if (rating == 'C') {
			hazard_rate = 0.06;
		} else if (rating == 'D') {
			hazard_rate = 0.08;
		} else if (rating == 'E') {
			hazard_rate = 0.1;
		}
		os << ID << "," << rating << "," << hazard_rate << endl;
		return os.str();
	}

	string stringFX(int ID, int nominal, int position) {
		std::ostringstream os;
		os << ID << "," << nominal << "," << position << endl;
		return os.str();
	}

	string stringSwap(int ID, char currency, int notional, float fixed_leg, int tenor,
			int position) {
		std::ostringstream os;
		os << ID << "," << currency<<","<<notional << "," << fixed_leg << "," << tenor << ","
				<< position << endl;
		return os.str();
	}

	string stringMapping(int counterPartyID, int dealID, char type ) {
			std::ostringstream os;
			os << counterPartyID << "," << dealID << "," << type << endl;
			return os.str();
		}

};
