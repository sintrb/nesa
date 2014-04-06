#include "stddef.h"

/*
该函数用于获取数据描述
2011-02-12
19:02
*/
TYPE_STRING gloabfunction::datatypetostring(TYPE_DATATYPE dt)
{
	TYPE_STRING ty = "";
	switch(dt)
	{
		case DATATYPE_NONE:{
			ty = "NONE";
			break;
		}
		case DATATYPE_ADDRESS:{
			ty = "ADDRESS";
			break;
		}
		case DATATYPE_WORD:{
			ty = "WORD";
			break;
		}
		case DATATYPE_BYTE:{
			ty = "BYTE";
			break;
		}
		case DATATYPE_HBYT:{
			ty = "HBYT";
			break;
		}
		case DATATYPE_LBYT:{
			ty = "LBYT";
			break;
		}
		case DATATYPE_RELATIVE:{
			ty = "RELATIVE";
			break;
		}
		case DATATYPE_LABEL:{
			ty = "LABEL";
			break;
		}
		case DATATYPE_ZPADDRESS:{
			ty = "ZPADDRESS";
			break;
		}
		case DATATYPE_TASK:{
			ty = "TASK";
			break;
		}
		case DATATYPE_BIG:{
			ty = "BIG";
			break;
		}
	}
	return ty;
}

/*
该函数用于获取数据尺寸
2011-02-12
20:08
*/
TYPE_WORD gloabfunction::datatypesize(TYPE_DATATYPE dt)
{
	TYPE_WORD sz = 0;
	switch(dt)
	{
		case DATATYPE_NONE:
		case DATATYPE_LABEL:
		case DATATYPE_TASK:{
			sz = 0;
			break;
		}
		
		case DATATYPE_BIG:
		case DATATYPE_ADDRESS:
		case DATATYPE_WORD:
		{
			sz = 2;
			break;
		}
		case DATATYPE_ZPADDRESS:
		case DATATYPE_BYTE:
		case DATATYPE_HBYT:
		case DATATYPE_LBYT:
		case DATATYPE_RELATIVE:{
			sz = 1;
			break;
		}
	}
	return sz;
}


