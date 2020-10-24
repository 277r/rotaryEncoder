/*
braincracker: R.
finishing date: 21:20 8-8-2020  HH:mm dd-mm-yyyy

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include <iostream>
#include <string.h>
#include <fstream>

#include "rotors.h"


//  constants
const int AOR = 256; // amount of rotors
const int stval = 256; // standard value for rotary length
const int stvalm = stval - 1; // standard value but 1 less bc lazy
//i'm so bad at coding it's insane


// other values
int keyGenSeed;
int mode;
int rotoff[AOR]; // rotary offsets
char dynchar;	   // dynamic character and int
int dyncharButInt;

std::string keyFileName;
std::string keyLine;
std::string fileName;
std::string oFileName;


// function that decodes in some unknown way
int decode(int chin, int rota[], int rotb[], int rotoffset)
{
	int count1 = stvalm;
	while (count1 >= 0)
	{
		if (chin == rotb[(count1 + rotoffset) % stval])
		{
			return rota[count1 % stval];
		}
		count1--;
	}
	return chin;
}

//function that encodes in some unknown way
int encode(int chin, int rota[256], int rotb[256], int rotoffset)
{
	int count1 = stvalm;
	while (count1 >= 0)
	{
		if (chin == rota[count1 % stval])
		{
			return rotb[(count1 + rotoffset) % stval];
		}
		count1--;
	}

	return chin;
}
// offsets checking
void offcheck()
{
	for (int i = 0; i < AOR; i++)
	{
		if (i + 1 == AOR && rotoff[i] >=stvalm)
		{
			rotoff[i] = 0;
		}
		else if (rotoff[i] >= stvalm)
		{
			rotoff[i] = 0;
			rotoff[i + 1]++;
		}
	}
}


/* offcheck later maybe
void offcheck() {
	for (int i; (sizeof(rotoff)/sizeof(rotoff[0])) > i; i++){	
		if (rotoff[i] >= stvalm){
			rotoff[i] = 0;
			rotoff[i + 1]++;
		}
	}

}*/

// reverse offset checking that probably isn't used but i'm too lazy to tell
/*
void moffcheck() {
    if (rotoff3 <= 0) {
        rotoff3 = stvalm;
        rotoff2--;

    }
    if (rotoff2 <= 0) {
        rotoff2 = stvalm;
        rotoff1--;
    }
    if (rotoff1 <= 0) {
        rotoff1 = stvalm;
    }
}
*/
// main function doing all the shit combined
int main()
{
	std::ifstream dataInput;
	std::ifstream keyInput;
	std::ofstream dataOutput;
	std::ofstream keyOutput;
	std::cout << "enter 0 to encode, enter 1 to decode, enter 2 for more info about this software, 3 for key generation" << std::endl;
	std::cin >> mode;
	if (mode == 0)
	{
		std::cout << "enter key file name" << std::endl;
		std::cin.ignore();
		std::getline(std::cin, keyFileName);
		std::cout << "enter data file name" << std::endl;
		std::getline(std::cin, fileName);
		
		
		keyInput.open(keyFileName);
		for (int i = 0; i < AOR; i++){
			keyInput >> rotoff[i];
		}

		dataInput.open(fileName, std::ifstream::binary);
		oFileName = fileName + ".xc7";
		if (!dataInput.is_open()){
			std::cout << "error 01: data input file does not exist" << std::endl;
			return 0;
		}
		if (!keyInput.is_open()){
			std::cout << "error 02: key input file does not exist" << std::endl;
			return 0;
		}
		dataOutput.open(oFileName.c_str());
		if (dataOutput.is_open())
		{
			std::cout << "output file access granted" << std::endl;
		}
		std::cout << "clearing output file" << std::endl;
		dataOutput.close();
		dataOutput.open(oFileName.c_str(), std::ios::out | std::ios::app | std::ios::binary);
		std::cout << "writing to output file" << std::endl;


		while (!dataInput.eof())
		{

			dataInput.read(&dynchar, 1);
			if (!dataInput.eof())
			{
				dyncharButInt = static_cast<int>(dynchar);
				for (int i = 0; i < AOR; i++)
				{
					dyncharButInt = encode(dyncharButInt, rot[i], rotA[i], rotoff[i]);
				}
				rotoff[0]++;
				offcheck();

				dynchar = static_cast<char>(dyncharButInt);
				dataOutput << dynchar;
			}
		}
		std::cout << "closing files" << std::endl;
		dataOutput.close();
		dataInput.close();
		keyInput.close();
	}
	else if (mode == 1)
	{
		std::cout << "enter key file name" << std::endl;
		std::cin.ignore();
		std::getline(std::cin, keyFileName);
		std::cout << "enter data file name" << std::endl;
		std::getline(std::cin, fileName);
		keyInput.open(keyFileName);

		for (int i = 0; i < AOR; i++)
		{
			keyInput >> rotoff[i];
		}

		dataInput.open(fileName, std::ifstream::binary);
		fileName.pop_back();
		fileName.pop_back();
		fileName.pop_back();
		fileName.pop_back();
		if (!dataInput.is_open())
		{
			std::cout << "error 01: data input file does not exist" << std::endl;
			return 0;
		}
		if (!keyInput.is_open())
		{
			std::cout << "error 02: key input file does not exist" << std::endl;
			return 0;
		}
		dataOutput.open(fileName.c_str());
		if (dataOutput.is_open())
		{
			std::cout << "output file access granted" << std::endl;
		}
		std::cout << "clearing output file" << std::endl;
		dataOutput.close();
		dataOutput.open(fileName.c_str(), std::ios::out | std::ios::app | std::ios::binary);
		std::cout << "writing to output file" << std::endl;
		while (!dataInput.eof())
		{

			dataInput.read(&dynchar, 1);
			if (!dataInput.eof())
			{
				dyncharButInt = static_cast<int>(dynchar);
				for (int i = AOR -1; i >= 0; i--)
				{
					dyncharButInt = decode(dyncharButInt, rot[i], rotA[i], rotoff[i]);
				}
				rotoff[0]++;
				offcheck();
				dynchar = static_cast<char>(dyncharButInt);
				dataOutput << dynchar;
			}
		}
		std::cout << "closing files" << std::endl;
		dataOutput.close();
		dataInput.close();
		keyInput.close();
	}
	else if (mode == 2)
	{
		std::cout << "you can read a guide online: (link that isn't finished yet)" << std::endl;
	}
	else if (mode == 3)
	{
		std::cout << "enter the name of the key file to generate" << std::endl;
		std::cin.ignore();
		std::getline(std::cin, keyFileName);
		std::cout << "enter a big number to use as seed to generate keys" << std::endl;
		std::cin >> keyGenSeed;
		keyOutput.open(keyFileName.c_str());
		if (keyOutput.is_open())
		{
			std::cout << "access granted" << std::endl;
		}
		std::cout << "clearing file" << std::endl;
		keyOutput.close();
		keyOutput.open(keyFileName.c_str(), std::ios::out | std::ios::app | std::ios::binary);
		int bruh;
		for (int ksA = 0; ksA < AOR; ksA++)
		{
			bruh = ksA + keyGenSeed;
			srand(time(NULL) + bruh);
			int randomNum = (rand() + keyGenSeed) % stval;
			if (randomNum < 0){
				randomNum = randomNum * -1;
			}
			keyOutput << randomNum << std::endl;
		}
		keyOutput.close();
	}
	std::cout << std::endl;
}
