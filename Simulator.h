#ifndef Simulator_h
#define Simulator_h

#include "Element.h"
#include "Exception.h"
#include "Time.h"
#include "Tree.h"
#include "TreeNode.h"
#include "Writer.h"
#include<fstream>
#include<string.h>

class Simulator
{
public:

	Simulator();

	void loadCircuit(const string& filepath);
	void simulate(const string& filepath);

	vector<TreeNode*> getRoot(); //vraca niz pokazivaca na korene stabla

	Time* isMomentInTime(const double moment); //proverava da li je trnutak vec u vektoru times_
	void addGenerator(const vector<double> moments, TreeNode* gen); //ide kroz niz trenutaka za taj generator i dodaje ih u vektor times_ ako treba

	void formW();

	void sortTimes(); //sortira bitne trenutke

	~Simulator();

private:
	double duration; //vreme trajanja simulacije
	int numOfElements; //broj elemenata u kolu
	vector<TreeNode*> tree_; //niz pokazivaca na cvorove sa elementima
	vector<TreeNode*> sondas_; //izdvojene sonde
	vector<TreeNode*> generators_; //izdvojeni generatori
	//vector<TreeNode*> manuels_;
	vector<Time*> times_;
	Tree* circuit_;
	vector<Writer*> w_;
};

#endif// !SIMULATOR