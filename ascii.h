/*
Dicionário da ttabela ASCII
Converte para os tipos:
   - Decimal;
   - Hxadecimal;
   - Caracter.
*/
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

#ifndef ASCII
#define ASCII

class Ascii{
	private:
	
	public:
		Ascii();
		string getDecimalToHexa(int old);
		char getDecimalToCarac(int old);
		int getHexaToDecimal(char old[]);
		char getHexaToCarc(char old[]);
		int getCaracToDecimal(char old);
		string getCaracToHexa(char old);
		~Ascii();
};
#endif
