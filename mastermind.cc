// Implementatie van klasse Mastermind.

#ifndef MastermindCCVar
#define MastermindCCVar

#include <iostream>
#include "mastermind.h"

using namespace std;

//*************************************************************************

Mastermind::Mastermind ()
{
  kleuren = MaxNrKleuren;
  gaatjes = MaxNrGaatjes;
  rijen = MaxNrRijen;

}  // Mastermind

//*************************************************************************

Mastermind::Mastermind (int nwnrkleuren, int nwnrgaatjes,
                        int nwnrrijen)
{
  kleuren = nwnrkleuren;
  gaatjes = nwnrgaatjes;
  rijen = nwnrrijen;


}  // Mastermind (nwnrkleuren, nwnrgaatjes, nwnrrijen)

//*************************************************************************

Mastermind::~Mastermind ()
{
  // TODO: implementeer, indien van toepassing, deze destructor

}  // Destructor.

//*************************************************************************

void Mastermind::setcode (char *rijtje)
{
  if (geldigeGok (rijtje) ) {
    code = rijtje;
  } else {
    cout << "Not a valid input" << endl;
  }

}  // setcode

//*************************************************************************

void Mastermind::drukaf ()
{

  if (guess.size() < 1 )  return;
  cout << "Gok:       wit:        rood:" << endl;

  for (unsigned int i = 0; i < guess.size(); i++) {
    for (unsigned int j = 0; j < guess[0].size(); j++) {
      cout << guess[i][j] << " ";
    }
    cout << "        " <<  wit[i] << "       " << rood[i] << endl;
  }
}  // drukaf

//*************************************************************************

bool Mastermind::eindstand ()
{
  // TODO: implementeer deze methode
  if (guess.size () < 1) return false;
  if (rood[guess.size() - 1] == gaatjes) {
    return true;
  } else if ((unsigned)rijen == guess.size ()) {
    cout << "Helaas je hebt verloren, de code was " << code << endl;
    return true;
  }

  return false;

}  // eindstand

//*************************************************************************

void Mastermind::doegok (string nwrijtje)
{

  if (geldigeGok (nwrijtje) ) {

    guess.push_back (nwrijtje);
    rood.push_back (aantalrood (nwrijtje, code));
    wit.push_back (aantalwit (nwrijtje, code));

    eindstand ();

  } else {
    cout << "Not a valid input" << endl;
  }

}  // doegok

//*************************************************************************

int Mastermind::goedegok(bool consistent, string &optgok)
{
  // TODO: implementeer deze methode
  string strZet1,strZet2, besteGok = "";
  int teller = 0, i, j;
  unsigned int l, k;
  if(guess.size() == 0){
    vector<int> zet;
    for(i=0;i<gaatjes;i++){
        j = i % kleuren;
        cout << j << endl;
        zet.push_back(j);
    }
    optgok = stringify(zet);

    return 0;
  }
  int ranRood, ranWit, aantalmax = -1,aantalmin = -1;
  cout << "1::::1" << endl;
	doezet(consistent);
  cout << "2::::2" << endl;
  cout << zetten.size() << "hierrrrrrrrrrrrrrrrrr" << endl;
  for(l = 0; l < zetten.size(); l++){
  for (i = 0; i < gaatjes; i++) {
		for (j = 0; j < kleuren; ++j) {
			if(i+j <= gaatjes){
          for(k = 0; k < zetten.size(); k++){
            if(l != k){
              strZet1 = zetten[l];
              //strZet1 = to_string(zetten[l]);
              strZet2 = zetten[k];
            ranRood = roodCheck(strZet1,strZet2);
              ranWit = witCheck(strZet1,strZet2);
              if(ranRood == i && ranWit == j){
                teller++;
          }
      }
    }

      if(aantalmax < teller || aantalmax == -1){
        aantalmax = teller;
      }
    }
      }
		}
    if((aantalmin > aantalmax || aantalmin == -1) && aantalmax != -1 && zetten[l] != guess[guess.size()-1]){
      aantalmin = aantalmax;
      besteGok = zetten[l];
    }
    aantalmax = -1;
	}
  optgok = besteGok;

  return 0;

}  // optimalegok

//*************************************************************************

int Mastermind::optimalegok(bool consistent, int &aantalstanden, string &optgok)
{
  // TODO: implementeer deze methode
  string strZet1,strZet2, besteGok = "";
  int teller = 0, i, j;
  unsigned int l, k;
  if(guess.size() == 0){
    vector<int> zet;
    for(i=0;i<gaatjes;i++){
        j = i % kleuren;
        cout << j << endl;
        zet.push_back(j);
    }
    optgok = stringify(zet);
    return 0;
  }

  int ranRood, ranWit, aantalmax = -1,aantalmin = -1;
  cout << "1::::1" << endl;
    doezet(consistent);
  cout << "2::::2" << endl;
  cout << zetten.size() << "hierrrrrrrrrrrrrrrrrr" << endl;
  for(l = 0; l < zetten.size(); l++){
  for (i = 0; i < gaatjes; i++) {
		for (j = 0; j < kleuren; ++j) {
			if(i+j <= gaatjes){
          for(k = 0; k < zetten.size(); k++){
            if(l != k){
              strZet1 = zetten[l];
              //strZet1 = to_string(zetten[l]);
              strZet2 = zetten[k];
            ranRood = roodCheck(strZet1,strZet2);
              ranWit = witCheck(strZet1,strZet2);
              if(ranRood == i && ranWit == j){
                if(aantalstanden != rijen){
                aantalstanden++;
                teller = optimalegok(consistent,aantalstanden,optgok);
                }
                else{
                aantalstanden--;
                return 0;
                }
          }
      }
    }

      if(aantalmax < teller || aantalmax == -1){
        aantalmax = teller;
      }
    }
      }
		}
    if((aantalmin > aantalmax || aantalmin == -1) && aantalmax != -1 && zetten[l] != guess[guess.size()-1]){
      aantalmin = aantalmax;
      besteGok = zetten[l];
    }
    optgok = besteGok;
    return teller+1;
    aantalmax = -1;
	}
  optgok = besteGok;
  return 0;

}  // goedegok

//*************************************************************************

bool Mastermind::geldigeGok (string rijtje) {

  if (rijtje.length () == (unsigned int) gaatjes) {
    for (unsigned int i = 0; i < rijtje.length () ; i++) {
      if (rijtje[i] - '0' > kleuren - 1) {
        cout << rijtje[i] << " mag niet" << " max is: " << kleuren - 1 << endl;
        return false;
      }
    }
  } else {
    return false;
  }
  return true;
}

//*************************************************************************

int Mastermind::aantalrood (string rijtje, string test) {
int aantalrood = 0;
  for (unsigned int i = 0; i < rijtje.length (); i++) {
    if (rijtje[i] == test[i]) {
      aantalrood++;
    }
  }
  return aantalrood;
}

//*************************************************************************

int Mastermind::aantalwit (string rijtje, string test) {
int aantalwit = 0;
  for (int j = 0; j < kleuren; j++) {
    //if j elemnt of rijtje && elem of code then wit++
    if(elementOf (rijtje, j) > 0 && elementOf (test, j) > 0) aantalwit++;
  }
  if(rood.back() == gaatjes) return 0;
  return aantalwit-rood.back();
}

//*************************************************************************

int Mastermind::elementOf (string test, int elem) {
  int aantal = 0;
  for (unsigned int i = 0; i < test.length (); i++) {
    if (test[i] - '0' == elem) aantal++;
  }
  return aantal;
}

//*************************************************************************

bool Mastermind::cons (string zet, int &aantal) {
  unsigned int i, j, k;
  int wit_,rood_;
  std::vector<int> whites, reds;
  for (i = 0; i < guess.size (); i++) {
    if (zet == guess[i]) return false;
  }
for(k=0; k< guess.size(); k++){

	for (i = 0; i < gaatjes; i++) {
		reds.push_back(i);
		for (j = 0; j < kleuren; ++j) {
			whites.push_back (j);
			rood_ = roodCheck(zet,guess[k]);
      wit_ = witCheck(zet,guess[k]);

			whites.clear();
		}
	reds.clear();
	}
}
  if (rood_ != wit_ ) cout << "Geen warning pls" << endl;
  return true;
}

//*************************************************************************

int Mastermind::mogelijkheden (int rood_aantal) {
  //formule = aantal kleuren ^  (max gaatjes - aantal rode gaatjes dat de gok heeft opgevuld)

  return pow (kleuren, gaatjes - rood_aantal);
}



void Mastermind::doezet (bool consistent) {
zetten.clear();
string str = "";
int i, l, j, k = 0;
int witter,rooder;
vector<int> zet;
bool ongoing = true, check = true,kann = true;

for (k = 0; k < gaatjes; k++) zet.push_back(0); //gaatjes is 3 zet[0] = 0, zet[1] = 0, zet[2] = 0;

while(ongoing){
 check = true;
 for(i = 0; i < kleuren; i++) {
  zet[0]= i;
      str = stringify(zet);
      cout << "str: " << str << endl;
      if(consistent){
        for(l=1;l<=guess.size();l++){
            witter = witCheck(str,guess[guess.size()-l]);
            rooder = roodCheck(str,guess[guess.size()-l]);
            cout << guess[guess.size()-l] << endl;
            cout << rood[rood.size()-l] << endl;
      cout << wit[wit.size()-l] << endl;
      cout << rooder << endl;
      cout << witter << endl;
            if(rood[rood.size()-l] != rooder || wit[wit.size()-l] != witter || str == guess[guess.size()-l]){
                kann = false;
            }
        }
        if(kann){
            zetten.push_back(str);
        }
        kann = true;
      }
      else{
      witter = witCheck(str,guess[guess.size()-1]);
      cout << guess[guess.size()-1] << endl;
      rooder = roodCheck(str,guess[guess.size()-1]);
      cout << rood[rood.size()-1] << endl;
      cout << wit[wit.size()-1] << endl;
      cout << rooder << endl;
      cout << witter << endl;
      if(rood[rood.size()-1] == rooder && wit[wit.size()-1] == witter){
        for(l=1;l<=guess.size();l++){
            if(str == guess[guess.size()-l]){
                kann = false;
            }
        }
        if(kann){
        zetten.push_back(str);
        }
        kann = true;
      }
      }
 }
 j = 1;
 while (check) {
  if (zet[j] < kleuren - 1) {
   zet[j]++;
   check = false;
  }
      else {
     if (j < gaatjes - 1) {
        zet[j] = 0;
       j++;
        } else {
           check = false;
           ongoing = false;
           zet.clear();
         }
    }
    }
  }
}

//****************************************************************************



int Mastermind::roodCheck(string str,string test){
  int i,teller = 0;
  for(i=0;i<gaatjes;i++){
    if(str[i]==test[i]){
      teller++;
    }
  }
  return teller;

}

int Mastermind::witCheck (string str,string test) {
vector<char> opslag;
opslag.push_back('E');
bool erin = false;
int teller = 0,minteller = 0;
int j,i,k;
    for(i=0;i<gaatjes;i++){
    if(str[i]==test[i]){
      opslag.push_back(str[i]);
      teller++;
      minteller++;
    }
  }
	for (i = 0; i < gaatjes ; i++) {
		for (j = 0; j < gaatjes ; j++) {
		if (str[i] == test[j] && str[j] != test[j] && str[i] != test[i]){
			for(k=0;k<=teller;k++){
       if (opslag[k] == str[i]) { // was eerst zet[i][i] heb hier maar zetten van gemaakt not sure wat dit doet.
         k=teller;
         erin = true;
       }
     }
			if(!erin){
                cout << str[i] << endl;
				opslag.push_back(str[i]);
                teller++;
		    }
		    erin = false;
	     }
     }


   }
teller -= minteller;
opslag.clear();
return teller;
}

string Mastermind::stringify (std::vector<int> v) {
  unsigned int i;
  string temp = "";
  for (i = 0; i < v.size (); i++) {
    temp += to_string(v[i]);
  }
  return temp;
}

#endif
