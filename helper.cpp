#include "helper.h"
bool helper::check(const char * input_char_array,unsigned *input_sha)
{
	helper::sha.Reset();
	unsigned output_sha[5];
	bool check_result = true;
	if(helper::sha.Result(output_sha))
	{
		for(int i=0;i<=4;i++)
		{
			if(output_sha[i] != input_sha[i])
			{
				check_result = false;
				break;
			}
		}
	}
}