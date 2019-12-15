#include "Simulator.h"
#include<stdio.h>

Simulator::Simulator() : duration(0), numOfElements(0), sondas_(), generators_(), w_(), tree_(), times_(), circuit_()
{
}

void Simulator::loadCircuit(const string& filepath)
{
	fstream inFile;
	inFile = fstream(filepath, ios::in);

	//char c; //pomocna promenjljiva za novi red i razmak
	int count = 0; //broji koliko elemenata je proslo

	if (inFile.peek() == EOF)
		throw WrongInput("Fajl je prazan");

	inFile >> duration;

	if (duration <= 0)
		throw WrongInput("Trajanje simulacije mora da bude vece od 0");

	if (inFile.peek() == EOF)
		throw WrongInput("Nema dovoljno podataka u fajlu");

	inFile >> numOfElements;
		
	if (numOfElements == 0)
		throw WrongInput("Nema elemenata u kolu");

	if (inFile.peek() == EOF)
		throw WrongInput("Nema podataka o elementima");

	//unosenje elemenata i formiranje vectora tih cvorova sa elementima (tree_)-------------------------------------------
	while (count < numOfElements && inFile.peek() != EOF)
	{
	
		int num; //redni broj elementa
		inFile >> num;

		if (num < 0)
			throw WrongInput("Redni broj elementa mora da bude veci od 0");

		if (inFile.peek() == EOF)
			throw WrongInput("Nema dovoljno podataka");

		int type_; //tip elementa	
		inFile >> type_;

		Element* s;
		TreeNode* k;
		GEN* g;
		MANUAL* m;
		NOT* n;
		OR* o;
		AND* a;

		vector<double> moments;

		switch (type_)
		{
		case Sonda:
		{
			s = new SONDA(num);
			k = new TreeNode(*s);
			tree_.push_back(k);

			delete s;

			sondas_.push_back(k); //stavljamo u vektor sondi koji ce biti veltor pocetnih cvorova drveta

			while (inFile.peek() != '\n')
			{
				if (inFile.peek() != ' ') //ukoliko se ne stavi enter odmah posle unosenja nego se stave razmaci
					throw WrongInput("Uneli ste previse podataka za sondu");

			}

			break;
		}
		case Gen:
		{
			if (inFile.peek() == EOF || inFile.peek() == '\n')
				throw WrongInput("Morate da unesete frekvenciju za generator");

			double freq;
			inFile >> freq; 

			if (freq == 0.0)
				throw WrongInput("Frekvencija ne moze biti 0");
			if (freq < 0)
				throw WrongInput("Frekvencija ne moze biti negativna");

			g = new GEN(num, freq);
			g->formMoments(duration);
			moments = g->getMoments(); //cuvamo niz bitnih trenutaka ovog generatora

			k = new TreeNode(*g); //formiramo cvor
			tree_.push_back(k); //stavljamo ga u vektor cvorova

			addGenerator(moments, k); //cuvaju se bitni trenutci kada se menja generator u objekte klase Time

			delete g; //brisemo privremeni element

			generators_.push_back(k); //dodavanje u vektor generatora pomocu koga cemo kontrolisati stanja generatora

			while (inFile.peek() != '\n')
			{
				if (inFile.peek() != ' ') //ukoliko se ne stavi enter odmah posle unosenja nego se stave razmaci
					throw WrongInput("Uneli ste previse podataka za generator");

			}
			break;
		}
		case Manual:
		{
			double moment;
			double all = 0;
			m = new MANUAL(num);
			while (inFile.peek() != '\n')
			{
				if (inFile.peek() == EOF)
					throw WrongInput("Nema podataka o vezama");

				inFile >> moment;

				if (moment < 0)
					throw WrongInput("trenutak promene ne moze biti negativan");

				all = all + moment; // posto se unose realtivni trenutci racunamo prave

				if (all < duration)
					m->addMoment(all);
			}
			moments = m->getMoments(); //cuvanje trnutaka promene

			k = new TreeNode(*m); //formiranje cvora i stavljenje u vektor cvorova
			tree_.push_back(k);

			delete m;

			addGenerator(moments, k); //cuvanje bitnih trenutaka u objekte klase Time
			generators_.push_back(k); //stavljanje u vektor generatora

			break;
		}
		case Not:
		{
			n = new NOT(num);
			k = new TreeNode(*n);

			delete n;

			tree_.push_back(k);
			
			while (inFile.peek() != '\n')
			{
				if (inFile.peek() != ' ') //ukoliko se ne stavi enter odmah posle unosenja nego se stave razmaci
					throw WrongInput("NOT moze da ima samo 1 ulaz");

			}

			break;
		}
		case Or:
		{
			int numOfPins = standard;
			if (inFile.peek() != '\n')
				inFile >> numOfPins; //ako je zadat broj ulaza drugaciji od standardnog

			if (numOfPins <= 0)
				throw WrongInput("broj ulaza mora biti pozitvan i veci od 0");

			o = new OR(num, numOfPins);
			k = new TreeNode(*o);

			delete o;

			tree_.push_back(k);

			while (inFile.peek() != '\n')
			{
				if (inFile.peek() != ' ') //ukoliko se ne stavi enter odmah posle unosenja nego se stave razmaci
					throw WrongInput("Uneli ste previse podataka za OR element");

			}
			break;
		}
		case And:
		{
			int numOfPins = standard;
			if (inFile.peek() != '\n')
				inFile >> numOfPins; //ako je zadat broj ulaza drugaciji od standardnog

			a = new AND(num, numOfPins);
			k = new TreeNode(*a);

			delete a;

			tree_.push_back(k);
			
			while(inFile.peek() != '\n')
			{
				if (inFile.peek() != ' ') //ukoliko se ne stavi enter odmah posle unosenja nego se stave razmaci
					throw WrongInput("Uneli ste previse podataka za AND element");

			}

			break;
		}
		default:
		{
			throw WrongInput("Uneli ste nepostojeci tip elementa");
			break;
		}
			
		}
		count++;
	} //IZUZETAK AKO COUNT NIJE NUMOFELEMENTS

	//povezivanje cvorova medjusobom ------------------------------------------------------------------------------
	while (inFile.peek()!=EOF)
	{
			int from, to, s = 0;
			int from_ = -1, to_ = -1;
			inFile >> from >> to >> s;

			for (int i=0; i<tree_.size() ; i++) //trazi ta dva elementa u vektoru tree_ da ih poveze
			{
				if (tree_[i]->getNum() == from) from_ = i;
				if (tree_[i]->getNum() == to) to_ = i;
			}

			if (tree_[to_]->getNumOfChildren() <= s)
				throw WrongInput("Uneti element nema zadati ulaz");

			if (from_ == -1)
				throw WrongInput("Ne postoji element sa unetim rednim brojem za izlaz");
			
			if (to_ == -1)
				throw WrongInput("ne postoji element sa unetim rednim brojem za ulazni element");

			tree_[to_]->addChild(*tree_[from_], s); //dodaje odgovarajuce dete odgovarajucem roditelju na ulaz s
	}
	inFile.close();

	if (generators_.size() == 0)
		throw WrongInput("Ovo kolo ne sadrzi generator");

	sortTimes(); //sortiramo niz trenutaka

	if (sondas_.size() == 0)
		throw WrongInput("Ovo kolo ne sadrzi sonde");
	
	circuit_ = new Tree(sondas_); //drvu prosledjujemo vektor pocetnih cvorova
}

void Simulator::simulate(const string& filepath)
{
	vector<bool> oldState(sondas_.size(), false); //vektor koji cuva stara stanja sonde

	int i = 0, j = 0;
	formW();

	circuit_->interact(); //prvi prolazak kroz drvo u trenurku 0

	//provera da li se nesto promenilo u trenutku 0
	for (auto p : sondas_)
	{
		if (p->getOutput() != oldState[i])
		{
			w_[j]->addMoment(0.0);
			oldState[i] = p->getOutput();
		}
		i++;
		j++;
	}

	for (auto k : times_)
	{
		k->changeState(); //promeni stanja svim generatorima koji treba da se promene u tom trenutku
		circuit_->interact();

		i = 0;
		j = 0;
		for (auto p : sondas_)
		{
			if (p->getOutput() != oldState[i])
			{
				w_[j]->addMoment(k->getT());
				oldState[i] = p->getOutput();
			}
			i++;
			j++;
		}         	
	}

	for (auto k : w_)
	{
		k->write(filepath);
	}

	return;
}

vector<TreeNode*> Simulator::getRoot()
{
	return sondas_;
}

void Simulator::addGenerator(const vector<double> moments, TreeNode* gen)
{
	for (auto k : moments)
	{
		Time* p;
		Time* curr = isMomentInTime(k); //curr ce pokazivati na taj trenutak ako postoji u times_, u suprotnom je nullptr

		if (curr==nullptr) //ovaj trenutak nije pronadjen kao bitan do sad
		{
			p = new Time(k);
			times_.push_back(p); //dodaje se u listu trenutaka
			times_.back()->add(gen); //generator se menja u ovom trnutku pa se dodaje u vector generatora tog trenutka
		}
		else
		{
			curr->add(gen); //vec postoji trenutak samo treba reci da se i ovaj generator menja u tom trenutku
		}
	}
}

void Simulator::formW()
{
	for (auto t: sondas_)
	{
		Writer* p;
		p = new Writer(t->getID());
		w_.push_back(p);
	}
}

void Simulator::sortTimes()
{
	for (int i = 0; i < times_.size() - 1; i++)
	{
		for (int j = i + 1; j < times_.size(); j++)
		{
			if (times_[i]->getT() > times_[j]->getT())
			{
				Time* p;
				p = times_[i];
				times_[i] = times_[j];
				times_[j] = p;
			}
		}
	}
}

Simulator::~Simulator()
{
	for (auto t : tree_) //brise se niz cvorova
	{
		delete t;
	}
	
	for (auto t : w_) //brise se niz writer objekata
	{
		delete t;
	}

	delete circuit_;
	
	for (auto t : times_) //brise se niz time obekata
	{
		delete t;
	}
	
}

Time* Simulator::isMomentInTime(const double moment)
{
	for (auto k : times_)
	{
		if (((k->getT() - moment) < 0.000001) && ((k->getT() - moment) > -0.000001))
			return k;
	}
	return nullptr;
}
