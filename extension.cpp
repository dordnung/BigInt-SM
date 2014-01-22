/**
 * -----------------------------------------------------
 * File        extension.cpp
 * Authors     David <popoklopsi> Ordnung
 * License     GPLv3
 * Web         http://popoklopsi.de
 * -----------------------------------------------------
 * 
 * 
 * Copyright (C) 2014 David <popoklopsi> Ordnung
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>
 */


#include "extension.h"




enum BigInt_Method
{
	RETURN_NEW = 0,
	SET_DIRECT = 1
};

HandleType_t g_BigIntType = 0;



// Natives
sp_nativeinfo_t bigint_natives[] =
{
	{"BigInt_Create",               BigInt_Create},
	{"BigInt_CreateFromString",     BigInt_CreateFromString},
	{"BigInt_ToInt",                BigInt_ToInt},
	{"BigInt_ToString",             BigInt_ToString},
	{"BigInt_GetSign",              BigInt_GetSign},
	{"BigInt_CompareTo",            BigInt_CompareTo},
	{"BigInt_Negate",               BigInt_Negate},
	{"BigInt_Add",                  BigInt_Add},
	{"BigInt_Subtract",             BigInt_Subtract},
	{"BigInt_Multiply",             BigInt_Multiply},
	{"BigInt_Divide",               BigInt_Divide},
	{"BigInt_DivideRemainder",      BigInt_DivideRemainder},
	{"BigInt_BitAnd",               BigInt_BitAnd},
	{"BigInt_BitOr",                BigInt_BitOr},
	{"BigInt_BitXor",               BigInt_BitXor},
	{"BigInt_BitShiftLeft",         BigInt_BitShiftLeft},
	{"BigInt_BitShiftRight",        BigInt_BitShiftRight},
	{"BigInt_GCD",                  BigInt_GCD},
	{"BigInt_Euclidean",            BigInt_Euclidean},
	{"BigInt_ModInv",               BigInt_ModInv},
	{"BigInt_ModExp",               BigInt_ModExp},
	{NULL, NULL}
};





/**
 * This is called after the initial loading sequence has been processed.
 *
 * @param error        Error message buffer.
 * @param maxlength    Size of error message buffer.
 * @param late         Whether or not the module was loaded after map load.
 * @return             True to succeed loading, false to fail.
 */
bool BigIntExtension::SDK_OnLoad(char *error, size_t err_max, bool late)
{
	HandleError err;

	// Create a Handle Type for BigInt
	g_BigIntType = g_pHandleSys->CreateType("BigInt", this, 0, NULL, NULL, myself->GetIdentity(), &err);

	if (g_BigIntType == 0)
	{
		// Couldn't create it, so fail loading.
		snprintf(error, err_max, "Could not create BigInt handle type (err: %d)", err);

		return false;
	}


	// Add the natives
	sharesys->AddNatives(myself, bigint_natives);

	//Now register the extension
	sharesys->RegisterLibrary(myself, "bigint");


	/* LOADED :) */
	return true;
}



/**
* Called when destroying a handle. Must be implemented.
*
* @param type		   Handle type.
* @param object	   Handle internal object.
*/
void BigIntExtension::OnHandleDestroy(HandleType_t type, void *object)
{
	// Destroy our object here
	if (type == g_BigIntType)
	{
		delete object;
	}
}



// Creates a BigInt from a Int
cell_t BigInt_Create(IPluginContext *pContext, const cell_t *params)
{
	BigInteger* bigint = new BigInteger(params[1]);

	Handle_t hndl = handlesys->CreateHandle(g_BigIntType, bigint, pContext->GetIdentity(), myself->GetIdentity(), NULL);

	if (!hndl)
	{
		delete bigint;
	}

	return hndl;
}



// Creates a BigInt from a String
cell_t BigInt_CreateFromString(IPluginContext *pContext, const cell_t *params)
{
	char *str;
	pContext->LocalToString(params[1], &str);

	BigInteger* bigint = new BigInteger(stringToBigInteger(str));

	Handle_t hndl = handlesys->CreateHandle(g_BigIntType, bigint, pContext->GetIdentity(), myself->GetIdentity(), NULL);

	if (!hndl)
	{
		delete bigint;
	}

	return hndl;
}



// Int from BigInt
cell_t BigInt_ToInt(IPluginContext *pContext, const cell_t *params)
{
	Handle_t hndl = static_cast<Handle_t>(params[1]);

	if (hndl == BAD_HANDLE)
	{
		return pContext->ThrowNativeError("Invalid Handle %i", BAD_HANDLE);
	}

	HandleError err;
	HandleSecurity sec(NULL, myself->GetIdentity());
	BigInteger *bigint;

	if ((err = handlesys->ReadHandle(hndl, g_BigIntType, &sec, (void **)&bigint)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl, err);
	}

	return bigint->toInt();
}




// String from BigInt
cell_t BigInt_ToString(IPluginContext *pContext, const cell_t *params)
{
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	int base = params[4];

	if (hndl == BAD_HANDLE)
	{
		return pContext->ThrowNativeError("Invalid Handle %i", BAD_HANDLE);
	}

	HandleError err;
	HandleSecurity sec(NULL, myself->GetIdentity());
	BigInteger *bigint;

	if ((err = handlesys->ReadHandle(hndl, g_BigIntType, &sec, (void **)&bigint)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl, err);
	}

	if (base != 10)
	{
		pContext->StringToLocal(params[2], params[3], std::string(BigUnsignedInABase(bigint->getMagnitude(), base)).c_str());

		return 1;
	}

	pContext->StringToLocal(params[2], params[3], bigIntegerToString(*bigint).c_str());

	return 1;
}



// Get Sign of BigInt
cell_t BigInt_GetSign(IPluginContext *pContext, const cell_t *params)
{
	Handle_t hndl = static_cast<Handle_t>(params[1]);

	if (hndl == BAD_HANDLE)
	{
		return pContext->ThrowNativeError("Invalid Handle %i", BAD_HANDLE);
	}

	HandleError err;
	HandleSecurity sec(NULL, myself->GetIdentity());
	BigInteger *bigint;

	if ((err = handlesys->ReadHandle(hndl, g_BigIntType, &sec, (void **)&bigint)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl, err);
	}

	return (int)bigint->getSign();
}



// Compare two BigInts
cell_t BigInt_CompareTo(IPluginContext *pContext, const cell_t *params)
{
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	Handle_t hndl2 = static_cast<Handle_t>(params[2]);

	if (hndl == BAD_HANDLE || hndl2 == BAD_HANDLE)
	{
		return pContext->ThrowNativeError("Invalid Handle %i", BAD_HANDLE);
	}

	HandleError err;
	HandleSecurity sec(NULL, myself->GetIdentity());

	BigInteger *bigint;
	BigInteger *bigint2;


	if ((err = handlesys->ReadHandle(hndl, g_BigIntType, &sec, (void **)&bigint)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl, err);
	}

	if ((err = handlesys->ReadHandle(hndl2, g_BigIntType, &sec, (void **)&bigint2)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl2, err);
	}


	return (int)bigint->compareTo(*bigint2);
}



// Negates a BigInt
cell_t BigInt_Negate(IPluginContext *pContext, const cell_t *params)
{
	Handle_t hndl = static_cast<Handle_t>(params[1]);

	if (hndl == BAD_HANDLE)
	{
		return pContext->ThrowNativeError("Invalid Handle %i", BAD_HANDLE);
	}

	HandleError err;
	HandleSecurity sec(NULL, myself->GetIdentity());
	BigInteger *bigint;

	if ((err = handlesys->ReadHandle(hndl, g_BigIntType, &sec, (void **)&bigint)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl, err);
	}

	if (params[2] == RETURN_NEW)
	{
		BigInteger *newInt = new BigInteger(-(*bigint));

		Handle_t hndlnew = handlesys->CreateHandle(g_BigIntType, newInt, pContext->GetIdentity(), myself->GetIdentity(), NULL);

		if (!hndlnew)
		{
			delete newInt;
		}

		return hndlnew;
	}
	else
	{
		bigint->negate(*bigint);
	}

	return hndl;
}



// Adds to BigInts
cell_t BigInt_Add(IPluginContext *pContext, const cell_t *params)
{
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	Handle_t hndl2 = static_cast<Handle_t>(params[2]);

	if (hndl == BAD_HANDLE || hndl2 == BAD_HANDLE)
	{
		return pContext->ThrowNativeError("Invalid Handle %i", BAD_HANDLE);
	}

	HandleError err;
	HandleSecurity sec(NULL, myself->GetIdentity());

	BigInteger *bigint;
	BigInteger *bigint2;


	if ((err = handlesys->ReadHandle(hndl, g_BigIntType, &sec, (void **)&bigint)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl, err);
	}

	if ((err = handlesys->ReadHandle(hndl2, g_BigIntType, &sec, (void **)&bigint2)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl2, err);
	}


	if (params[3] == RETURN_NEW)
	{
		BigInteger *newInt;

		try
		{
			newInt = new BigInteger((*bigint) + (*bigint2));
		}
		catch (char *error)
		{
			return pContext->ThrowNativeError("BigIntegers Method Failed (error %s)", error);
		}

		Handle_t hndlnew = handlesys->CreateHandle(g_BigIntType, newInt, pContext->GetIdentity(), myself->GetIdentity(), NULL);

		if (!hndlnew)
		{
			delete newInt;
		}

		return hndlnew;
	}
	else
	{
		try
		{
			(*bigint) += (*bigint2);
		}
		catch (char *error)
		{
			return pContext->ThrowNativeError("BigIntegers Method Failed(error %s)", error);
		}
	}

	return hndl;
}



// Subtracts two BigInts
cell_t BigInt_Subtract(IPluginContext *pContext, const cell_t *params)
{
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	Handle_t hndl2 = static_cast<Handle_t>(params[2]);

	if (hndl == BAD_HANDLE || hndl2 == BAD_HANDLE)
	{
		return pContext->ThrowNativeError("Invalid Handle %i", BAD_HANDLE);
	}

	HandleError err;
	HandleSecurity sec(NULL, myself->GetIdentity());

	BigInteger *bigint;
	BigInteger *bigint2;


	if ((err = handlesys->ReadHandle(hndl, g_BigIntType, &sec, (void **)&bigint)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl, err);
	}

	if ((err = handlesys->ReadHandle(hndl2, g_BigIntType, &sec, (void **)&bigint2)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl2, err);
	}


	if (params[3] == RETURN_NEW)
	{
		BigInteger *newInt;

		try
		{
			newInt = new BigInteger((*bigint) - (*bigint2));
		}
		catch (char *error)
		{
			return pContext->ThrowNativeError("BigIntegers Method Failed (error %s)", error);
		}

		Handle_t hndlnew = handlesys->CreateHandle(g_BigIntType, newInt, pContext->GetIdentity(), myself->GetIdentity(), NULL);

		if (!hndlnew)
		{
			delete newInt;
		}

		return hndlnew;
	}
	else
	{
		try
		{
			(*bigint) -= (*bigint2);
		}
		catch (char *error)
		{
			return pContext->ThrowNativeError("BigIntegers Method Failed(error %s)", error);
		}
	}

	return hndl;
}



// Multiply to BigInts
cell_t BigInt_Multiply(IPluginContext *pContext, const cell_t *params)
{
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	Handle_t hndl2 = static_cast<Handle_t>(params[2]);

	if (hndl == BAD_HANDLE || hndl2 == BAD_HANDLE)
	{
		return pContext->ThrowNativeError("Invalid Handle %i", BAD_HANDLE);
	}

	HandleError err;
	HandleSecurity sec(NULL, myself->GetIdentity());

	BigInteger *bigint;
	BigInteger *bigint2;


	if ((err = handlesys->ReadHandle(hndl, g_BigIntType, &sec, (void **)&bigint)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl, err);
	}

	if ((err = handlesys->ReadHandle(hndl2, g_BigIntType, &sec, (void **)&bigint2)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl2, err);
	}


	if (params[3] == RETURN_NEW)
	{
		BigInteger *newInt;

		try
		{
			newInt = new BigInteger((*bigint) * (*bigint2));
		}
		catch (char *error)
		{
			return pContext->ThrowNativeError("BigIntegers Method Failed (error %s)", error);
		}

		Handle_t hndlnew = handlesys->CreateHandle(g_BigIntType, newInt, pContext->GetIdentity(), myself->GetIdentity(), NULL);

		if (!hndl)
		{
			delete newInt;
		}

		return hndlnew;
	}
	else
	{
		try
		{
			(*bigint) *= (*bigint2);
		}
		catch (char *error)
		{
			return pContext->ThrowNativeError("BigIntegers Method Failed(error %s)", error);
		}
	}

	return hndl;
}



// Divide two BigInts
cell_t BigInt_Divide(IPluginContext *pContext, const cell_t *params)
{
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	Handle_t hndl2 = static_cast<Handle_t>(params[2]);

	if (hndl == BAD_HANDLE || hndl2 == BAD_HANDLE)
	{
		return pContext->ThrowNativeError("Invalid Handle %i", BAD_HANDLE);
	}

	HandleError err;
	HandleSecurity sec(NULL, myself->GetIdentity());

	BigInteger *bigint;
	BigInteger *bigint2;


	if ((err = handlesys->ReadHandle(hndl, g_BigIntType, &sec, (void **)&bigint)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl, err);
	}

	if ((err = handlesys->ReadHandle(hndl2, g_BigIntType, &sec, (void **)&bigint2)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl2, err);
	}


	if (params[3] == RETURN_NEW)
	{
		BigInteger *newInt;

		try
		{
			newInt = new BigInteger((*bigint) / (*bigint2));
		}
		catch (char *error)
		{
			return pContext->ThrowNativeError("BigIntegers Method Failed (error %s)", error);
		}

		Handle_t hndlnew = handlesys->CreateHandle(g_BigIntType, newInt, pContext->GetIdentity(), myself->GetIdentity(), NULL);

		if (!hndlnew)
		{
			delete newInt;
		}

		return hndlnew;
	}
	else
	{
		try
		{
			(*bigint) /= (*bigint2);
		}
		catch (char *error)
		{
			return pContext->ThrowNativeError("BigIntegers Method Failed(error %s)", error);
		}
	}

	return hndl;
}



// Return remainder of divide
cell_t BigInt_DivideRemainder(IPluginContext *pContext, const cell_t *params)
{
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	Handle_t hndl2 = static_cast<Handle_t>(params[2]);

	if (hndl == BAD_HANDLE || hndl2 == BAD_HANDLE)
	{
		return pContext->ThrowNativeError("Invalid Handle %i", BAD_HANDLE);
	}

	HandleError err;
	HandleSecurity sec(NULL, myself->GetIdentity());

	BigInteger *bigint;
	BigInteger *bigint2;


	if ((err = handlesys->ReadHandle(hndl, g_BigIntType, &sec, (void **)&bigint)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl, err);
	}

	if ((err = handlesys->ReadHandle(hndl2, g_BigIntType, &sec, (void **)&bigint2)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl2, err);
	}


	if (params[3] == RETURN_NEW)
	{
		BigInteger *newInt;

		try
		{
			newInt = new BigInteger((*bigint) % (*bigint2));
		}
		catch (char *error)
		{
			return pContext->ThrowNativeError("BigIntegers Method Failed (error %s)", error);
		}

		Handle_t hndlnew = handlesys->CreateHandle(g_BigIntType, newInt, pContext->GetIdentity(), myself->GetIdentity(), NULL);

		if (!hndlnew)
		{
			delete newInt;
		}

		return hndlnew;
	}
	else
	{
		try
		{
			(*bigint) %= (*bigint2);
		}
		catch (char *error)
		{
			return pContext->ThrowNativeError("BigIntegers Method Failed(error %s)", error);
		}
	}

	return hndl;
}



// Uses BitAnd on BigInteger
cell_t BigInt_BitAnd(IPluginContext *pContext, const cell_t *params)
{
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	Handle_t hndl2 = static_cast<Handle_t>(params[2]);

	if (hndl == BAD_HANDLE || hndl2 == BAD_HANDLE)
	{
		return pContext->ThrowNativeError("Invalid Handle %i", BAD_HANDLE);
	}

	HandleError err;
	HandleSecurity sec(NULL, myself->GetIdentity());

	BigInteger *bigint;
	BigInteger *bigint2;


	if ((err = handlesys->ReadHandle(hndl, g_BigIntType, &sec, (void **)&bigint)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl, err);
	}

	if ((err = handlesys->ReadHandle(hndl2, g_BigIntType, &sec, (void **)&bigint2)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl2, err);
	}

	BigInteger *newInt;

	try
	{
		newInt = new BigInteger((bigint->getMagnitude()) & (bigint2->getMagnitude()));
	}
	catch (char *error)
	{
		return pContext->ThrowNativeError("BigIntegers Method Failed (error %s)", error);
	}

	Handle_t hndlnew = handlesys->CreateHandle(g_BigIntType, newInt, pContext->GetIdentity(), myself->GetIdentity(), NULL);

	if (!hndlnew)
	{
		delete newInt;
	}

	return hndlnew;
}



// Uses BitOr
cell_t BigInt_BitOr(IPluginContext *pContext, const cell_t *params)
{
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	Handle_t hndl2 = static_cast<Handle_t>(params[2]);

	if (hndl == BAD_HANDLE || hndl2 == BAD_HANDLE)
	{
		return pContext->ThrowNativeError("Invalid Handle %i", BAD_HANDLE);
	}

	HandleError err;
	HandleSecurity sec(NULL, myself->GetIdentity());

	BigInteger *bigint;
	BigInteger *bigint2;


	if ((err = handlesys->ReadHandle(hndl, g_BigIntType, &sec, (void **)&bigint)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl, err);
	}

	if ((err = handlesys->ReadHandle(hndl2, g_BigIntType, &sec, (void **)&bigint2)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl2, err);
	}

	BigInteger *newInt;

	try
	{
		newInt = new BigInteger((bigint->getMagnitude()) | (bigint2->getMagnitude()));
	}
	catch (char *error)
	{
		return pContext->ThrowNativeError("BigIntegers Method Failed (error %s)", error);
	}

	Handle_t hndlnew = handlesys->CreateHandle(g_BigIntType, newInt, pContext->GetIdentity(), myself->GetIdentity(), NULL);

	if (!hndlnew)
	{
		delete newInt;
	}

	return hndlnew;
}



// Uses Bit Xor
cell_t BigInt_BitXor(IPluginContext *pContext, const cell_t *params)
{
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	Handle_t hndl2 = static_cast<Handle_t>(params[2]);

	if (hndl == BAD_HANDLE || hndl2 == BAD_HANDLE)
	{
		return pContext->ThrowNativeError("Invalid Handle %i", BAD_HANDLE);
	}

	HandleError err;
	HandleSecurity sec(NULL, myself->GetIdentity());

	BigInteger *bigint;
	BigInteger *bigint2;


	if ((err = handlesys->ReadHandle(hndl, g_BigIntType, &sec, (void **)&bigint)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl, err);
	}

	if ((err = handlesys->ReadHandle(hndl2, g_BigIntType, &sec, (void **)&bigint2)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl2, err);
	}

	BigInteger *newInt;

	try
	{
		newInt = new BigInteger((bigint->getMagnitude()) ^ (bigint2->getMagnitude()));
	}
	catch (char *error)
	{
		return pContext->ThrowNativeError("BigIntegers Method Failed (error %s)", error);
	}

	Handle_t hndlnew = handlesys->CreateHandle(g_BigIntType, newInt, pContext->GetIdentity(), myself->GetIdentity(), NULL);

	if (!hndlnew)
	{
		delete newInt;
	}

	return hndlnew;
}



// Uses BitShiftLeft
cell_t BigInt_BitShiftLeft(IPluginContext *pContext, const cell_t *params)
{
	Handle_t hndl = static_cast<Handle_t>(params[1]);

	if (hndl == BAD_HANDLE)
	{
		return pContext->ThrowNativeError("Invalid Handle %i", BAD_HANDLE);
	}

	HandleError err;
	HandleSecurity sec(NULL, myself->GetIdentity());

	BigInteger *bigint;


	if ((err = handlesys->ReadHandle(hndl, g_BigIntType, &sec, (void **)&bigint)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl, err);
	}

	BigInteger *newInt;

	try
	{
		newInt = new BigInteger((bigint->getMagnitude()) << params[2]);
	}
	catch (char *error)
	{
		return pContext->ThrowNativeError("BigIntegers Method Failed (error %s)", error);
	}

	Handle_t hndlnew = handlesys->CreateHandle(g_BigIntType, newInt, pContext->GetIdentity(), myself->GetIdentity(), NULL);

	if (!hndlnew)
	{
		delete newInt;
	}

	return hndlnew;
}



// Uses BitShiftRight
cell_t BigInt_BitShiftRight(IPluginContext *pContext, const cell_t *params)
{
	Handle_t hndl = static_cast<Handle_t>(params[1]);

	if (hndl == BAD_HANDLE)
	{
		return pContext->ThrowNativeError("Invalid Handle %i", BAD_HANDLE);
	}

	HandleError err;
	HandleSecurity sec(NULL, myself->GetIdentity());

	BigInteger *bigint;


	if ((err = handlesys->ReadHandle(hndl, g_BigIntType, &sec, (void **)&bigint)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl, err);
	}

	BigInteger *newInt;
	
	try
	{
		newInt = new BigInteger((bigint->getMagnitude()) >> params[2]);
	}
	catch (char *error)
	{
		return pContext->ThrowNativeError("BigIntegers Method Failed (error %s)", error);
	}

	Handle_t hndlnew = handlesys->CreateHandle(g_BigIntType, newInt, pContext->GetIdentity(), myself->GetIdentity(), NULL);

	if (!hndlnew)
	{
		delete newInt;
	}

	return hndlnew;
}



// GCF of two big ints
cell_t BigInt_GCD(IPluginContext *pContext, const cell_t *params)
{
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	Handle_t hndl2 = static_cast<Handle_t>(params[2]);

	if (hndl == BAD_HANDLE || hndl2 == BAD_HANDLE)
	{
		return pContext->ThrowNativeError("Invalid Handle %i", BAD_HANDLE);
	}

	HandleError err;
	HandleSecurity sec(NULL, myself->GetIdentity());

	BigInteger *bigint;
	BigInteger *bigint2;


	if ((err = handlesys->ReadHandle(hndl, g_BigIntType, &sec, (void **)&bigint)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl, err);
	}

	if ((err = handlesys->ReadHandle(hndl2, g_BigIntType, &sec, (void **)&bigint2)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl2, err);
	}

	BigInteger *newInt;

	try
	{
		newInt = new BigInteger(gcd(bigint->getMagnitude(), bigint2->getMagnitude()));
	}
	catch (char *error)
	{
		return pContext->ThrowNativeError("BigIntegers Method Failed (error %s)", error);
	}

	Handle_t hndlnew = handlesys->CreateHandle(g_BigIntType, newInt, pContext->GetIdentity(), myself->GetIdentity(), NULL);

	if (!hndlnew)
	{
		delete newInt;
	}

	return hndlnew;
}




// Euclidean from Bigints
cell_t BigInt_Euclidean(IPluginContext *pContext, const cell_t *params)
{
	cell_t *hndl3;
	cell_t *hndl4;
	cell_t *hndl5;

	Handle_t hndl = static_cast<Handle_t>(params[1]);
	Handle_t hndl2 = static_cast<Handle_t>(params[2]);

	pContext->LocalToPhysAddr(params[3], &hndl3);
	pContext->LocalToPhysAddr(params[4], &hndl4);
	pContext->LocalToPhysAddr(params[5], &hndl5);

	if (hndl == BAD_HANDLE || hndl2 == BAD_HANDLE)
	{
		return pContext->ThrowNativeError("Invalid Handle %i", BAD_HANDLE);
	}

	HandleError err;
	HandleSecurity sec(NULL, myself->GetIdentity());

	BigInteger *bigint;
	BigInteger *bigint2;


	if ((err = handlesys->ReadHandle(hndl, g_BigIntType, &sec, (void **)&bigint)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl, err);
	}

	if ((err = handlesys->ReadHandle(hndl2, g_BigIntType, &sec, (void **)&bigint2)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl2, err);
	}

	BigInteger g, r, s;

	try
	{
		extendedEuclidean(*bigint, *bigint2, g, r, s);
	}
	catch (char *error)
	{
		return pContext->ThrowNativeError("BigIntegers Method Failed (error %s)", error);
	}


	if (hndl3 != NULL)
	{
		BigInteger *bigint3 = new BigInteger(g);

		Handle_t hndlnew = handlesys->CreateHandle(g_BigIntType, bigint3, pContext->GetIdentity(), myself->GetIdentity(), NULL);

		*hndl3 = *(cell_t *)&hndlnew;
	}


	if (hndl4 != NULL)
	{
		BigInteger *bigint4 = new BigInteger(r);

		Handle_t hndlnew = handlesys->CreateHandle(g_BigIntType, bigint4, pContext->GetIdentity(), myself->GetIdentity(), NULL);

		*hndl4 = *(cell_t *)&hndlnew;
	}


	if (hndl5 != NULL)
	{
		BigInteger *bigint5 = new BigInteger(s);

		Handle_t hndlnew = handlesys->CreateHandle(g_BigIntType, bigint5, pContext->GetIdentity(), myself->GetIdentity(), NULL);

		*hndl5 = *(cell_t *)&hndlnew;
	}

	return 1;
}



// Calculate ModInv
cell_t BigInt_ModInv(IPluginContext *pContext, const cell_t *params)
{
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	Handle_t hndl2 = static_cast<Handle_t>(params[2]);

	if (hndl == BAD_HANDLE || hndl2 == BAD_HANDLE)
	{
		return pContext->ThrowNativeError("Invalid Handle %i", BAD_HANDLE);
	}

	HandleError err;
	HandleSecurity sec(NULL, myself->GetIdentity());

	BigInteger *bigint;
	BigInteger *bigint2;


	if ((err = handlesys->ReadHandle(hndl, g_BigIntType, &sec, (void **)&bigint)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl, err);
	}

	if ((err = handlesys->ReadHandle(hndl2, g_BigIntType, &sec, (void **)&bigint2)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl2, err);
	}

	BigInteger *newInt;

	try
	{
		newInt = new BigInteger(modinv(*bigint, bigint2->getMagnitude()));
	}
	catch (...)
	{
		return BAD_HANDLE;
	}

	Handle_t hndlnew = handlesys->CreateHandle(g_BigIntType, newInt, pContext->GetIdentity(), myself->GetIdentity(), NULL);

	if (!hndlnew)
	{
		delete newInt;
	}

	return hndlnew;
}



// Calculates ModExp
cell_t BigInt_ModExp(IPluginContext *pContext, const cell_t *params)
{
	Handle_t hndl = static_cast<Handle_t>(params[1]);
	Handle_t hndl2 = static_cast<Handle_t>(params[2]);
	Handle_t hndl3 = static_cast<Handle_t>(params[3]);

	if (hndl == BAD_HANDLE || hndl2 == BAD_HANDLE || hndl3 == BAD_HANDLE)
	{
		return pContext->ThrowNativeError("Invalid Handle %i", BAD_HANDLE);
	}

	HandleError err;
	HandleSecurity sec(NULL, myself->GetIdentity());

	BigInteger *bigint;
	BigInteger *bigint2;
	BigInteger *bigint3;


	if ((err = handlesys->ReadHandle(hndl, g_BigIntType, &sec, (void **)&bigint)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl, err);
	}

	if ((err = handlesys->ReadHandle(hndl2, g_BigIntType, &sec, (void **)&bigint2)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl2, err);
	}

	if ((err = handlesys->ReadHandle(hndl3, g_BigIntType, &sec, (void **)&bigint3)) != HandleError_None)
	{
		return pContext->ThrowNativeError("Invalid Handle %x (error %d)", hndl3, err);
	}


	BigInteger *newInt;

	try
	{
		newInt = new BigInteger(modexp(*bigint, bigint2->getMagnitude(), bigint3->getMagnitude()));
	}
	catch (char *error)
	{
		return pContext->ThrowNativeError("BigIntegers Method Failed (error %s)", error);
	}

	Handle_t hndlnew = handlesys->CreateHandle(g_BigIntType, newInt, pContext->GetIdentity(), myself->GetIdentity(), NULL);

	if (!hndlnew)
	{
		delete newInt;
	}

	return hndlnew;
}




/* Linking extension */
BigIntExtension g_BigIntExtension;
SMEXT_LINK(&g_BigIntExtension);