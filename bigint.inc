#if defined _bigint_included
	#endinput
#endif

#define _bigint_included





/* Enumeration for the sign of a BigInteger. */
enum BigInt_Sign
{
	NEGATIVE = -1, 
	ZERO = 0, 
	POSITIVE = 1
};



/* Enumeration for the result of a comparison. */
enum BigInt_CmpRes 
{
	LESS = -1, 
	EQUAL = 0, 
	GREATER = 1 
};


/**
 * Method to use for some Methods 
 * RETURN_NEW will return a new BigInt Handle and will not change the original one.
 * SET_DIRECT will override the given BigInt Handle and will return the same.
 * 
 */
enum BigInt_Method
{
	RETURN_NEW = 0, 
	SET_DIRECT = 1
};







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
 *
 * @return          BigInt Handle.
 */
native Handle:BigInt_CreateFromString(const String:str[]);




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
 *
 * @noreturn
 */
native BigInt_ToString(Handle:bigint, String:str[], maxlength);




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
	return BigInt_GetSign(bigint) == NEGATIVE;
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
	return BigInt_GetSign(bigint) == ZERO;
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
	return BigInt_GetSign(bigint) == POSITIVE;
}




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
	return BigInt_CompareTo(bigint, bigint2) == LESS;
}




/**
 * Checks whether the BigInt is lesser than a int value.
 *
 * @param bigint    BigInt Handle.
 * @param int       Integer to compare with.
 *
 * @return          True if lesser, otherwise false.
 */
stock bool:BigInt_IsLessInt(Handle:bigint, int)
{
	new Handle:bigint2 = BigInt_Create(int);
	new bool:cmp = BigInt_CompareTo(bigint, bigint2) == LESS;

	CloseHandle(bigint2);

	return cmp;
}




/**
 * Checks whether the BigInt is lesser than a string value.
 *
 * @param bigint    BigInt Handle.
 * @param str       String to compare with.
 *
 * @return          True if lesser, otherwise false.
 */
stock bool:BigInt_IsLessString(Handle:bigint, const String:str[])
{
	new Handle:bigint2 = BigInt_CreateFromString(str);
	new bool:cmp = BigInt_CompareTo(bigint, bigint2) == LESS;

	CloseHandle(bigint2);

	return cmp;
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
	return BigInt_CompareTo(bigint, bigint2) != GREATER;
}




/**
 * Checks whether the BigInt is lesser or equal than a int value.
 *
 * @param bigint    BigInt Handle.
 * @param int       Integer to compare with.
 *
 * @return          True if lesser or equal, otherwise false.
 */
stock bool:BigInt_IsLessOrEqualInt(Handle:bigint, int)
{
	new Handle:bigint2 = BigInt_Create(int);
	new bool:cmp = BigInt_CompareTo(bigint, bigint2) != GREATER;

	CloseHandle(bigint2);

	return cmp;
}




/**
 * Checks whether the BigInt is lesser or equal than a string value.
 *
 * @param bigint    BigInt Handle.
 * @param str       String to compare with.
 *
 * @return          True if lesser or equal, otherwise false.
 */
stock bool:BigInt_IsLessOrEqualString(Handle:bigint, const String:str[])
{
	new Handle:bigint2 = BigInt_CreateFromString(str);
	new bool:cmp = BigInt_CompareTo(bigint, bigint2) != GREATER;

	CloseHandle(bigint2);

	return cmp;
}





/**
 * Checks whether the BigInt is equal to another one.
 *
 * @param bigint    BigInt Handle.
 * @param bigint2   BigInt Handle to compare with.
 *
 * @return          True if equal, otherwise false.
 */
stock bool:BigInt_IsEqual(Handle:bigint, Handle:bigint2)
{
	return BigInt_CompareTo(bigint, bigint2) == EQUAL;
}




/**
 * Checks whether the BigInt is equal with a int value.
 *
 * @param bigint    BigInt Handle.
 * @param int       Integer to compare with.
 *
 * @return          True if equal, otherwise false.
 */
stock bool:BigInt_IsEqualInt(Handle:bigint, int)
{
	new Handle:bigint2 = BigInt_Create(int);
	new bool:cmp = BigInt_CompareTo(bigint, bigint2) == EQUAL;

	CloseHandle(bigint2);

	return cmp;
}




/**
 * Checks whether the BigInt is equal with a string value.
 *
 * @param bigint    BigInt Handle.
 * @param str       String to compare with.
 *
 * @return          True if equal, otherwise false.
 */
stock bool:BigInt_IsEqualString(Handle:bigint, const String:str[])
{
	new Handle:bigint2 = BigInt_CreateFromString(str);
	new bool:cmp = BigInt_CompareTo(bigint, bigint2) == EQUAL;

	CloseHandle(bigint2);

	return cmp;
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
	return BigInt_CompareTo(bigint, bigint2) != EQUAL;
}




/**
 * Checks whether the BigInt is not equal with a int value.
 *
 * @param bigint    BigInt Handle.
 * @param int       Integer to compare with.
 *
 * @return          True if not equal, otherwise false.
 */
stock bool:BigInt_IsNotEqualInt(Handle:bigint, int)
{
	new Handle:bigint2 = BigInt_Create(int);
	new bool:cmp = BigInt_CompareTo(bigint, bigint2) != EQUAL;

	CloseHandle(bigint2);

	return cmp;
}




/**
 * Checks whether the BigInt is not equal with a string value.
 *
 * @param bigint    BigInt Handle.
 * @param str       String to compare with.
 *
 * @return          True if not equal, otherwise false.
 */
stock bool:BigInt_IsNotEqualString(Handle:bigint, const String:str[])
{
	new Handle:bigint2 = BigInt_CreateFromString(str);
	new bool:cmp = BigInt_CompareTo(bigint, bigint2) != EQUAL;

	CloseHandle(bigint2);

	return cmp;
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
	return BigInt_CompareTo(bigint, bigint2) != LESS;
}




/**
 * Checks whether the BigInt is greater or equal than a int value.
 *
 * @param bigint    BigInt Handle.
 * @param int       Integer to compare with.
 *
 * @return          True if greater or equal, otherwise false.
 */
stock bool:BigInt_IsLessOrEqualInt(Handle:bigint, int)
{
	new Handle:bigint2 = BigInt_Create(int);
	new bool:cmp = BigInt_CompareTo(bigint, bigint2) != LESS;

	CloseHandle(bigint2);

	return cmp;
}




/**
 * Checks whether the BigInt is greater or equal than a string value.
 *
 * @param bigint    BigInt Handle.
 * @param str       String to compare with.
 *
 * @return          True if greater or equal, otherwise false.
 */
stock bool:BigInt_IsLessOrEqualString(Handle:bigint, const String:str[])
{
	new Handle:bigint2 = BigInt_CreateFromString(str);
	new bool:cmp = BigInt_CompareTo(bigint, bigint2) != LESS;

	CloseHandle(bigint2);

	return cmp;
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
	return BigInt_CompareTo(bigint, bigint2) == GREATER;
}




/**
 * Checks whether the BigInt is greater than a int value.
 *
 * @param bigint    BigInt Handle.
 * @param int       Integer to compare with.
 *
 * @return          True if greater, otherwise false.
 */
stock bool:BigInt_IsLessInt(Handle:bigint, int)
{
	new Handle:bigint2 = BigInt_Create(int);
	new bool:cmp = BigInt_CompareTo(bigint, bigint2) == GREATER;

	CloseHandle(bigint2);

	return cmp;
}




/**
 * Checks whether the BigInt is greater than a string value.
 *
 * @param bigint    BigInt Handle.
 * @param str       String to compare with.
 *
 * @return          True if greater, otherwise false.
 */
stock bool:BigInt_IsLessString(Handle:bigint, const String:str[])
{
	new Handle:bigint2 = BigInt_CreateFromString(str);
	new bool:cmp = BigInt_CompareTo(bigint, bigint2) == GREATER;

	CloseHandle(bigint2);

	return cmp;
}





/**
 * Gives the length of a BigInt.
 *
 * @param bigint    BigInt Handle.
 *
 * @return          Length of the BigInt.
 */
native BigInt_GetLength(Handle:bigint);





/**
 * Gives the capacity of a BigInt.
 *
 * @param bigint    BigInt Handle.
 *
 * @return          capacity of the BigInt.
 */
native BigInt_GetCapacity(Handle:bigint);





/**
 * Gives a block of a BigInt.
 *
 * @param bigint    BigInt Handle.
 * @param index     Index to get Block for.
 *
 * @return          block of the BigInt at given index.
 */
native BigInt_GetBlock(Handle:bigint, index);





/**
 * Sets a block of a BigInt.
 *
 * @param bigint    BigInt Handle.
 * @param index     Index of block to set.
 * @param newBlock  New Block to set to.
 * @param autoClose Auto close the old bigint of first parameter.
 *
 * @return          New BigInt with changed Block.
 */
native Handle:BigInt_SetBlock(Handle:bigint, index, newBlock, bool:autoClose = false);





/**
 * Negates a BigInt.
 *
 * @param bigint    BigInt Handle.
 * @param method    Method to use here.
 *
 * @return          New negated BigInt (RETURN_NEW) or same as first parameter (SET_DIRECT).
 */
native Handle:BigInt_Negate(Handle:bigint, BigInt_Method:method = RETURN_NEW);





/**
 * Adds two BigInts.
 *
 * @param summand   BigInt Handle with first Summand.
 * @param summand2  BigInt Handle with second Summand.
 * @param method    Method to use here.
 *
 * @return          New added BigInt (RETURN_NEW) or same as first parameter (SET_DIRECT).
 */
native Handle:BigInt_Add(Handle:summand1, Handle:summand2, BigInt_Method:method = RETURN_NEW);





/**
 * Adds a BigInt with an integer.
 *
 * @param summand   BigInt Handle with first Summand.
 * @param summand2  Integer with second Summand.
 * @param method    Method to use here.
 *
 * @return          New added BigInt (RETURN_NEW) or same as first parameter (SET_DIRECT).
 */
stock Handle:BigInt_AddInt(Handle:summand1, summand2, BigInt_Method:method = RETURN_NEW)
{
	new Handle:bigint = BigInt_Create(summand2);
	new Handle:newBigInt = BigInt_Add(summand1, bigint);

	CloseHandle(bigint);

	return newBigInt;
}





/**
 * Adds a BigInt with a string.
 *
 * @param summand   BigInt Handle with first Summand.
 * @param summand2  String with second Summand.
 * @param method    Method to use here.
 *
 * @return          New added BigInt (RETURN_NEW) or same as first parameter (SET_DIRECT).
 */
stock Handle:BigInt_AddString(Handle:summand1, const String:summand2[], BigInt_Method:method = RETURN_NEW)
{
	new Handle:bigint = BigInt_CreateFromString(summand2);
	new Handle:newBigInt = BigInt_Add(summand1, bigint);

	CloseHandle(bigint);

	return newBigInt;
}





/**
 * Substracts two BigInts.
 *
 * @param minuend    BigInt Handle with minuend.
 * @param subtrahend BigInt Handle with subtrahend.
 * @param method     Method to use here.
 *
 * @return           New substracted BigInt (RETURN_NEW) or same as first parameter (SET_DIRECT).
 */
native Handle:BigInt_Subtract(Handle:minuend, Handle:subtrahend, BigInt_Method:method = RETURN_NEW);





/**
 * Substracts a BigInt with an integer.
 *
 * @param minuend    BigInt Handle with minuend.
 * @param subtrahend Integer with subtrahend.
 * @param method     Method to use here.
 *
 * @return           New substracted BigInt (RETURN_NEW) or same as first parameter (SET_DIRECT).
 */
stock Handle:BigInt_SubtractInt(Handle:minuend, subtrahend, BigInt_Method:method = RETURN_NEW)
{
	new Handle:bigint = BigInt_Create(subtrahend);
	new Handle:newBigInt = BigInt_Subtract(minuend, bigint);

	CloseHandle(bigint);

	return newBigInt;
}





/**
 * Substracts a BigInt with a string.
 *
 * @param minuend    BigInt Handle with minuend.
 * @param subtrahend String with subtrahend.
 * @param method     Method to use here.
 *
 * @return           New substracted BigInt (RETURN_NEW) or same as first parameter (SET_DIRECT).
 */
stock Handle:BigInt_SubtractString(Handle:minuend, const String:subtrahend[], BigInt_Method:method = RETURN_NEW)
{
	new Handle:bigint = BigInt_CreateFromString(subtrahend);
	new Handle:newBigInt = BigInt_Subtract(minuend, bigint);

	CloseHandle(bigint);

	return newBigInt;
}





/**
 * Multiplys two BigInts.
 *
 * @param multiplier   BigInt Handle with multiplier.
 * @param multiplicand BigInt Handle with multiplicand.
 * @param method       Method to use here.
 *
 * @return             New multiplied BigInt (RETURN_NEW) or same as first parameter (SET_DIRECT).
 */
native Handle:BigInt_Multiply(Handle:multiplier, Handle:multiplicand, BigInt_Method:method = RETURN_NEW);





/**
 * Multiplys a BigInt with an integer.
 *
 * @param multiplier   BigInt Handle with multiplier.
 * @param multiplicand Integer with multiplicand.
 * @param method       Method to use here.
 *
 * @return             New multiplied BigInt (RETURN_NEW) or same as first parameter (SET_DIRECT).
 */
stock Handle:BigInt_MultiplyInt(Handle:multiplier, multiplicand, BigInt_Method:method = RETURN_NEW)
{
	new Handle:bigint = BigInt_Create(multiplicand);
	new Handle:newBigInt = BigInt_Multiply(multiplier, bigint);

	CloseHandle(bigint);

	return newBigInt;
}





/**
 * Multiplys a BigInt with a string.
 *
 * @param multiplier   BigInt Handle with multiplier.
 * @param multiplicand String with multiplicand.
 * @param method       Method to use here.
 *
 * @return             New multiplied BigInt (RETURN_NEW) or same as first parameter (SET_DIRECT).
 */
stock Handle:BigInt_MultiplyString(Handle:multiplier, const String:multiplicand[], BigInt_Method:method = RETURN_NEW)
{
	new Handle:bigint = BigInt_CreateFromString(multiplicand);
	new Handle:newBigInt = BigInt_Multiply(multiplier, bigint);

	CloseHandle(bigint);

	return newBigInt;
}





/**
 * Divides two BigInts.
 *
 * @param dividend     BigInt Handle with dividend.
 * @param divisor      BigInt Handle with divisor.
 * @param method       Method to use here.
 *
 * @return             New divided BigInt (RETURN_NEW) or same as first parameter (SET_DIRECT).
 */
native Handle:BigInt_Divide(Handle:dividend, Handle:divisor, BigInt_Method:method = RETURN_NEW);





/**
 * Divides a BigInt with an integer.
 *
 * @param dividend     BigInt Handle with dividend.
 * @param divisor      Integer with divisor.
 * @param method       Method to use here.
 *
 * @return             New divided BigInt (RETURN_NEW) or same as first parameter (SET_DIRECT).
 */
stock Handle:BigInt_DivideInt(Handle:dividend, divisor, BigInt_Method:method = RETURN_NEW)
{
	new Handle:bigint = BigInt_Create(divisor);
	new Handle:newBigInt = BigInt_Divide(dividend, bigint);

	CloseHandle(bigint);

	return newBigInt;
}





/**
 * Divides a BigInt with a string.
 *
 * @param dividend     BigInt Handle with dividend.
 * @param divisor      String with divisor.
 * @param method       Method to use here.
 *
 * @return             New divided BigInt (RETURN_NEW) or same as first parameter (SET_DIRECT).
 */
stock Handle:BigInt_DivideString(Handle:dividend, const String:divisor[], BigInt_Method:method = RETURN_NEW)
{
	new Handle:bigint = BigInt_CreateFromString(divisor);
	new Handle:newBigInt = BigInt_Divide(dividend, bigint);

	CloseHandle(bigint);

	return newBigInt;
}





/**
 * Divides two BigInts and returns the remainder.
 *
 * @param dividend     BigInt Handle with dividend.
 * @param divisor      BigInt Handle with divisor.
 * @param method       Method to use here.
 *
 * @return             New BigInt with remainder of divison (RETURN_NEW) or same as first parameter (SET_DIRECT).
 */
native Handle:BigInt_DivideRemainder(Handle:dividend, Handle:divisor, BigInt_Method:method = RETURN_NEW);





/**
 * Divides a BigInt with an integer and returns the remainder.
 *
 * @param dividend     BigInt Handle with dividend.
 * @param divisor      Integer with divisor.
 * @param method       Method to use here.
 *
 * @return             New BigInt with remainder of divison (RETURN_NEW) or same as first parameter (SET_DIRECT).
 */
stock Handle:BigInt_DivideRemainderInt(Handle:dividend, divisor, BigInt_Method:method = RETURN_NEW)
{
	new Handle:bigint = BigInt_Create(divisor);
	new Handle:newBigInt = BigInt_DivideRemainder(dividend, bigint);

	CloseHandle(bigint);

	return newBigInt;
}





/**
 * Divides a BigInt with a string and returns the remainder.
 *
 * @param dividend     BigInt Handle with dividend.
 * @param divisor      String with divisor.
 * @param method       Method to use here.
 *
 * @return             New BigInt with remainder of divison (RETURN_NEW) or same as first parameter (SET_DIRECT).
 */
stock Handle:BigInt_DivideRemainderString(Handle:dividend, const String:divisor[], BigInt_Method:method = RETURN_NEW)
{
	new Handle:bigint = BigInt_CreateFromString(divisor);
	new Handle:newBigInt = BigInt_DivideRemainder(dividend, bigint);

	CloseHandle(bigint);

	return newBigInt;
}





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
 * Performs the logical AND operation on a BigInt and an integer.
 *
 * @param bits1      BigInt Handle with first bits.
 * @param bits2      Integer with second bits.
 *
 * @return           New BigInt with result of the operation.
 */
stock Handle:BigInt_BitAndInt(Handle:bits1, bits2)
{
	new Handle:bigint = BigInt_Create(bits2);
	new Handle:newBigInt = BigInt_BitAnd(bits1, bigint);

	CloseHandle(bigint);

	return newBigInt;
}





/**
 * Performs the logical AND operation on a BigInt and a string.
 *
 * @param bits1      BigInt Handle with first bits.
 * @param bits2      String with second bits.
 *
 * @return           New BigInt with result of the operation.
 */
stock Handle:BigInt_BitAndString(Handle:bits1, const String:bits2[])
{
	new Handle:bigint = BigInt_CreateFromString(bits2);
	new Handle:newBigInt = BigInt_BitAnd(bits1, bigint);

	CloseHandle(bigint);

	return newBigInt;
}





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
 * Performs the logical OR operation on a BigInt and an integer.
 *
 * @param bits1      BigInt Handle with first bits.
 * @param bits2      Integer with second bits.
 *
 * @return           New BigInt with result of the operation.
 */
stock Handle:BigInt_BitOrInt(Handle:bits1, bits2)
{
	new Handle:bigint = BigInt_Create(bits2);
	new Handle:newBigInt = BigInt_BitOr(bits1, bigint);

	CloseHandle(bigint);

	return newBigInt;
}





/**
 * Performs the logical AND operation on a BigInt and a string.
 *
 * @param bits1      BigInt Handle with first bits.
 * @param bits2      String with second bits.
 *
 * @return           New BigInt with result of the operation.
 */
stock Handle:BigInt_BitOrString(Handle:bits1, const String:bits2[])
{
	new Handle:bigint = BigInt_CreateFromString(bits2);
	new Handle:newBigInt = BigInt_BitOr(bits1, bigint);

	CloseHandle(bigint);

	return newBigInt;
}





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
 * Performs the logical XOR operation on a BigInt and an integer.
 *
 * @param bits1      BigInt Handle with first bits.
 * @param bits2      Integer with second bits.
 *
 * @return           New BigInt with result of the operation.
 */
stock Handle:BigInt_BitXorInt(Handle:bits1, bits2)
{
	new Handle:bigint = BigInt_Create(bits2);
	new Handle:newBigInt = BigInt_BitXor(bits1, bigint);

	CloseHandle(bigint);

	return newBigInt;
}





/**
 * Performs the logical XOR operation on a BigInt and a string.
 *
 * @param bits1      BigInt Handle with first bits.
 * @param bits2      String with second bits.
 *
 * @return           New BigInt with result of the operation.
 */
stock Handle:BigInt_BitXorString(Handle:bits1, const String:bits2[])
{
	new Handle:bigint = BigInt_CreateFromString(bits2);
	new Handle:newBigInt = BigInt_BitXor(bits1, bigint);

	CloseHandle(bigint);

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
		MarkNativeAsOptional("BigInt_GetCapacity");
		MarkNativeAsOptional("BigInt_GetBlock");
		MarkNativeAsOptional("BigInt_Negate");
		MarkNativeAsOptional("BigInt_Add");
		MarkNativeAsOptional("BigInt_Subtract");
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