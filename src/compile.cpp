#include "function.h"

/*
该函数用于编译全部g_code的代码
2011-01-30
11:52
*/

TYPE_STATUS compile::compileall()
{
	for(unsigned int i=0; i<g_insarray.size(); ++i){
		if(g_insarray[i].length()){
			compile::compileone(g_insarray[i]);
		}
	}
	return 1;
}

	
/*
该函数用于编译单指令
2011-01-30
11:53
*/
TYPE_STATUS compile::compileone(TYPE_STRING& ins)
{
//	cout << ins<<endl;
	g_filepoint.set(valueswitch::numvalue(ins.substr(0, ins.find_first_of(':'))));
	ins = ins.substr(ins.find_first_of(':')+1, string::npos);
	if(ins.find_last_of(':') == (ins.length() - 1)){//标签
		ins = ".LABEL " + ins.substr(0, ins.length() - 1);
	}
	g_code_line = ins;
	if(ins[0] == '.'){	//伪指令
		macro::macrojudge(ins);
	}
	else{	//指令
		instruction::compileins(ins);
	}
	return 1;
}

