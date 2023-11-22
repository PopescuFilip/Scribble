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

std::string User::GetUser()
{
	return m_username;
}

bool User::IsCorrectPass(const std::string& password)
{
	return password == m_password;
}
