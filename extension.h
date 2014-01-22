/**
 * -----------------------------------------------------
 * File        extension.h
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

#ifndef EXTENSION_H
#define EXTENSION_H


#include "smsdk_ext.h"
#include "BigIntegerLibrary.hh"





class BigIntExtension : public SDKExtension, public IHandleTypeDispatch
{
public:
	/**
	 * This is called after the initial loading sequence has been processed.
	 *
	 * @param error        Error message buffer.
	 * @param maxlength    Size of error message buffer.
	 * @param late         Whether or not the module was loaded after map load.
	 * @return             True to succeed loading, false to fail.
	 */
	virtual bool SDK_OnLoad(char *error, size_t maxlength, bool late);


	/**
	 * Called when destroying a handle. Must be implemented.
	 *
	 * @param type		   Handle type.
	 * @param object	   Handle internal object.
	 */
	virtual void OnHandleDestroy(HandleType_t type, void *object);
};




cell_t BigInt_Create(IPluginContext *pContext, const cell_t *params);
cell_t BigInt_CreateFromString(IPluginContext *pContext, const cell_t *params);
cell_t BigInt_ToInt(IPluginContext *pContext, const cell_t *params);
cell_t BigInt_ToString(IPluginContext *pContext, const cell_t *params);
cell_t BigInt_GetSign(IPluginContext *pContext, const cell_t *params);
cell_t BigInt_CompareTo(IPluginContext *pContext, const cell_t *params);
cell_t BigInt_GetLength(IPluginContext *pContext, const cell_t *params);
cell_t BigInt_GetCapacity(IPluginContext *pContext, const cell_t *params);
cell_t BigInt_GetBlock(IPluginContext *pContext, const cell_t *params);
cell_t BigInt_Negate(IPluginContext *pContext, const cell_t *params);
cell_t BigInt_Add(IPluginContext *pContext, const cell_t *params);
cell_t BigInt_Subtract(IPluginContext *pContext, const cell_t *params);
cell_t BigInt_Multiply(IPluginContext *pContext, const cell_t *params);
cell_t BigInt_Divide(IPluginContext *pContext, const cell_t *params);
cell_t BigInt_DivideRemainder(IPluginContext *pContext, const cell_t *params);
cell_t BigInt_BitAnd(IPluginContext *pContext, const cell_t *params);
cell_t BigInt_BitOr(IPluginContext *pContext, const cell_t *params);
cell_t BigInt_BitXor(IPluginContext *pContext, const cell_t *params);
cell_t BigInt_BitShiftLeft(IPluginContext *pContext, const cell_t *params);
cell_t BigInt_BitShiftRight(IPluginContext *pContext, const cell_t *params);
cell_t BigInt_GCD(IPluginContext *pContext, const cell_t *params);
cell_t BigInt_Euclidean(IPluginContext *pContext, const cell_t *params);
cell_t BigInt_ModInv(IPluginContext *pContext, const cell_t *params);
cell_t BigInt_ModExp(IPluginContext *pContext, const cell_t *params);


#endif