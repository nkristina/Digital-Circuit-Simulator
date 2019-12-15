#ifndef WRITER_H
#define WRITER_H

#include<fstream>
#include<vector>
#include<string>

using namespace std;

class Writer
{
public:
	Writer(int id);

	void write(string inFile);
	void addMoment(double t); //dodaje trenutak pormene


private:
	int id_;
	vector<double> changeMoments_;
	bool output_ = false;
};

#endif // !WRITER_H
