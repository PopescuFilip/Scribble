module;
#include<iostream>
#include<string>
#include<unordered_set>
#include <random>

export module random;

namespace ScribbleServer
{
	export class Random
	{
	public:
		char GetRandomChar();
		std::string GetRandomCode(size_t size = 4);
		std::string GetRandomUniqueCode(const std::unordered_set<std::string>& codes);

	private:

	};
};

