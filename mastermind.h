// Definitie van klasse Mastermind.

#ifndef MastermindHVar  // om te voorkomen dat dit .h bestand meerdere keren
#define MastermindHVar  // wordt ge-include

#include <string>
#include <vector>
#include <stdlib.h>
#include <math.h> //voor pow
using namespace std;

const char EersteKleurKar = '0';  // om flexibel te zijn met keuze
                                  // van alfabet van kleuren
const int MaxNrKleuren = 10;  // moet minstens 6 zijn voor standaard spel
const int MaxNrGaatjes = 6;   // moet minstens 4 zijn voor standaard spel
const int MaxNrRijen = 20; // moet minstens 10 zijn voor standaard spel;
                            // makkelijk om stapel in een array te implementeren

class Mastermind
{
  public:
    // Default constructor.
    Mastermind ();

    // Constructor met parameters.
    Mastermind (int nwnrkleuren, int nwnrgaatjes, int nwnrrijen);

    // Destructor, indien van toepassing.
    ~Mastermind ();

    // Zet code.
    // Controleer tevoren nog wel of rijtje een geldige code is voor
    // het huidige spel.
    void setcode (char *rijtje);

    // Druk de hele stand (stapel met gedane gokken en resultaten)
    // af op het scherm.
    void drukaf ();

    // Controleer of de huidige stand een eindstand is, dat wil zeggen:
    // of bovenop de stapel een patroon staat dat gelijk is aan de code
    // (los van de vraag of er een resultaat bij staat).
    bool eindstand ();

    // Doe de gok met nwrijtje.
    // Voeg de gok met het bijbehorende resultaat toe aan de stapel,
    // die de huidige stand van het spel weergeeft.
    // Controleer tevoren nog wel of nwrijtje een geldige gok is voor
    // het huidige spel.
    void doegok (string nwrijtje);

    // Gebruik brute force om, uitgaande van de huidige stand, een optimale
    // gok te bepalen: een gok die het benodigde aantal gokken/stappen om
    // de code te raden minimaliseert, ook bij `zo slecht mogelijke' resultaten.
    // Daarbij beperken we ons wel of niet tot consistente gokken
    // (afhankelijk van parameter `consistent').
    // Hoog parameter aantalstanden op met het aantal standen dat we hierbij
    // bekijken.
    // De optimale gok zelf retourneren we in parameter optgok.
    // Retourneer:
    // * minimale aantal gokken/stappen om code te raden, in slechtste geval
    int optimalegok (bool consistent, int &aantalstanden,
                    string &optgok);

    // Bepaal, uitgaande van de huidige stand, een goede gok:
    // een gok die het aantal nog mogelijke codes minimaliseert,
    // ook bij een `zo slecht mogelijk' resultaat.
    // Daarbij beperken we ons wel of niet tot consistente gokken
    // (afhankelijk van parameter `consistent').
    // De goede gok zelf retourneren we in optgok.
    // Retourneer:
    // * het aantal nog mogelijke codes bij de goede gok, bij een zo slecht
    //   mogelijk resultaat
    int goedegok (bool consistent, string &goedegok);

  private:
    int kleuren, gaatjes, rijen;
    string code;
    vector<string> guess;
    vector<string> zetten;
    vector<int> wit, rood, position, kleurtjes;

    bool notIn(int el, vector<int> seen);
    int aantalwit (string rijtje, string test);
    int notPosition (int index, int index2);






    // Controleerd of de code geldig is
    // Retourneerd true als er de code correct ingevoerd is.
    bool geldigeGok (string rijtje);

    // Deze functie vult de rode en witte pinnen in.
    int aantalrood (string rijtje, string test);
    int roodCheck(string str,string test);
    int witCheck (string str,string test);
    // Helper functie van aantaljuist.
    // checkt of een element in de string zit.
    int elementOf (string test, int elem);

    bool cons (string zet, int &aantal);

    int mogelijkheden (int rood_aantal);
		void doezet (bool consistent);
    string stringify (std::vector<int> v);

};

#endif
