import user;

using ScribbleServer::User;

User::User():
	m_username{ "defaultUser" },
	m_password{ "12345678" }
{}

User::User(const std::string & username, const std::string & password):
	m_username{ username },
	m_password{password}
{}

std::string User::GetUser() const
{
	return m_username;
}

std::string User::GetPassword() const
{
	return m_password;
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
