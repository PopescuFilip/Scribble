import user;

using ScribbleServer::User;

User::User():
	m_userId{ -1 },
	m_username{ "defaultUser" },
	m_password{ "12345678" }
{}

User::User(const std::string& username, const std::string& password) :
	m_userId{ -1 },
	m_username{ username },
	m_password{ password }
{}


int User::GetUserId() const
{
	return m_userId;
}

std::string User::GetUsername() const
{
	return m_username;
}

std::string User::GetPassword() const
{
	return m_password;
}

void User::SetUserId(const int& userId)
{
	m_userId = userId;
}

void User::SetUsername(const std::string& user)
{
	m_username = user;
}

void User::SetPassword(const std::string& password)
{
	m_password = password;
}

bool User::IsCorrectPass(const std::string& password)
{
	return password == m_password;
}
