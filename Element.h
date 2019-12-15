#ifndef Elementt
#define Elementt

#include<iostream>
#include<stdio.h>
#include<vector>

using namespace std;

const int standard = 2; //standardni broj ulaza za sve elemente osim NOT

enum type { Sonda = 0, Gen, Manual, Not, And, Or };

class Element
{
public:
	Element(int num) : num_(num), output_(false) {};
	Element(const Element& other) { num_ = other.getNumber(); output_ = other.getOutput(); }; //kopirajuci konstruktor

	virtual Element* clone() const = 0;

	virtual void doing(bool input) = 0; //funkcija koja racuna izaz na elementu
	virtual bool isGenerator() const = 0; //provera da li je generator
	virtual bool standardOutput() const = 0; //pocetna vrednost pri racunanju izlaza
	virtual int getNumberOfPins() const = 0; //vraca broj ulaza

	void setOutput(bool input) { output_ = input; } //posattavljanje ulaza na zadatu vrednosti

	bool getOutput() const { return output_; }
	int getNumber() const { return num_; }

	virtual ~Element() {};

protected:
	int num_; //redni broj elementa
	bool output_; //izlaz
};

//NOT--------------------------------------------------------------------------------
class NOT : public Element
{
public:
	NOT(int num) :Element(num), numberOfPins_(1) { x_ = Not; } // postavalja broj ulaza na standardni za NOT element
	NOT(const NOT& other) : Element(other) { numberOfPins_ = other.getNumberOfPins(); x_ = Not; };

	NOT* clone() const override {return new NOT(*this); }

	void doing(bool input) override { output_ = !input; } //negira ulaz

	bool isGenerator() const override { return false; }
	bool standardOutput() const override { return false; }
	int getNumberOfPins() const override { return numberOfPins_; }


private:
	int numberOfPins_;
	type x_; //tip elementa
};

//OR----------------------------------------------------------------------------------
class OR : public Element
{
public:
	OR(int num, int pins=standard) : Element(num), numberOfPins_(pins) { x_ = Or; } //posatvaljanje broja ulaza na standardni za OR elment ako nije drigacije navedeno
	OR(const OR& other): Element(other) { numberOfPins_ = other.getNumberOfPins(); x_ = Or; }

	OR* clone() const override {return new OR(*this); }

	void doing(bool input) override { output_ = output_ || input; } //input ce biti vrednost sa jednog od ulaza, ona se dodaje na dosada izracunat izlaz	
	
	bool isGenerator() const override { return false; }
	bool standardOutput() const override { return false; }
	int getNumberOfPins() const override { return numberOfPins_; }

private:
	int numberOfPins_;
	type x_;
};

//AND----------------------------------------------------------------------------------
class AND : public Element
{
public:
	AND(int num, int pins = standard) : Element(num), numberOfPins_(pins) { x_ = And; output_ = true; } //posatvaljanje broja ulaza na standardni za AND elment ako nije drigacije navedeno
	AND(const AND& other) : Element(other) { numberOfPins_ = other.getNumberOfPins(); x_ = And; }

	AND* clone() const override {return new AND(*this); }

	void doing(bool input) override { output_ = output_ && input; } //input ce biti vrednost sa jednog od ulaza, ona se dodaje na dosada izracunat izlaz

	bool isGenerator() const override { return false; }
	bool standardOutput() const override { return true; }
	int getNumberOfPins() const override { return numberOfPins_; }

	//~AND() {}
private:
	int numberOfPins_;
	type x_;
};

//GENERATOR--------------------------------------------------------------------------------
class GEN : public Element
{
public:
	GEN(int num, double freq) : Element(num), freq_(freq) { x_ = Gen; t_ = 1. / (2 * freq_); } //za t_ se racuna poluperioda iz frekvencije koja se dobija
	GEN(const GEN& other) : Element(other) { t_ = other.getHalfPeriod(); freq_ = other.getFreq(); moments_ = other.getMoments(); x_ = Gen; }

	GEN* clone() const override {return new GEN(*this); }

	void changeOutput() { output_ = !output_; } //funkcija koja promeni izlaz generatora
	void doing(bool input) override { output_ = input; } //funkcija koja promeni izlaz generatora na zadatu vrednost

	void formMoments(double duration) { for (int i = 1; t_*i < duration; i++) moments_.push_back(t_ * i); } //formira niz vremena u kojima se menja vrednost generatora
	vector<double> getMoments() const { return moments_; }

	double getHalfPeriod() const { return t_; } //vraca poluperiodu
	double getFreq() const { return freq_; } //vraca frekvenciju

	bool isGenerator() const override { return true; }
	bool standardOutput() const override { return false; }
	int getNumberOfPins() const override { return 0; }

private:
	double t_, freq_; // t_ je polu perioda (na koliko se menja signal), freq_ je frekvencija
	type x_;
	vector<double> moments_;
};

//RUCNI GENERATOR--------------------------------------------------------------------------
class MANUAL: public Element
{
public:
	MANUAL(int num) : Element(num) { x_ = Manual; }; //obrisala sam vec iz konstruktora
	MANUAL(const MANUAL& other) : Element(other) { moments_ = other.getMoments(); x_ = Manual; }

	MANUAL* clone() const override { return new MANUAL(*this); }

	void changeOutput() { output_ = !output_; } //funkcija koja promeni izlaz generatora
	void doing(bool input) override { output_ = input; } //funkcija koja promeni izlaz generatora na zadatu vrednost

	double getMoment(int i) const { return moments_[i]; } //funcija koja vraca i-ti trenutak
	void addMoment(double moment) { moments_.push_back(moment); } //dodaje trenutak promene u niz
	vector<double> getMoments() const { return moments_; }

	bool isGenerator() const override { return true; }
	bool standardOutput() const override { return false; }
	int getNumberOfPins() const override { return 0; }

private:
	vector<double> moments_; // niz u kom se cuvaju trenutci u kojima se menja izlaz generatora
	type x_;
};

//SONDA--------------------------------------------------------------------------------------
class SONDA : public Element
{
public:
	SONDA(int num) : Element(num) { x_ = Sonda; }
	SONDA(const SONDA& other) : Element(other) { x_ = Sonda; }

	SONDA* clone() const override { return new SONDA(*this); }

	void doing(bool input) override { output_ = input; }

	virtual bool isGenerator() const override { return false; }
	virtual bool standardOutput() const override { return false; }
	int getNumberOfPins() const override { return 1; }

private:
	type x_;
};
#endif
