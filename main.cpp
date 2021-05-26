#include <fstream>
#include <getopt.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * @author dts，just for demo.
 * @author pxl, fuck demo.
 */
const std::string DATABASE_NAME = "tianchi_dts_data";														// 待处理数据库名，无需修改
const std::string SCHEMA_FILE_DIR = "schema_info_dir";														// schema文件夹，无需修改。
const std::string SCHEMA_FILE_NAME = "schema.info";															// schema文件名，无需修改。
const std::string SOURCE_FILE_DIR = "source_file_dir";														// 输入文件夹，无需修改。
const std::string SINK_FILE_DIR = "sink_file_dir";															// 输出文件夹，无需修改。
const std::string SOURCE_FILE_NAME_TEMPLATE = "tianchi_dts_source_data_";									// 输入文件名，无需修改。
const std::string SINK_FILE_NAME_TEMPLATE = "tianchi_dts_sink_data_";										// 输出文件名模板，无需修改。
const std::string CHECK_TABLE_SETS = "customer,district,item,new_orders,order_line,orders,stock,warehouse"; // 待处理表集合，无需修改。
//COLUMN NUMBER 5
//{"Name":"i_id","Ordinal":1,"Unsigned":false,"CharSet":null,"ColumnDef":"int(11)","Length":null,"Precision":10,"Scale":0}
class ColumnDefType
{
};
class ColumnInfo
{
	std::string name;
	int ordinal;
	bool isUnsigned;
	std::string charSet;
	ColumnDefType columnDef;
	int length;
	int precision;
	int scale;
};
class TableInfo
{
};

class Demo
{
public:
	std::string sourceDirectory;
	std::string sinkDirectory;

public:
	bool initialSchemaInfo()
	{
		std::cout << "Read schema_info_dir/schema.info file and construct table in memory." << std::endl;
		std::string path = sourceDirectory + "//" + SCHEMA_FILE_DIR + "//" + SCHEMA_FILE_NAME;
		std::cout << "path: " << path << std::endl;
		std::ifstream schemaInfo(path);
		if (!schemaInfo.is_open())
		{
			std::cout << "not found: schemaInfo" << std::endl;
			return false;
		}
		return true;
	}

	bool loadSourceData(int dataNumber)
	{
		std::cout << "Read source_file_dir/tianchi_dts_source_data_* file" << std::endl;
		std::string path = sourceDirectory + "//" + SOURCE_FILE_DIR + "//" + SOURCE_FILE_NAME_TEMPLATE + std::to_string(dataNumber);
		std::cout << "path: " << path << std::endl;
		std::ifstream sourceData(path);
		if (!sourceData.is_open())
		{
			std::cout << "not found: sourceData " + std::to_string(dataNumber) << std::endl;
			return false;
		}
		return true;
	}

	void cleanData()
	{
		std::cout << "Clean and sort the source data." << std::endl;
		return;
	}

	void sinkData(std::string path)
	{
		std::cout << "Sink the data." << std::endl;
		std::cout << "path: " << path << std::endl;
		std::cout << "sinkDirectory: " << sinkDirectory << std::endl;
		return;
	}
};

/**
Input: 
1. Disordered source data (in SOURCE_FILE_DIR)
2. Schema information (in std::string)

Process:
    data clean: 
    1) duplicate primary key data;
    2) exceed char length data;
    3) error date time type data;
    4) error decimal type data;
    5) error data type.

    sort by pk

Output:
1. Sorted data of each table (out SINK_FILE_DIR)

**/
int main(int argc, char *argv[])
{
	Demo *demo = new Demo();

	static struct option long_options[] = {
		{"input_dir", required_argument, 0, 'i'},
		{"output_dir", required_argument, 0, 'o'},
		{"output_db_url", required_argument, 0, 'r'},
		{"output_db_user", required_argument, 0, 'u'},
		{"output_db_passwd", required_argument, 0, 'p'},
		{0, 0, 0, 0}};
	int opt_index;
	int opt;

	while (-1 != (opt = getopt_long(argc, argv, "", long_options, &opt_index)))
	{

		switch (opt)
		{
		case 'i':
			demo->sourceDirectory = optarg;
			break;
		case 'o':
			demo->sinkDirectory = optarg;
			break;
		}
	}

	std::cout << "[Start]\tload schema information." << std::endl;
	// load schema information.
	demo->initialSchemaInfo();
	std::cout << "[End]\tload schema information." << std::endl;

	// load input Start file.
	std::cout << "[Start]\tload input Start file." << std::endl;
	int dataNumber = 1;
	while (demo->loadSourceData(dataNumber))
		dataNumber++;
	std::cout << "[End]\tload input Start file." << std::endl;

	// data clean.
	std::cout << "[Start]\tdata clean." << std::endl;
	demo->cleanData();
	std::cout << "[End]\tdata clean." << std::endl;

	// sink to target file
	std::cout << "[Start]\tsink to target file." << std::endl;
	demo->sinkData(SINK_FILE_DIR);
	std::cout << "[End]\tsink to target file." << std::endl;

	return 0;
}
