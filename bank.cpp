#include <iostream>
#include <vector>
#include <typeinfo>

using namespace std;

class ContBancar {
protected:
	string numeDetinator;
	string dataDeschi;
	float sold;
public:
	ContBancar() {
		sold = 0;
	}
	ContBancar(string _dataDeschi, string _numeDetinator) {
		dataDeschi = _dataDeschi; numeDetinator = _numeDetinator; sold = 0;
	}
	ContBancar(const ContBancar &obiect) {
		numeDetinator = obiect.numeDetinator; dataDeschi = obiect.dataDeschi; sold = obiect.sold;
	}
	virtual void afisare();

	ContBancar operator = (ContBancar);

	friend void citire(ContBancar &obiect);

};

void citire(ContBancar &obiect) {
	cout << "Nume detinator: ";
	cin >> obiect.numeDetinator;
	cout << "Data deschiderii: ";
	cin >> obiect.dataDeschi;
}

ContBancar ContBancar::operator = (ContBancar obiect)
{
	this->numeDetinator = obiect.numeDetinator;
	this->dataDeschi = obiect.dataDeschi;
	this->sold = obiect.sold;
	return *this;
}

void ContBancar::afisare() {
	cout << "Nume: " << numeDetinator << endl << "Data deschiderii: " << dataDeschi << endl << "Sold: " << sold << endl;
}

class ContEconomii :public ContBancar {
	int luniDobanda;
	float procentDobanda;
	vector<float>istoric;
public:
    ContEconomii():ContBancar(){

    }
	ContEconomii(string _dataDeschi, string _numeDetinator) :ContBancar(_dataDeschi, _numeDetinator) {
		istoric.push_back(sold);
	}
	void afisare();
	ContEconomii operator = (ContEconomii);
	friend void citire(ContEconomii &obiect);
	void retrage(float suma);
	void depune(float suma);
	void getIstoric();
};

void ContEconomii::depune(float suma) {
	sold += suma;
	istoric.push_back(sold);
}

void ContEconomii::getIstoric() {
    cout << "Istoric sold"<<endl;
	vector<float>::iterator i;

	for (i = istoric.begin(); i != istoric.end(); i++) {
		cout <<" -> "<< *i << " ";
	}
	cout << endl;
}

void ContEconomii::retrage(float suma) {
	sold -= suma;
	istoric.push_back(sold);
}

void citire(ContEconomii &obiect) {
    cout << "Nume detinator: ";
    cin >> obiect.numeDetinator;
    cout << "Data deschiderii: ";
    cin >> obiect.dataDeschi;
	cout << "Luni dobanda: ";
	cin >> obiect.luniDobanda;
	cout << "Procent dobanda: ";
	cin >> obiect.procentDobanda;
}

ContEconomii ContEconomii::operator = (ContEconomii obiect)
{
	this->numeDetinator = obiect.numeDetinator;
	this->dataDeschi = obiect.dataDeschi;
	this->sold = obiect.sold;
	this->luniDobanda = obiect.luniDobanda;
	this->procentDobanda = obiect.procentDobanda;
	return *this;
}

void ContEconomii::afisare() {
	ContBancar::afisare();
	cout << "Dobanda calculata la " << luniDobanda << " luni" << endl << "Dobanda: " << procentDobanda * 100 << "%" << endl;
}

class ContCurent :public ContBancar {
	int tranzactiiGratuite;
	float comision;
public:
    ContCurent():ContBancar(){

    }
	ContCurent(string _dataDeschi, string _numeDetinator) :ContBancar(_dataDeschi, _numeDetinator) {

	}
	void afisare();

	ContCurent operator = (ContCurent);

	friend void citire(ContCurent &obiect);

	void depune(float suma); ///depuneri gratuite
	void retrage(float suma); ///1$ retragere peste numarul de tranzactii gratuite

};

void ContCurent::retrage(float suma) {
	sold -= suma;
	if (tranzactiiGratuite < 0) {
		sold -= 1;
	}
}

void ContCurent::depune(float suma) {
	sold -= suma;
}

void citire(ContCurent &obiect) {
    cout << "Nume detinator: ";
    cin >> obiect.numeDetinator;
    cout << "Data deschiderii: ";
    cin >> obiect.dataDeschi;
	cout << "Numar tranzactii gratuite: ";
	cin >> obiect.tranzactiiGratuite;
	cout << "Comision: ";
	cin >> obiect.comision;
}

ContCurent ContCurent::operator = (ContCurent obiect)
{
	this->numeDetinator = obiect.numeDetinator;
	this->dataDeschi = obiect.dataDeschi;
	this->sold = obiect.sold;
	this->tranzactiiGratuite = obiect.tranzactiiGratuite;
	this->comision = obiect.comision;
	return *this;
}

void ContCurent::afisare() {
	ContBancar::afisare();
	cout << "Tranzactii gratuite ramase: " << tranzactiiGratuite << endl << "Comision tranzactie: " << comision * 100 << "%" << endl;
}


template <class Tip>
class GestionareConturi{
    static Tip index;
    ContBancar** v;
    int currentPos = 0;
    int nrConturi;
    void cresteIndex(){
        index++;
    }
public:
    GestionareConturi(int nrConturi){
        this->nrConturi = nrConturi;
        cout<<"Template"<<endl;
        v = new ContBancar *[nrConturi];
    }
    operator+=(ContBancar &ob) {
        v[currentPos] = &ob;
        cresteIndex();
        currentPos = index - '\0';
    }
    void afisare(){
        cout<<endl;
        ContBancar cb;
        ContEconomii ce;
        ContCurent cc;
        for(int i = 0; i < nrConturi; i++){
            if(typeid(*v[i]) == typeid(cb)){
                ContBancar *out = dynamic_cast<ContBancar *>(v[i]);
                out->afisare();
                cout<<endl;
            }if(typeid(*v[i]) == typeid(ce)){
                ContEconomii *out = dynamic_cast<ContEconomii *>(v[i]);
                out->depune(500);
                out->depune(700);
                out->retrage(20);
                out->getIstoric();
                out->afisare();
                cout<<endl;
            }if(typeid(*v[i]) == typeid(cc)){
                ContCurent *out = dynamic_cast<ContCurent *>(v[i]);
                out->afisare();
                cout<<endl;
            }
        }
    }
    void citireDate(){
        int optiune;
        for(int i = 0; i < nrConturi; i++){
            cout<<"1 -> Cont Bancar, 2 -> Cont Economii, 3-> Cont Curent"<<endl;
            cin>>optiune;
            switch(optiune){
                case 1:{
                    ContBancar *c = new ContBancar();
                    citire(*c);
                    *this += *c;
                    break;
                }
                case 2: {
                    ContEconomii *c = new ContEconomii();
                    citire(*c);
                    *this += *c;
                    break;
                }
                case 3: {
                    ContCurent *c = new ContCurent();
                    citire(*c);
                    *this += *c;
                    break;
                }

            }
        }
    }

};
template <class Tip>
Tip GestionareConturi<Tip>::index = 0;

template <>
class GestionareConturi<int>{
    static int index;
    ContBancar** v;
    void cresteIndex(){
        index++;
    }
public:
    GestionareConturi(int nrConturi){
        cout<<"Specializare";
        if(nrConturi < 0){
            try{
                throw 20;
            }
            catch(int e){
                cout<<"Numarul conturilor nu poate fi negativ, eroarea numarul: "<<e;
            }
        }
        else {
            v = new ContBancar *[nrConturi];
        }
    }
     operator+=(ContBancar &ob){
        cresteIndex();
    }

};

template <>
int GestionareConturi<int>::index = 0;

int main()
{
    int nrConturi;
    cout<<"Cate conturi?"<<endl;
    cin>>nrConturi;
    GestionareConturi<char> gc(nrConturi);
    gc.citireDate();
    gc.afisare();
	return 0;
}
