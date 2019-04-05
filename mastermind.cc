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
    wit.push_back (aantalwit (nwrijtje, code));
    rood.push_back (aantalrood (nwrijtje, code));

    eindstand ();

  } else {
    cout << "Not a valid input" << endl;
  }

}  // doegok

//*************************************************************************

int Mastermind::optimalegok (bool consistent, int &aantalstanden,
                             char optgok[MaxNrGaatjes+1])
{
  // TODO: implementeer deze methode
	vector<int> wit_, rood_;
	int i,j;
	for (i = 0; i < gaatjes; i++) {
		rood_.push_back(i);
		for (j = 0; j < kleuren; ++j) {
			wit_.push_back (j);
			//if (cons (zet) )
			wit_.clear();
		}
	rood_.clear();
	}

	witCheck ();
  return 0;

}  // optimalegok

//*************************************************************************

int Mastermind::goedegok (bool consistent, string &goedegok)
{
  // TODO: implementeer deze methode
  string zet = "";
  int i, j, l, p, o, aantal_codes = 0, aantal2 = 100000, rood_aantal = 0;


  for (l = 0; l < kleuren; l++) {
    if (gaatjes < 5) l = kleuren;
    for (p = 0; p < kleuren; p++) {
      if (gaatjes < 4) p = kleuren;
      for (o = 0; o < kleuren; o++) {
        if (gaatjes < 3) o = kleuren;
        for (i = 0; i < kleuren; i++) {
          if (gaatjes < 2) i = kleuren;
          for (j = 0; j < kleuren; j++) {
            switch (gaatjes) {
              case 1:
              zet =   to_string (j);
              break;
              case 2:
              zet =   to_string (i) + to_string(j);
              break;
              case 3:
              zet =   to_string (o) + to_string (i) + to_string(j);
              break;
              case 4:
              zet =   to_string (p) + to_string (o) + to_string (i)
                    + to_string(j);
              break;
              case 5:
              zet =   to_string (l) + to_string (p) + to_string (o)
                    + to_string (i) + to_string (j);
            }
            if (cons (zet, rood_aantal) && consistent) {
              aantal_codes = mogelijkheden (rood_aantal);


                if (aantal_codes <= aantal2) {
                  aantal2 = aantal_codes;
                  goedegok = zet;
                }
            }
          }
        }
      }
    }
  }
  return aantal2;

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
  return aantalwit;
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

bool Mastermind::cons (string zet, int &rood_aantal) {
  unsigned int i;

  for (i = 0; i < guess.size (); i++) {
    if (zet == guess[i]) return false;
  }

  for (i = 0; i < guess.size (); i++) {
    int wit_zet = aantalwit (zet, guess[i]);
    int rood_zet = aantalrood (zet, guess[i]);
    if (wit_zet == wit[i]) {
      if (rood_zet == rood[i]) {
        rood_aantal = rood_zet;

        return true;
      }
    }
  }
  return false;
}

//*************************************************************************

int Mastermind::mogelijkheden (int rood_aantal) {
  //formule = aantal kleuren ^  (max gaatjes - aantal rode gaatjes dat de gok heeft opgevuld)

  return pow (kleuren, gaatjes - rood_aantal);
}

void Mastermind::doezet () {

int i, j;
vector<int> zet;
bool ongoing = true, check = true;

	for (int k = 0; k < gaatjes; k++) zet.push_back(0); //gaatjes is 3 zet[0] = 0, zet[1] = 0, zet[2] = 0;		

	while(ongoing){
		check = true;
		for(i=0;i<kleuren;i++){
			zet[0]= i;
			cout << zet[0] << zet[1] << zet[2] << endl;
			//doezet();
		}
			j = 1;
			while(check) {

				if(zet[j] < kleuren - 1) {
					zet[j]++;
					check = false;
				
				} else {
						 if(j < gaatjes - 1) {
							j++;
			
							}
						 
						 else {check = false; ongoing = false; zet.clear(); }
		 
	}
}
   

}



}

//****************************************************************************


bool Mastermind::witCheck () {
vector<int> opslag;
string zet, test;
opslag.push_back(-1);
bool erin = false;
int teller = 0;
int j,i,k;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
		if (zet[i] == test[j]){ 
			for(k=0;k<=teller;k++){
       if (opslag[k] == zet[i])
			   j=0;k=teller;erin = true;
}
			if(erin){
				opslag[teller] = zet[i];teller++;
				erin = false;
		}		
	
	} 
}
cout << " " 

}
}

#endif
