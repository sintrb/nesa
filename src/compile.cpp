#include "function.h"

/*
�ú������ڱ���ȫ��g_code�Ĵ���
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
�ú������ڱ��뵥ָ��
2011-01-30
11:53
*/
TYPE_STATUS compile::compileone(TYPE_STRING& ins)
{
//	cout << ins<<endl;
	g_filepoint.set(valueswitch::numvalue(ins.substr(0, ins.find_first_of(':'))));
	ins = ins.substr(ins.find_first_of(':')+1, string::npos);
	if(ins.find_last_of(':') == (ins.length() - 1)){//��ǩ
		ins = ".LABEL " + ins.substr(0, ins.length() - 1);
	}
	g_code_line = ins;
	if(ins[0] == '.'){	//αָ��
		macro::macrojudge(ins);
	}
	else{	//ָ��
		instruction::compileins(ins);
	}
	return 1;
}

