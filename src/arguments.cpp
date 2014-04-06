#include "function.h"

/*
该函数用于将初始化参数
2011-02-13
19:18
*/
TYPE_STATUS arguments::initarg(int args, char *arg[])
{
	TYPE_STRING thisexe = arg[0];
	for(int i = 1; i < args; ++i){
		string nowarg = arg[i];
		if(nowarg == "--i"){	//指令
			instruction::inf();
			exit(0);
		}
		else if(nowarg == "--t"){	//任务
			g_tasinf = true;
		}
		else if(nowarg == "--l"){	//标签
			g_labinf = true;
		}
		else if(nowarg == "--s"){	//代码段
			g_seginf = true;
		}
		else if(nowarg == "-o"){	//输出文件名
			if(i < (args-1)){
				g_outfilename = arg[++i];
			}
		}
		else if(nowarg == "-w"){	//警告级别
			if(i < (args-1)){
				TYPE_NUM lv = valueswitch::strtonum(arg[++i]);
				if(lv>=0 && lv<=2){
					g_warninglevel = lv;
				}
				else{
					cout<<thisexe<<" -w (0-2)"<<endl;
				}
			}
		}
		else if(nowarg == "-e"){	//错误级别
			if(i < (args-1)){
				TYPE_NUM lv = valueswitch::strtonum(arg[++i]);
				if(lv>=0 && lv<=2){
					g_errorlevel = lv;
				}
				else{
					cout<<thisexe<<" -e (0-2)"<<endl;
				}
			}
		}
		else if(nowarg == "-h" || nowarg == "/?"){	//输出文件名
			help();
		}
		else if(nowarg == "-v"){	//输出文件名
			version();
		}
		else if(nowarg.find_first_of('.') != string::npos && g_infilename.length()==0){	//输出文件名
			g_infilename = nowarg;
		}
		else{
			cout<<thisexe<<" fail: Unknown arguments:"<<nowarg<<endl;
		}
	}
	if(g_infilename.length()==0){
		cout<<thisexe<<" fail: no input file"<<endl;
		exit(1);
	}
	if(g_outfilename.length()==0){
		g_outfilename = g_infilename.substr(0, g_infilename.find_last_of('.'))+".nes";
	}
	return 1;
}

/*
该函数用于显示帮助
2011-02-13
20:16
*/
void arguments::help()
{
	cout<<"Usage: nesa.exe [options] file\n";
	cout<<"Options:\n";
	cout<<" -o name\tName the output file\n";
	cout<<" -w num \tSet warning level (0-2)\n";
	cout<<" -e num \tSet errror level (0-2)\n";
	cout<<" -v     \tDisplay version\n";
	cout<<" -h     \tHelp (this text)\n";
	cout<<" --i    \tDisplay supported instruction\n";
	cout<<" --l    \tDisplay labels information\n";
	cout<<" --s    \tDisplay segments information\n";
	cout<<" --t    \tDisplay tasks information\n";
	exit(0);
}

/*
该函数用于显示版本
2011-02-13
20:18
*/
void arguments::version()
{
	cout<<g_version<<endl;
	exit(0);
}

