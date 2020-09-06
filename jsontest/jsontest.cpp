#include <cpplinq.hpp>
#include <rapidjson/filereadstream.h>
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "../../std_lib_facilities.h"

using namespace rapidjson;
using namespace cpplinq;

struct employee {
	string id;
	string name;
	string city;

	employee(string id = "", string name = "", string city = "")
		:id(move(id)), name(move(name)), city(move(city))
	{
	}
};


void print(vector<employee> test_vector) {

	auto result = from(test_vector)
		>> where([](employee const & e) {return e.city == "Toronto"; })
		>> orderby_ascending([](employee const & e) {return e.name; })
		>> select([](employee const & e) {return e.name; })
		>> to_vector();

	for (int i = 0; i != result.size(); ++i) {
		cout << result[i] << "\n";
	}
}

int main()
{

	vector<employee> test_vector;
	test_vector.push_back(employee());

	FILE *stream;
	fopen_s(&stream, "C:\\Users\\ejeng\\source\\repos\\jsontest\\Employees.json", "r");
	
	char readBuffer[65536];
	FileReadStream is(stream, readBuffer, sizeof(readBuffer));

	Document document;
	document.ParseStream(is);
	

	const Value& array = document["Employee"];
	for (int i = 0; i < array.Size(); ++i) {
		test_vector[i].id = array[i]["Id"].GetString();
		test_vector[i].city = array[i]["City"].GetString();
		test_vector[i].name = array[i]["Name"].GetString();

		test_vector.push_back(employee());
	}

	print(test_vector);

	fclose(stream);
}


