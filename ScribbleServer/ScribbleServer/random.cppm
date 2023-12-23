module;
import <string>;
import <unordered_set>;

export module random;

namespace ScribbleServer
{
	export char GetRandomChar();
	export std::string GetRandomCode(size_t size = 4);
	export std::string GetRandomUniqueCode(const std::unordered_set<std::string>& codes);

};

