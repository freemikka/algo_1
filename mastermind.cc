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
/*
int goedegok(bool consistent, string &optgok): genereert een goede gok voor mastermind.
strZet1,strZet2: de zetten van de vector zetten. beide strings worden gebruikt in witCheck en roodCheck.
BesteGok: string voor de beste gok.
ranRood,ranWit: de resultaten tussen de zetten in vector zetten (aantal rode/witte pinnen).
aantalmax,aantalmin: aantalmax pakt de hoogste aantal codes van de zet. aantalmin pakt de laagste aantalmax van alle zetten.
*/
int Mastermind::goedegok(bool consistent, string &optgok)
{
  string strZet1,strZet2, besteGok = "";
  int teller = 0, i, j;
  unsigned int l, k;
  vector<int> zet;
  //Random zet maken in het geval dat er geen begintoestand is
  if(guess.size() == 0){
    for(i=0;i<gaatjes;i++){
        j = i % kleuren;
        zet.push_back(j);
    }
    optgok = stringify(zet);

    return 0;
  }
  int ranRood, ranWit, aantalmax = -1,aantalmin = -1;
	doezet(consistent);
  for(l = 0; l < zetten.size(); l++){
    for (i = 0; i < gaatjes; i++) {
  		for (j = 0; j < kleuren; ++j) {
  			if(i+j <= gaatjes){
            for(k = 0; k < zetten.size(); k++){
              if(l != k){
                strZet1 = zetten[l];
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

  return zetten.size();

}  // optimalegok

//*************************************************************************
/*
int Mastermind::optimalegok(bool consistent, int &aantalstanden, string &optgok): genereert een optimale gok voor mastermind.
strZet1,strZet2: de zetten van de vector zetten. beide strings worden gebruikt in witCheck en roodCheck.
BesteGok: string voor de beste gok.
ranRood,ranWit: de resultaten tussen de zetten in vector zetten (aantal rode/witte pinnen).
aantalmax,aantalmin: aantalmax pakt de hoogste aantal codes van de zet. aantalmin pakt de laagste aantalmax van alle zetten.
*/
int Mastermind::optimalegok(bool consistent, int &aantalstanden, string &optgok)
{
  string strZet1,strZet2, besteGok = "";
  int teller = 0, i, j;
  unsigned int l, k;
  //Random zet maken in het geval dat er geen begintoestand is
  if(guess.size() == 0){
    vector<int> zet;
    for(i=0;i<gaatjes;i++){
        j = i % kleuren;
        zet.push_back(j);
    }
    optgok = stringify(zet);
    return 0;
  }

  int ranRood, ranWit, aantalmax = -1,aantalmin = -1;
  doezet(consistent);
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
  return zetten.size();

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
      position.push_back (i);
    }
  }
  return aantalrood;
}

//*************************************************************************

int Mastermind::aantalwit (string rijtje, string test) {
  int aantal = 0;
  for (int i = 0; i < gaatjes; i++) {
    for (int j = 0; j < gaatjes; j++) {
      if (rijtje[i] == test[j] && notIn(rijtje[i], kleurtjes) && notPosition(i, j)) {
        aantal++;
        kleurtjes.push_back(rijtje[i]);
      }
    }
  }
  position.clear();
  kleurtjes.clear();
  return aantal;
}

//*************************************************************************

int Mastermind::notPosition (int index, int index2) {
  for (unsigned int i = 0; i < position.size(); i++) {
    if (index == position[i] || index2 == position[i]) return false;
  }

  return true;
}


bool Mastermind::notIn(int el, vector<int> seen) {
  unsigned int i;
  for (i = 0; i < seen.size(); ++i) {
    if(el == seen[i] || seen.size() == 0) return false;
  }
  return true;
}

//*************************************************************************
/*
void Mastermind::doezet (bool consistent): genereert zetten voor vector zetten die mogelijk zijn voor optimale/goede gok.
str,zet: gebruikt om alle zetten op te slaan in een tijdelijke string of vector<int>.
witter,rooder: worden de aantal witte/rode pinnen opgeslagen tussen vorige zetten en alle mogelijke zetten.
ongoing,check: zorgt ervoor dat alle zetten geprobeerd worden.
kann: kijkt of een zet wel mogelijk is (oftewel niet consistent bij consistent = true of zet niet eerder gebruikt is etc)
*/
void Mastermind::doezet (bool consistent) {
zetten.clear();
string str = "";
int i, j, k = 0;
unsigned int l;
int witter,rooder;
vector<int> zet;
bool ongoing = true, check = true,kann = true;

for (k = 0; k < gaatjes; k++) zet.push_back(0); //gaatjes is 3 zet[0] = 0, zet[1] = 0, zet[2] = 0;

while(ongoing){
 check = true;
 for(i = 0; i < kleuren; i++) {
  zet[0]= i;
      str = stringify(zet);
// als consistent, checkt de functie alle resultaten inplaats van alleen maar de vorige resultaat.
      if(consistent){
        for(l=1;l<=guess.size();l++){
            witter = witCheck(str,guess[guess.size()-l]);
            rooder = roodCheck(str,guess[guess.size()-l]);

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
      rooder = roodCheck(str,guess[guess.size()-1]);

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

/*
int roodCheck(string str,string test): kijkt naar de twee codes str en test, vervolgens returned aantal rode pinnen voor de twee strings.
teller: telt aantal rode pinnen.
*/
int Mastermind::roodCheck(string str,string test){
  int i,teller = 0;
  for(i=0;i<gaatjes;i++){
    if(str[i]==test[i]){
      teller++;
    }
  }
  return teller;

}

//*************************************************************************
/*
int witCheck(string str,string test): kijkt naar de twee codes str en test, vervolgens returned aantal witte pinnen voor de twee strings.
opslag: als een kleur al gespot is wordt die in opslag opgeslagen, als dezelfde kleur weer wordt gezien zal die niet opgeteld worden bij witte pinnen.
teller,minteller: tellen aantal witte pinnen.
erin: of een kleur al in opslag zit, zo niet wordt de kleur in opslag gestopt en teller++.
*/
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

//*************************************************************************

string Mastermind::stringify (std::vector<int> v) {
  unsigned int i;
  string temp = "";
  for (i = 0; i < v.size (); i++) {
    temp += to_string(v[i]);
  }
  return temp;
}

#endif
