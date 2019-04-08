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
  char gok[MaxNrGaatjes+1];

  string optgok = "";
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

void doeexperimenten ()
{
  // TODO: implementeer deze functie
    Mastermind *m2;
    int keuze,aantalstanden = 0;
    string optgok = "";
    string goedegok = "";
    char code[MaxNrGaatjes+1];
    bool consistent = true;
    int rijteller,aantalrijen, i, j;
    cout << endl;
    cout << "1. Experiment 1 - niet consistent" << endl;
    cout << "2. Experiment 1 - consistent" << endl;
    cout << "3. Experiment 2 - niet consistent" << endl;
    cout << "4. Experiment 2 - consistent" << endl;
    cout << "5. Experiment 3 - niet consistent" << endl;
    cout << "6. Experiment 3 - consistent" << endl;
    cout << "7. Experiment 4 - consistent" << endl;
    cout << "Maak een keuze:";
    cin >> keuze;
    clock_t t1, t2;
    switch (keuze)
    {
    case 1:
    case 2:
        consistent = (keuze==2);
        rijteller = 0;
        aantalrijen = 4;
        m2 = new Mastermind(3,3,aantalrijen);
        cout << "geheime code:";
        cin >> code;
        m2 -> setcode (code);
        t1 = clock ();
        while(rijteller != aantalrijen && !m2->eindstand()){
        m2-> optimalegok (consistent, aantalstanden, optgok);
        m2->doegok (optgok);
        m2->drukaf ();
        rijteller++;
        }
        if(m2->eindstand()){
            m2->eindstand();
        }
        else if(rijteller == aantalrijen){
            cout << "maxaantalrijen" << endl;
        }
        t2 = clock ();
        cout << "Dit kostte " << (t2-t1) << " clock ticks, ofwel "
               << (((double)(t2-t1))/CLOCKS_PER_SEC) << " seconden." << endl;
        break;
    case 3:
    case 4:
    case 5:
    case 6:
        consistent = (keuze==4 || keuze==6);
        rijteller = 0;
        aantalrijen = 10;
        m2 = new Mastermind(6,4,aantalrijen);
        if(keuze == 3 || keuze == 4){
        cout << "geheime code:";
        cin >> code;
        m2 -> setcode (code);
        }
        else{
        code[0] = '1';
        code[1] = '0';
        code[2] = '2';
        code[3] = '5';
        m2 -> setcode(code);
        }
        t1 = clock ();
        while(rijteller != aantalrijen && !m2->eindstand()){
        m2-> goedegok (consistent, goedegok);
        m2->doegok (goedegok);
        m2->drukaf ();
        rijteller++;
        }
        if(m2->eindstand()){
            m2->eindstand();
        }
        else if(rijteller == aantalrijen){
            cout << "maxaantalrijen" << endl;
        }
        t2 = clock ();
        cout << "Dit kostte " << (t2-t1) << " clock ticks, ofwel "
               << (((double)(t2-t1))/CLOCKS_PER_SEC) << " seconden." << endl;
        break;

    case 7:
        consistent = true;
        for(i =1; i < 10; i++){
            for(j=1 ; j < 10; j++){
        rijteller = 0;
        aantalrijen = 5;
        m2 = new Mastermind(i,j,aantalrijen);
        cout << "geheime code:";
        cin >> code;
        m2 -> setcode (code);
        t1 = clock ();
        while(rijteller != aantalrijen && !m2->eindstand()){
        m2-> optimalegok (consistent, aantalstanden, optgok);
        m2->doegok (optgok);
        m2->drukaf ();
        rijteller++;
        }
        if(m2->eindstand()){
            m2->eindstand();
        }
        else if(rijteller == aantalrijen){
            cout << "maxaantalrijen" << endl;
        }
        t2 = clock ();
        cout << "Dit kostte " << (t2-t1) << " clock ticks, ofwel "
               << (((double)(t2-t1))/CLOCKS_PER_SEC) << " seconden." << endl;

            }
        }
        break;
    }
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

// 0001 2
// 1000 2
int main ()
{

  hoofdmenu();
  return 0;

}
