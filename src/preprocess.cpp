#include "function.h"

/*
该函数用于处理包含文件
2011-02:13
11:44
*/
TYPE_STATUS preprocess::includefile(TYPE_FILENAME fn)
{
	isShowErrline = true;
//	strprocess::supper(fn);
	if(g_includedfiles.find(fn)==g_includedfiles.end()){	//没解过包
		g_includedfiles.insert(g_includedfiles.end(), fn);	//标记
		//开始包含
		TYPE_STRING_ARRAY sa;
		if(fileio::loadtxtarray(fn, sa)){
			g_insarray.push_back("0:.FILE " + fn);
			g_insarray.push_back("0:.LINE 1");
			bool isNote = false;
			for(unsigned int i=0; i<sa.size(); ++i){
				if(sa[i].length()){
					TYPE_STRING line = sa[i];
					TYPE_STRING_ARRAY insa;
					strprocess::getinsarray(line, insa, isNote);
					for(unsigned int j=0; j<insa.size(); ++j){
						if(insa[j].length()){
							TYPE_STRING &ins = insa[j];
							TYPE_STRING upins = ins;
							strprocess::supper(upins);
							if(strprocess::getstringarg(upins, 0)==".INCLUDE" || strprocess::getstringarg(upins, 0)==".INC"){
								TYPE_STRING fnn = strprocess::getstringarg(ins, 1);
								if(fn.length()){
									g_filepoint.set(fn);
									g_filepoint.set(i+1);
									includefile(fnn);
									g_insarray.push_back("0:.FILE " + fn);
									g_insarray.push_back("0:.LINE " + valueswitch::numtostr(i+1));
								}
							}
							else{
								g_insarray.push_back(valueswitch::numtostr(i+1)+":"+ins);
							}
						}
					}
				}
			}
		}
	}
	else{	//已经包含
		errorprocess::showwarning(WARNING_ARE_INCFILE, fn);
	}
	return 0;
}

/*
该函数用于处理包含文件
2011-02:13
12:14
*/
void preprocess::inf()
{
	cout<<"PreInformation:\n";
	cout<<"\tIncludedFile:\n";
	for(TYPE_FILE_ARRAY::const_iterator it = g_includedfiles.begin(); it != g_includedfiles.end(); ++it){
		cout<<"\t\t"<<*it<<endl;
	}
	cout<<"\tInstruction:\n";
	for(unsigned int i=0; i<g_insarray.size(); ++i){
		cout<<"\t\t"<<g_insarray[i]<<endl;
	}
}










