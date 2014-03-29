#include "Data.h"
#include "sha1.h"
InitData::InitData()
{

}
ifstream OpenData::OpenDataFile()
{
	ifstream user_data_base("user_database.txt");
	ifstream admin_data_base("admin_database.txt");
	if((!user_data_base.is_open()) || (!admin_data_base.is_open()))
	{
		
	}
}