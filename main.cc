// Hoofdprogramma voor oplossing voor eerste po Algoritmiek,
// voorjaar 2019: Mastermind.
//
// Biedt de gebruiker een menustructuur om
// * het spel te spelen, waarbij de gebruiker steeds
//   - een gok kan doen tegen een vooraf opgegeven code,
//   - een optimale gok kan vragen: een gok die het maximale aantal gokken
//     om de code te kraken minimaliseert,
//   - een goede gok kan vragen: een gok die het maximale aantal mogelijk
//     resterende codes na deze gok minimaliseert
// * experimenten te doen
//
// ... (namen studenten)

#include <iostream>
#include <ctime>  // voor clock() en clock_t
#include "standaard.h"
#include "mastermind.h"

//*************************************************************************

// Speel het spel vanaf stand m1.
// Hierbij krijgt de gebruiker herhaaldelijk de keuze om
//   - een gok te doen tegen een vooraf opgegeven code,
//   - een optimale gok te vragen: een gok die het maximale aantal gokken
//     om de code te kraken minimaliseert,
//   - een goede gok te vragen: een gok die het maximale aantal mogelijk
//     resterende codes na deze gok minimaliseert
// Bij de laatste twee opties kan ervoor gekozen worden om wel of niet te
// eisen dat er alleen gokken worden geprobeerd die consistent zijn met
// eerdere resultaten in het spel.
//
// Na iedere gedane gok wordt de stand afgedrukt.
//
// Dit alles gaat door
// * totdat er een eindstand is bereikt (de code is geraden)
// * of totdat de gebruiker aangeeft dat hij wil stoppen met het spel
void doespel (Mastermind *m1)
{ int keuze,
      aantalstanden,  // aantal bekeken standen bij aanroep van optimalegok
      maxaantalgokken,  // maximum aantal gokken (bij een zo slecht mogelijk
                        // resultaat) als we optimale gok uitvoeren
      maxaantalcodes;   // maximum aantal mogelijke codes (bij een zo slecht
                        // mogelijk resultaat) als we goede gok uitvoeren
  char gok[MaxNrGaatjes+1],
       optgok[MaxNrGaatjes+1];
  string goedegok = "";
  bool consistent;
  clock_t t1, t2;

  m1 -> drukaf ();

  keuze = 0;
  while (keuze!=6 && !m1->eindstand())
  {
    cout << endl;
    cout << "1. Een gok doen" << endl;
    cout << "2. Een optimale gok vragen met consistent spel" << endl;
    cout << "3. Een optimale gok vragen zonder verplicht consistent spel"
         << endl;
    cout << "4. Een goede gok vragen met consistent spel" << endl;
    cout << "5. Een goede gok vragen zonder verplicht consistent spel"
         << endl;
    cout << "6. Stoppen met dit spel" << endl;
    cout << endl;
    cout << "Maak een keuze: ";
    cin >> keuze;
    switch (keuze)
    { case 1: cout << endl;
              cout << "Geef de gok: ";
              cin >> gok;
              m1->doegok (gok);
              m1->drukaf ();
              break;
      case 2:
      case 3: consistent = (keuze==2);
              aantalstanden = 0;
              t1 = clock ();
              maxaantalgokken = m1-> optimalegok (consistent, aantalstanden,
                                                  optgok);
              t2 = clock ();

              cout << endl;
              cout << "Optimale gok = " << optgok << endl;
              cout << "Maximum aantal gokken hierbij = " << maxaantalgokken
                   << endl;
              cout << "We hebben hiervoor " << aantalstanden
                   << " standen bekeken." << endl;
              cout << "Dit kostte " << (t2-t1) << " clock ticks, ofwel "
               << (((double)(t2-t1))/CLOCKS_PER_SEC) << " seconden." << endl;
              break;
      case 4:
      case 5: consistent = (keuze==4);
              t1 = clock ();
              maxaantalcodes = m1-> goedegok (consistent, goedegok);
              t2 = clock ();
              cout << endl;
              cout << "Goede gok = " << goedegok << endl;
              cout << "Maximum aantal codes hierbij = " << maxaantalcodes
                   << endl;
              cout << "Dit kostte " << (t2-t1) << " clock ticks, ofwel "
               << (((double)(t2-t1))/CLOCKS_PER_SEC) << " seconden." << endl;
              break;
      case 6: break;
      default: cout << endl;
               cout << "Voer een goede keuze in!" << endl;
    }  // switch

  }  // while

  if (m1->eindstand())
  { cout << endl;
    cout << "De huidige stand is een eindstand.\n";
  }

}  // doespel

//*************************************************************************

// Voert de experimenten uit zoals beschreven in de opdracht.
void doeexperimenten ()
{
  // TODO: implementeer deze functie

}  // doeexperimenten

//*************************************************************************

void hoofdmenu ()
{ Mastermind *m1;  // pointer, om makkeijk nieuwe objecten te kunnen maken
                   // en weer weg te gooien
  int keuze,
      nrkleuren, nrgaatjes, nrrijen;
  char code[MaxNrGaatjes+1];

  do
  {
    cout << endl;
    cout << "1. Een spel spelen" << endl;
    cout << "2. Experimenten doen" << endl;
    cout << "3. Stoppen" << endl;
    cout << endl;
    cout << "Maak een keuze: ";
    cin >> keuze;
    switch (keuze)
    { case 1:
              cout << "Geef een aantal kleuren: ";
              cin >> nrkleuren;
              cout << "Geef een aantal gaatjes: ";
              cin >> nrgaatjes;
              cout << "Geef een aantal rijen op het bord: ";
              cin >> nrrijen;
              if (integerinbereik ("aantal kleuren", nrkleuren, 1, MaxNrKleuren)
               && integerinbereik ("aantal gaatjes", nrgaatjes, 1, MaxNrGaatjes)
               && integerinbereik ("aantal rijen", nrrijen, 1, MaxNrRijen))
                m1 = new Mastermind (nrkleuren, nrgaatjes, nrrijen);
              else
              { cout << "We kiezen standaard aantal kleuren en gaatjes."
                     << endl;
                m1 = new Mastermind ();
              }
              cout << "Geef de geheime code: ";
              cin >> code;
              m1 -> setcode (code);
              doespel (m1);
              delete m1;  // netjes opruimen
              break;
      case 2: doeexperimenten ();
              break;
      case 3: break;
      default: cout << endl;
               cout << "Voer een goede keuze in!" << endl;
    }

  } while (keuze!=3);

}  // hoofdmenu

//*************************************************************************

int main ()
{

  hoofdmenu ();

  return 0;

}
