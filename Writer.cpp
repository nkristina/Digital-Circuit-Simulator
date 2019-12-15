#include "Writer.h"

void Writer::write(string inFile)
{
	string outFile=inFile;
	while (outFile.back()!='.')
	{
		outFile.pop_back();
	}
	outFile.pop_back();

	outFile = outFile + "_" + to_string(id_) + ".txt";

	fstream out;
	out = fstream(outFile, ios::out);

	for (auto t: changeMoments_)
	{
		out << output_ << " -> " << !output_ << ": " << t << "us" << endl;
		output_ = !output_;
	}

	out.close();
}

void Writer::addMoment(double t)
{
	changeMoments_.push_back(t);
}

Writer::Writer(int id): id_(id)
{
}
