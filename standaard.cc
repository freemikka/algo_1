// Implementatie van standaard functies.

#ifndef StandaardCCVar
#define StandaardCCVar

#include <iostream>
#include "standaard.h"
using namespace std;

//*************************************************************************

bool integerinbereik (const char *variabele, int waarde,
                      int minWaarde, int maxWaarde)
{
  if (waarde>=minWaarde && waarde<=maxWaarde)
    return true;
  else
  { cout << variabele << "=" << waarde << ", maar moet in [" << minWaarde
         << "," << maxWaarde << "] liggen." << endl;
    return false;
  }

}  // integerinbereik

#endif
