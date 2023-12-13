#include <random>

import random;

using ScribbleServer::Random;

char Random::GetRandomChar()
{
	return 0;
}
std::string Random::GetRandomCode(size_t size)
{
	return std::string();
}
std::string Random::GetRandomUniqueCode(const std::unordered_set<std::string>& codes)
{
	return std::string();
}
