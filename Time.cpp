#include "Time.h"

Time::Time(double t): t_(t)
{
}

double Time::getT() const
{
	return t_;
}

void Time::add(TreeNode* gen)
{
	generators_.push_back(gen);
}

void Time::changeState()
{
	for (auto k : generators_)
	{
		k->changeGenerator();
	}
}

/*void Time::addGenerator(vector<double> generators, double duration)
{
	for (auto k : generators)
	{
		if (!isInTime(k))
			t_.push_back(k);
	}

}*/

/*bool Time::isInTime(double t)
{
	for (auto k : t_)
	{
		if (k == t)
			return true;
	}
	return false;
}*/
