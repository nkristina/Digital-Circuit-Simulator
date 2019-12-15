#include "Simulator.h"
#include "Exception.h"
#include <iostream>
#include <vector>
#include<string>

void test() {
	// IZMENITI SADRZAJ UNUTAR '{' i '}' DA BISTE POKRETALI ZELJENI SKUP TESTOVA
	int test_numbers[] = { 0,1,2,3,4,5 };
	std::vector<int> test_vector(test_numbers, test_numbers + sizeof(test_numbers) / sizeof(int));
	try {

		for (int test_number : test_vector) {
			Simulator simulator;
			simulator.loadCircuit("D:/ETF 2/OOP/Simulator/Simulator/inputs/test_" + to_string(test_number) + ".txt");
			simulator.simulate("D:/ETF 2/OOP/Simulator/Simulator/outputs/test_" + to_string(test_number) + "_output.txt");
		}
	}
	catch (WrongInput& e) {
		std::cout << e.what() << std::endl;
	}
	catch (Exception & e) {
		std::cout << e.what() << std::endl;
	}
}