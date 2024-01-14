import random;
#include <random>;

char GetRandomChar()
{
    const std::string charset = "0123456789";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, charset.size() - 1);
    return charset[distr(gen)];
}

std::string GetRandomCode(size_t size)
{
    std::string code;
    for (int i = 0; i < size; i++)
    {
        code += std::move(GetRandomChar());
    }
    return code;
}

std::string GetRandomUniqueCode(const std::unordered_set<std::string>& codes)
{
    std::string code;
    bool isUnique = false;

    while (!isUnique)
    {
        code = std::move(GetRandomCode(4));

        if (std::find(codes.begin(), codes.end(), code) == codes.end())
        {
            isUnique = true;
        }
    }

    return code;
}
