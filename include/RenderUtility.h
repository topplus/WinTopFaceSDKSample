#ifndef	RENDER_UTILITY_H
#define RENDER_UTILITY_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <list>
#include <algorithm>

namespace sceneRenderer
{
	using namespace std;

	class LogUtility
	{
	public:
		static void Log(string str)
		{
			cout<<str<<endl;
		}

		static void LogError(string str)
		{
			cout<<endl<<"error\t"<<str<<endl;
		}


	};

}




#endif
