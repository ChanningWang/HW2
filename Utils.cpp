#include <iostream>
#include <thread>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <time.h>
#include <boost/algorithm/string.hpp>
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <chrono>
#include <random>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"
#include "Logging.cpp"


using namespace std;
using namespace boost::algorithm;

typedef boost::uniform_int<> NumberDistribution;
typedef boost::mt19937 RandomNumberGenerator;
typedef boost::variate_generator<RandomNumberGenerator&, NumberDistribution> Generator;

class Utils{

public:



	static string getParam(string file, string key) {
		std::ifstream fileStream(file);
		string line;
		std::vector<string> strs;
		while (getline(fileStream, line, '\n')) {
			if (boost::algorithm::contains(line, key)) {
				boost::split(strs, line, boost::is_any_of("="));
				trim(strs[1]);
				return strs[1];

			}
		}
		return "";
	}

//	static Generator getRandomGenerator(int low, int high) {
//
//		NumberDistribution distribution(1, 5);
//				RandomNumberGenerator generator;
//				Generator numberGenerator(generator, distribution);
//				generator.seed(std::time(0)); // seed with the current time
//	}


//	Bank citi;
//	citi.createCounterParties("CounterParty.txt");
//	citi.createFX("FX.txt");
//	citi.createSwap("Swap.txt");
//	citi.createMapping("DealMap.txt");





};
