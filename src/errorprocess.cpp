#include "function.h"

/*
该函数用于显示错误信息
2011-01-31
11:50
*/
void  errorprocess::showerr(TYPE_ERROR err, TYPE_STRING serr)
{
	if(g_errorlevel == 2){	//级别2
		return;
	}
	front();
	cout<<"error: ";
	switch(err)
	{
		//Miss err
		case ERR_MISS_FH:{
			cout<<"missing \';\'";
			break;
		}
		case ERR_MISS_YH:{
			cout<<"missing \'\"\'";
			break;
		}
		case ERR_MISS_LH:{
			cout<<"missing \'{\'";
			break;
		}
		case ERR_MISS_RH:{
			cout<<"missing \'}\'";
			break;
		}
		case ERR_MISS_LK:{
			cout<<"missing \'(\'";
			break;
		}
		case ERR_MISS_RK:{
			cout<<"missing \')\'";
			break;
		}
		case ERR_MISS_ZS:{
			cout<<"missing \'*/\'";
			break;
		}
		case ERR_MISS_LF:{
			cout<<"missing \'[/\'";
			break;
		}
		case ERR_MISS_RF:{
			cout<<"missing \']/\'";
			break;
		}
		
		//Out err
		case ERR_OUT_CODE:{
			cout<<"there are too many code in segment:"<<serr;
			break;
		}
		
		case ERR_OUT_ORG:{
			cout<<"the org address is out of range:"<<serr;
			break;
		}
		
		case ERR_OUT_RANGE:{
			cout<<"the data out of range:"<<serr;
			break;
		}
		
		case ERR_OUT_ADD:{
			cout<<"CPU can't access the address(0000-ffff):"<<serr;
			break;
		}
		
		case ERR_OUT_REV:{
			cout<<"the address out of range:"<<serr;
			break;
		}
		
		//Have err
		case ERR_HAVA_SEG:{
			cout<<"already define segment:"<<serr;
			break;
		}
		case ERR_HAVA_LAB:{
			cout<<"already define label:"<<serr;
			break;
		}
		case ERR_HAVA_INS:{
			cout<<"already define instruction:"<<serr;
			break;
		}
		
		//Unknow err
		case ERR_UK_LABEL:{
			cout<<"unknow label \'"<<serr<<"\'";
			break;
		}
		case ERR_UK_SYM:{
			cout<<"unknow symbol \'"<<serr<<"\'";
			break;			
		}
		
		
		//Size err
		case ERR_SIZE_SEG:{
			cout<<"the size is illegality(maybe too large) in segment define:"<<serr;
			break;
		}
		
		//Hava No err
		case ERR_HAVANO_SEG:{
			cout<<"have no such segment:"<<serr;
			break;
		}
		case ERR_HAVANO_FILE:{
			cout<<"have no such file:"<<serr;
			break;
		}
		case ERR_HAVANO_LAB:{
			cout<<"have no such label:"<<serr;
			break;
		}
		case ERR_OPEN_FILE:{
			cout<<"can't open file:"<<serr;
			break;
		}		
		
		
		//Empty err
		case ERR_UNDEFINE_SEG:{
			cout<<"undefine any segment:";
			break;
		}
		case ERR_UNDEFINE_LAB:{
			cout<<"undefine Label:"<<serr;
			break;
		}
		
		case ERR_ERR_FILENAME:{
			cout<<"filename error:"<<serr;
			break;
		}
		case ERR_EMPTY_FILENAME:{
			cout<<"filename is empty";
			break;
		}
		case ERR_EMPTY_NUM:{
			cout<<"the number is empty"<<serr;
			break;
		}
		
		case ERR_CNT_LAB:{
			cout<<"can't solve label:"<<serr;
			break;
		}
		
		//Ill err
		case ERR_ILL_SYN:{
			cout<<"illegality syntax:"<<serr;
			break;
		}
		
		
		//Not err
		case ERR_NOT_NUM:{
			cout<<"not a number:"<<serr;
			break;
		}
		
		case ERR_NOT_CONST:{
			cout<<"not a const number:"<<serr;
			break;			
		}
		
		
		//other
		default:{
			cout<<"Unknow error!!!";
		}
	}
	back();
	if(g_errorlevel == 0){	//中断
		label::labelinf();
		segmentmanager::segmentinf();
		task::taskinf();
		exit(1);
	}
}


/*
该函数用于显示错误信息
2011-01-29
20:00
*/
void  errorprocess::showerr(TYPE_ERROR err)
{
	showerr(err, "");
}

/*
该函数用于显示警告信息包含字串
2011-01-30
14:27
*/
void  errorprocess::showwarning(TYPE_WARNING wn, TYPE_STRING swn)
{
	if(g_warninglevel == 2){	//级别2
		return;
	}
	front();
	cout<<"warning:";
	switch(wn)
	{
		case WARNING_NO_USING:{
			cout<<"it's no using:"<<swn;
			break;
		}
		case UNKNOWN_NUM_TYPE:{
			cout<<"unknown number type:"<<swn;
			break;
		}
		case UNKNOWN_MAC_TYPE:{
			cout<<"unknown macro:"<<swn;
			break;
		}
		case WARNING_EMPTY_NUM:{
			cout<<"the number is empty"<<swn;
			break;
		}
		case WARNING_ARE_INCFILE:{
			cout<<"already include file:"<<swn;
			break;
		}
		case WARNING_FLOW_OVER:{
			cout<<"the number over flow:"<<swn;
			break;
		}
		case WARNING_FLOW_UNDER:{
			cout<<"the number under flow:"<<swn;
			break;
		}
		case WARNING_TYPE_WARN:{
			cout<<"the date type is not matching:"<<swn;
			break;
		}
	}
	back();
	if(g_warninglevel == 0){	//中断
		exit(1);
	}
}


/*
该函数用于显示警告信息
2011-01-30
12:43
*/
void  errorprocess::showwarning(TYPE_WARNING wn)
{
	showwarning(wn, "");
}

/*
该函数用于显示信息头
2011-02-03
00:30
*/
void  errorprocess::front()
{
	TYPE_FILENAME fn = g_filepoint.getfilename();
	TYPE_LINE ln = g_filepoint.getline();
	static int nb = 0;
	if(fn.length()>0){
		cout<<dec<<"NO:"<<nb++<<" ";
		cout<<fn<<":"<<ln<<" ";
	}
}
	
/*
该函数用于显示信息尾
2011-02-03
00:38
*/
void  errorprocess::back()
{
	cout<<endl;
	if(isShowErrline)cout<<"\tThe line:"<<g_code_line<<endl;
		else cout<<endl;
}
