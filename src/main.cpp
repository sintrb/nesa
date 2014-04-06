#include "stddef.h"
#include "function.h"






int main(int args, char *arg[])
{
	instruction::init();
	arguments::initarg(args, arg);
	preprocess::includefile(g_infilename);
	compile::compileall();
	task::dotask();
	segmentmanager::saveoutfile(g_outfilename);
	if(g_labinf)label::labelinf();
	if(g_seginf)segmentmanager::segmentinf();
	if(g_tasinf)task::taskinf();
	cout<<"compile success!!!"<<endl;
	return 0;
}

