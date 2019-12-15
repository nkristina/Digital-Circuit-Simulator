#ifndef timee_h
#define timee_h

#include "TreeNode.h"
#include<vector>

class Time
{
public:
	Time(double t);

	//void formTime(vector<GEN*> generators, vector<MANUAL*> manuels, double duration);
	double getT() const;

	void add(TreeNode* gen);
	void changeState();

	//void addGenerator(vector<double> generators,double duration);
	//void addManual(vector<double> manuels, double duration);
	
private:
	//bool isInTime(double t);
	double t_;
	vector<TreeNode*> generators_;
};

#endif // !timee_h