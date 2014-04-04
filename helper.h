/*
辅助函数（helper function）
Designed by DeathSea 2014 Jnu
sha1值运算，验证
*/
#include <iostream>
#include "sha1.h"
using std::string;
class helper
{
private:
	SHA1  sha;
public:
	bool check(const char *input_char_array,unsigned *input_sha );
	void calculate(const char *input_char_array,unsigned *input_sha);
};