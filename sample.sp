#include <sourcemod>
#include <bigint>


#define FirstNumber      "8885213245812354894512415721448"
#define SecondNumber     "-992115489722222244688872321"



public OnPluginStart()
{
	decl String:resultString[1024];
	decl String:resultString2[512];
	decl String:resultString3[512];
	decl String:resultString4[512];
	decl String:resultString5[512];

	new Handle:firstNumber = BigInt_CreateFromString(FirstNumber);
	new Handle:secondNumber = BigInt_CreateFromString(SecondNumber);
	new Handle:result;
	new Handle:g;
	new Handle:r;
	new Handle:s;


	switch(BigInt_CompareTo(firstNumber, secondNumber))
	{
		case LESS:
		{
			PrintToServer("%s is lesser than %s", FirstNumber, SecondNumber);
		}
		case EQUAL:
		{
			PrintToServer("%s is equal with %s", FirstNumber, SecondNumber);
		}
		case GREATER:
		{
			PrintToServer("%s is greater than %s", FirstNumber, SecondNumber);
		}
		default:
		{
			PrintToServer("%s is greater than %s", FirstNumber, SecondNumber);
		}
	}


	switch(BigInt_GetSign(firstNumber))
	{
		case NEGATIVE:
		{
			PrintToServer("%s is negative", FirstNumber);
		}
		case ZERO:
		{
			PrintToServer("%s is zero", FirstNumber);
		}
		case POSITIVE:
		{
			PrintToServer("%s is positive", FirstNumber);
		}
		default:
		{
			PrintToServer("%s is positive", FirstNumber);
		}
	}


	switch(BigInt_GetSign(secondNumber))
	{
		case NEGATIVE:
		{
			PrintToServer("%s is negative", SecondNumber);
		}
		case ZERO:
		{
			PrintToServer("%s is zero", SecondNumber);
		}
		case POSITIVE:
		{
			PrintToServer("%s is positive", SecondNumber);
		}
		default:
		{
			PrintToServer("%s is positive", SecondNumber);
		}
	}



	BigInt_Euclidean(firstNumber, secondNumber, g, r, s);
	BigInt_ToString(g, resultString3, sizeof(resultString3));
	BigInt_ToString(r, resultString4, sizeof(resultString4));
	BigInt_ToString(s, resultString5, sizeof(resultString5));
	PrintToServer("%s*%s + %s*%s == %s", resultString4, FirstNumber, resultString5, SecondNumber, resultString3);


	result = BigInt_Add(firstNumber, secondNumber);
	BigInt_ToString(result, resultString, sizeof(resultString));

	PrintToServer("%s + %s is %s", FirstNumber, SecondNumber, resultString);
	CloseHandle(result);


	result = BigInt_Subtract(firstNumber, secondNumber);
	BigInt_ToString(result, resultString, sizeof(resultString));

	PrintToServer("%s - %s is %s", FirstNumber, SecondNumber, resultString);
	CloseHandle(result);


	result = BigInt_Multiply(firstNumber, secondNumber);
	BigInt_ToString(result, resultString, sizeof(resultString));

	PrintToServer("%s * %s is %s", FirstNumber, SecondNumber, resultString);
	CloseHandle(result);


	result = BigInt_Divide(firstNumber, secondNumber);
	BigInt_DivideRemainder(firstNumber, secondNumber, SET_DIRECT);

	BigInt_ToString(result, resultString, sizeof(resultString));
	BigInt_ToString(firstNumber, resultString2, sizeof(resultString2));

	PrintToServer("%s / %s is %s with remainder %s", FirstNumber, SecondNumber, resultString, resultString2);
	CloseHandle(result);

	CloseHandle(firstNumber);
	CloseHandle(secondNumber);
}