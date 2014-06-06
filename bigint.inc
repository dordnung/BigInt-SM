#if defined _bigint_included
	#endinput
#endif

#define _bigint_included





/* Enumeration for a operation of a BigInteger. */
enum BigInt_Comp
{
	BigInt_ADD = 0, 
	BigInt_SUBTRACT, 
	BigInt_MULTIPLY,
	BigInt_DIVIDE,
	BigInt_DIVIDE_REMAINDER
};


/* Enumeration for a bit operation of a BigInteger. */
enum BigInt_CompBit
{
	BigInt_AND = 0, 
	BigInt_OR, 
	BigInt_XOR
};



/* Enumeration for the sign of a BigInteger. */
enum BigInt_Sign
{
	BigInt_NEGATIVE = -1, 
	BigInt_ZERO = 0, 
	BigInt_POSITIVE = 1
};



/* Enumeration for the result of a comparison. */
enum BigInt_CmpRes 
{
	BigInt_LESSER = -1, 
	BigInt_EQUAL = 0, 
	BigInt_GREATER = 1 
};


/**
 * Method to use for some Methods 
 * BigInt_RETURN_NEW will return a new BigInt Handle and will not change the original one.
 * BigInt_Override will override the given BigInt Handle and will return the same.
 * 
 */
enum BigInt_Method
{
	BigInt_RETURN_NEW = 0, 
	BigInt_OVERRIDE = 1
};








/*

CREATION AND CONVERTING OF A BIGINT

*/



/**
 * Creates a new BigInt from an integer
 *
 * @param int       Integer to create BigInteger from.
 *
 * @return          BigInt Handle.
 */
native Handle:BigInt_Create(int);




/**
 * Creates a new BigInt from a string
 *
 * @param str       String to create BigInteger from.
 * @param base      Base of the String.
 *
 * @return          BigInt Handle.
 */
native Handle:BigInt_CreateFromString(const String:str[], base = 10);




/**
 * Converters to primitive integer types
 *
 * @param bigint    BigInt Handle.
 *
 * @return          Integer of BigInt Handle.
 */
native BigInt_ToInt(Handle:bigint);




/**
 * Converters to primitive string types
 *
 * @param bigint    BigInt Handle.
 * @param str       String to save bigint in.
 * @param maxlength Maxlength of the string.
 * @param base      Base to convert to.
 *
 * @noreturn
 */
native BigInt_ToString(Handle:bigint, String:str[], maxlength, base = 10);









/*

SIGN OF A BIGINT

*/



/**
 * Get the sign of a BigInt
 *
 * @param bigint    BigInt Handle.
 *
 * @return          Sign of BigInt.
 */
native BigInt_Sign:BigInt_GetSign(Handle:bigint);




/**
 * Checks whether the BigInt is negative.
 *
 * @param bigint    BigInt Handle.
 *
 * @return          True if negative, otherwise false.
 */
stock bool:BigInt_IsNegative(Handle:bigint)
{
	return BigInt_GetSign(bigint) == BigInt_NEGATIVE;
}




/**
 * Checks whether the BigInt is zero.
 *
 * @param bigint    BigInt Handle.
 *
 * @return          True if zero, otherwise false.
 */
stock bool:BigInt_IsZero(Handle:bigint)
{
	return BigInt_GetSign(bigint) == BigInt_ZERO;
}




/**
 * Checks whether the BigInt is positive.
 *
 * @param bigint    BigInt Handle.
 *
 * @return          True if positive, otherwise false.
 */
stock bool:BigInt_IsPositive(Handle:bigint)
{
	return BigInt_GetSign(bigint) == BigInt_POSITIVE;
}









/*

COMPARING OF BIGINTS

*/


/**
 * Compares two BigInts.
 *
 * @param bigint    BigInt Handle.
 * @param bigint2   BigInt Handle to compare with.
 *
 * @return          Result of the comparing.
 */
native BigInt_CmpRes:BigInt_CompareTo(Handle:bigint, Handle:bigint2);




/**
 * Compares a BigInt with an integer.
 *
 * @param bigint    BigInt Handle.
 * @param int       Integer to compare with.
 *
 * @return          Result of the comparing.
 */
stock BigInt_CmpRes:BigInt_CompareToInt(Handle:bigint, int)
{
	new Handle:bigint2 = BigInt_Create(int);
	new BigInt_CmpRes:cmp = BigInt_CompareTo(bigint, bigint2);

	CloseHandle(bigint2);

	return cmp;
}




/**
 * Compares a BigInt with a string.
 *
 * @param bigint    BigInt Handle.
 * @param str       String to compare with.
 *
 * @return          Result of the comparing.
 */
stock BigInt_CmpRes:BigInt_CompareToString(Handle:bigint, const String:str[])
{
	new Handle:bigint2 = BigInt_CreateFromString(str);
	new BigInt_CmpRes:cmp = BigInt_CompareTo(bigint, bigint2);

	CloseHandle(bigint2);

	return cmp;
}




/**
 * Checks whether the BigInt is lesser than another one.
 *
 * @param bigint    BigInt Handle.
 * @param bigint2   BigInt Handle to compare with.
 *
 * @return          True if lesser, otherwise false.
 */
stock bool:BigInt_IsLess(Handle:bigint, Handle:bigint2)
{
	return BigInt_CompareTo(bigint, bigint2) == BigInt_LESSER;
}





/**
 * Checks whether the BigInt is lesser or equal than another one.
 *
 * @param bigint    BigInt Handle.
 * @param bigint2   BigInt Handle to compare with.
 *
 * @return          True if lesser or equal, otherwise false.
 */
stock bool:BigInt_IsLessOrEqual(Handle:bigint, Handle:bigint2)
{
	return BigInt_CompareTo(bigint, bigint2) != BigInt_GREATER;
}





/**
 * Checks whether the BigInt is not equal to another one.
 *
 * @param bigint    BigInt Handle.
 * @param bigint2   BigInt Handle to compare with.
 *
 * @return          True if not equal, otherwise false.
 */
stock bool:BigInt_IsNotEqual(Handle:bigint, Handle:bigint2)
{
	return BigInt_CompareTo(bigint, bigint2) != BigInt_EQUAL;
}





/**
 * Checks whether the BigInt is greater or equal than another one.
 *
 * @param bigint    BigInt Handle.
 * @param bigint2   BigInt Handle to compare with.
 *
 * @return          True if not greater or equal, otherwise false.
 */
stock bool:BigInt_IsGreaterOrEqual(Handle:bigint, Handle:bigint2)
{
	return BigInt_CompareTo(bigint, bigint2) != BigInt_LESSER;
}




/**
 * Checks whether the BigInt is greater than another one.
 *
 * @param bigint    BigInt Handle.
 * @param bigint2   BigInt Handle to compare with.
 *
 * @return          True if not greater, otherwise false.
 */
stock bool:BigInt_IsGreater(Handle:bigint, Handle:bigint2)
{
	return BigInt_CompareTo(bigint, bigint2) == BigInt_GREATER;
}







/*

COMPUTE WITH A BIGINT

*/

/**
 * Negates a BigInt.
 *
 * @param bigint    BigInt Handle.
 * @param method    Method to use here.
 *
 * @return          New negated BigInt (BigInt_RETURN_NEW) or same as first parameter (BigInt_Override).
 */
native Handle:BigInt_Negate(Handle:bigint, BigInt_Method:method = BigInt_RETURN_NEW);





/**
 * Adds two BigInts.
 *
 * @param summand   BigInt Handle with first Summand.
 * @param summand2  BigInt Handle with second Summand.
 * @param method    Method to use here.
 *
 * @return          New added BigInt (BigInt_RETURN_NEW) or same as first parameter (BigInt_Override).
 */
native Handle:BigInt_Add(Handle:summand1, Handle:summand2, BigInt_Method:method = BigInt_RETURN_NEW);





/**
 * Substracts two BigInts.
 *
 * @param minuend    BigInt Handle with minuend.
 * @param subtrahend BigInt Handle with subtrahend.
 * @param method     Method to use here.
 *
 * @return           New substracted BigInt (BigInt_RETURN_NEW) or same as first parameter (BigInt_Override).
 */
native Handle:BigInt_Subtract(Handle:minuend, Handle:subtrahend, BigInt_Method:method = BigInt_RETURN_NEW);





/**
 * Multiplys two BigInts.
 *
 * @param multiplier   BigInt Handle with multiplier.
 * @param multiplicand BigInt Handle with multiplicand.
 * @param method       Method to use here.
 *
 * @return             New multiplied BigInt (BigInt_RETURN_NEW) or same as first parameter (BigInt_Override).
 */
native Handle:BigInt_Multiply(Handle:multiplier, Handle:multiplicand, BigInt_Method:method = BigInt_RETURN_NEW);





/**
 * Divides two BigInts.
 *
 * @param dividend     BigInt Handle with dividend.
 * @param divisor      BigInt Handle with divisor.
 * @param method       Method to use here.
 *
 * @return             New divided BigInt (BigInt_RETURN_NEW) or same as first parameter (BigInt_Override).
 */
native Handle:BigInt_Divide(Handle:dividend, Handle:divisor, BigInt_Method:method = BigInt_RETURN_NEW);





/**
 * Divides two BigInts and returns the remainder.
 *
 * @param dividend     BigInt Handle with dividend.
 * @param divisor      BigInt Handle with divisor.
 * @param method       Method to use here.
 *
 * @return             New BigInt with remainder of divison (BigInt_RETURN_NEW) or same as first parameter (BigInt_Override).
 */
native Handle:BigInt_DivideRemainder(Handle:dividend, Handle:divisor, BigInt_Method:method = BigInt_RETURN_NEW);





/**
 * Computes a BigInt from two BigInts
 *
 * @param bigint    BigInt Handle with 1. operator.
 * @param bigint2   BigInt Handle with 2. operator.
 * @param comp      Arithmetic operation to use.
 * @param method    Method to use here.
 *
 * @return          New computed BigInt (BigInt_RETURN_NEW) or same as first parameter (BigInt_Override).
 */
stock Handle:BigInt_Compute(Handle:bigint, Handle:bigint2, BigInt_Comp:comp, BigInt_Method:method = BigInt_RETURN_NEW)
{
	switch(comp)
	{
		case BigInt_ADD:
		{
			return BigInt_Add(Handle:bigint, Handle:bigint2, method);
		}
		case BigInt_SUBTRACT:
		{
			return BigInt_Subtract(Handle:bigint, Handle:bigint2, method);
		}
		case BigInt_MULTIPLY:
		{
			return BigInt_Multiply(Handle:bigint, Handle:bigint2, method);
		}
		case BigInt_DIVIDE:
		{
			return BigInt_Divide(Handle:bigint, Handle:bigint2, method);
		}
		default:
		{
			return BigInt_DivideRemainder(Handle:bigint, Handle:bigint2, method);
		}
	}
	
	return INVALID_HANDLE;
}





/**
 * Computes a BigInt from a BigInt and an Integer.
 *
 * @param bigint    BigInt Handle with 1. operator.
 * @param int       Integer with 2. operator.
 * @param comp      Arithmetic operation to use.
 * @param method    Method to use here.
 *
 * @return          New computed BigInt (BigInt_RETURN_NEW) or same as first parameter (BigInt_Override).
 */
stock Handle:BigInt_ComputeInt(Handle:bigint, int, BigInt_Comp:comp, BigInt_Method:method = BigInt_RETURN_NEW)
{
	new Handle:bigint2 = BigInt_Create(int);
	new Handle:newBigInt = BigInt_Compute(bigint, bigint2, comp, method);

	CloseHandle(bigint2);

	return newBigInt;
}





/**
 * Computes a BigInt from a BigInt and a String.
 *
 * @param bigint    BigInt Handle with 1. operator.
 * @param str       String with 2. operator.
 * @param comp      Arithmetic operation to use.
 * @param method    Method to use here.
 *
 * @return          New computed BigInt (BigInt_RETURN_NEW) or same as first parameter (BigInt_Override).
 */
stock Handle:BigInt_ComputeString(Handle:bigint, const String:str[], BigInt_Comp:comp, BigInt_Method:method = BigInt_RETURN_NEW)
{
	new Handle:bigint2 = BigInt_CreateFromString(str);
	new Handle:newBigInt = BigInt_Compute(bigint, bigint2, comp, method);

	CloseHandle(bigint2);

	return newBigInt;
}





/**
 * Computes a BigInt from an integer and a string
 *
 * @param int       Integer with 1. operator.
 * @param str       String with 2. operator.
 * @param comp      Arithmetic operation to use.
 * @param method    Method to use here.
 *
 * @return          New computed BigInt (BigInt_RETURN_NEW) or same as first parameter (BigInt_Override).
 */
stock Handle:BigInt_ComputeIntStr(int, const String:str[], BigInt_Comp:comp)
{
	new Handle:bigint = BigInt_Create(int);
	new Handle:bigint2 = BigInt_CreateFromString(str);

	new Handle:newBigInt = BigInt_Compute(bigint, bigint2, comp, BigInt_RETURN_NEW);

	CloseHandle(bigint);
	CloseHandle(bigint2);

	return newBigInt;
}






/**
 * Computes a BigInt from two Integers.
 *
 * @param int       Integer with 1. operator.
 * @param int2      Integer with 2. operator.
 * @param comp      Arithmetic operation to use.
 * @param method    Method to use here.
 *
 * @return          New computed BigInt (BigInt_RETURN_NEW) or same as first parameter (BigInt_Override).
 */
stock Handle:BigInt_ComputeInts(int, int2, BigInt_Comp:comp)
{
	new Handle:bigint = BigInt_Create(int);
	new Handle:bigint2 = BigInt_Create(int2);

	new Handle:newBigInt = BigInt_Compute(bigint, bigint2, comp, BigInt_RETURN_NEW);

	CloseHandle(bigint);
	CloseHandle(bigint2);

	return newBigInt;
}





/**
 * Computes a BigInt from two strings.
 *
 * @param str       String with 1. operator.
 * @param str2      String with 2. operator.
 * @param comp      Arithmetic operation to use.
 * @param method    Method to use here.
 *
 * @return          New computed BigInt (BigInt_RETURN_NEW) or same as first parameter (BigInt_Override).
 */
stock Handle:BigInt_ComputeStrs(const String:str[], const String:str2[], BigInt_Comp:comp)
{
	new Handle:bigint = BigInt_CreateFromString(str);
	new Handle:bigint2 = BigInt_CreateFromString(str2);

	new Handle:newBigInt = BigInt_Compute(bigint, bigint2, comp, BigInt_RETURN_NEW);

	CloseHandle(bigint);
	CloseHandle(bigint2);

	return newBigInt;
}









/*

USE BIT OPERATIONS ON A BIGINT

*/

/**
 * Performs the logical AND operation on two BigInts.
 *
 * @param bits1      BigInt Handle with first bits.
 * @param bits2      BigInt Handle with second bits.
 *
 * @return           New BigInt with result of the operation.
 */
native Handle:BigInt_BitAnd(Handle:bits1, Handle:bits2);




/**
 * Performs the logical OR operation on two BigInts.
 *
 * @param bits1      BigInt Handle with first bits.
 * @param bits2      BigInt Handle with second bits.
 *
 * @return           New BigInt with result of the operation.
 */
native Handle:BigInt_BitOr(Handle:bits1, Handle:bits2);




/**
 * Performs the logical XOR operation on two BigInts.
 *
 * @param bits1      BigInt Handle with first bits.
 * @param bits2      BigInt Handle with second bits.
 *
 * @return           New BigInt with result of the operation.
 */
native Handle:BigInt_BitXor(Handle:bits1, Handle:bits2);





/**
 * Computes a Bit operation from two BigInts
 *
 * @param bigint    BigInt Handle with 1. Bitstring.
 * @param bigint2   BigInt Handle with 2. Bitstring.
 * @param compBit   Bit operation to use.
 *
 * @return          New computed Bit BigInt.
 */
stock Handle:BigInt_ComputeBit(Handle:bigint, Handle:bigint2, BigInt_CompBit:compBit)
{
	switch(compBit)
	{
		case BigInt_AND:
		{
			return BigInt_BitAND(Handle:bigint, Handle:bigint2);
		}
		case BigInt_OR:
		{
			return BigInt_BitOR(Handle:bigint, Handle:bigint2);
		}
		default:
		{
			return BigInt_BitXOR(Handle:bigint, Handle:bigint2);
		}
	}
	
	return INVALID_HANDLE;
}





/**
 * Computes a Bit operation from a BigInt and an Integer
 *
 * @param bigint    BigInt Handle with 1. Bitstring.
 * @param int       Integer with 2. Bitstring.
 * @param compBit   Bit operation to use.
 *
 * @return          New computed Bit BigInt.
 */
stock Handle:BigInt_ComputeBitInt(Handle:bigint, int, BigInt_CompBit:compBit)
{
	new Handle:bigint2 = BigInt_Create(int);
	new Handle:newBigInt = BigInt_ComputeBit(bigint, bigint2, compBit);

	CloseHandle(bigint2);

	return newBigInt;
}





/**
 * Computes a Bit operation from a BigInt and an String.
 *
 * @param bigint    BigInt Handle with 1. Bitstring.
 * @param str       String with 2. Bitstring.
 * @param compBit   Bit operation to use.
 *
 * @return          New computed Bit BigInt.
 */
stock Handle:BigInt_ComputeBitString(Handle:bigint, const String:str[], BigInt_CompBit:compBit)
{
	new Handle:bigint2 = BigInt_CreateFromString(str);
	new Handle:newBigInt = BigInt_ComputeBit(bigint, bigint2, compBit);

	CloseHandle(bigint2);

	return newBigInt;
}





/**
 * Shift a given BigInt to the left.
 *
 * @param bits1      BigInt Handle with bits.
 * @param shift      Number to shift with.
 *
 * @return           New left-shifted BigInt.
 */
native Handle:BigInt_BitShiftLeft(Handle:bits, shift);





/**
 * Shift a given BigInt to the right.
 *
 * @param bits1      BigInt Handle with bits.
 * @param shift      Number to shift with.
 *
 * @return           New right-shifted BigInt.
 */
native Handle:BigInt_BitShiftRight(Handle:bits, shift);









/*

SOME ARITHMETIC FUNCTIONS WITH BIGINTS

*/

/**
 * Returns the greatest common divisor of a and b.
 *
 * @param a          BigInt Handle.
 * @param b          BigInt Handle.
 *
 * @return           Greatest Common divisor.
 */
native Handle:BigInt_GCD(Handle:a, Handle:b);





/**
 * Extended Euclidean algorithm.
 * Given m and n, finds gcd g and numbers r, s such that r*m + s*n == g.
 *
 * @param m          BigInt Handle.
 * @param n          BigInt Handle.
 * @param g          Handle to save result of g.
 * @param r          Handle to save result of r.
 * @param s          Handle to save result of s.
 *
 * @noreturn
 */
native BigInt_Euclidean(Handle:m, Handle:n, &Handle:g, &Handle:r, &Handle:s);





/**
 * Returns the multiplicative inverse of x modulo n.
 *
 * @param x          BigInt Handle.
 * @param n          BigInt Handle.
 *
 * @return           Multiplicative inverse or INVALID_HANDLE if x and n have a common factor.
 */
native Handle:BigInt_ModInv(Handle:x, Handle:n);





/**
 * Returns (base ^ exponent) % modulus.
 *
 * @param base       BigInt Handle with base.
 * @param exponent   BigInt Handle with exponent.
 * @param modulus    BigInt Handle with modulus.
 *
 * @return           (base ^ exponent) % modulus.
 */
native Handle:BigInt_ModExp(Handle:base, Handle:exponent, Handle:modulus);






public Extension:__ext_bigint =
{
	name = "BigInt",
	file = "bigint.ext",

	#if defined AUTOLOAD_EXTENSIONS
		autoload = 1,
	#else
		autoload = 0,
	#endif

	#if defined REQUIRE_EXTENSIONS
		required = 1,
	#else
		required = 0,
	#endif
};



#if !defined REQUIRE_EXTENSIONS
	public __ext_bigint_SetNTVOptional()
	{
		MarkNativeAsOptional("BigInt_Create");
		MarkNativeAsOptional("BigInt_CreateFromString");
		MarkNativeAsOptional("BigInt_ToInt");
		MarkNativeAsOptional("BigInt_ToString");
		MarkNativeAsOptional("BigInt_GetSign");
		MarkNativeAsOptional("BigInt_CompareTo");
		MarkNativeAsOptional("BigInt_GetLength");
		MarkNativeAsOptional("BigInt_GetBlock");
		MarkNativeAsOptional("BigInt_SetBlock");
		MarkNativeAsOptional("BigInt_Negate");
		MarkNativeAsOptional("BigInt_Add");
		MarkNativeAsOptional("BigInt_Subtract");
		MarkNativeAsOptional("BigInt_Multiply");
		MarkNativeAsOptional("BigInt_Divide");
		MarkNativeAsOptional("BigInt_DivideRemainder");
		MarkNativeAsOptional("BigInt_BitAnd");
		MarkNativeAsOptional("BigInt_BitOr");
		MarkNativeAsOptional("BigInt_BitXor");
		MarkNativeAsOptional("BigInt_BitShiftLeft");
		MarkNativeAsOptional("BigInt_BitShiftRight");
		MarkNativeAsOptional("BigInt_GCD");
		MarkNativeAsOptional("BigInt_Euclidean");
		MarkNativeAsOptional("BigInt_ModInv");
		MarkNativeAsOptional("BigInt_ModExp");
	}
#endif
