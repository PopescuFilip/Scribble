import user;

using ScribbleServer::User;

ScribbleServer::User::User():
	m_username{ "defaultUser" },
	m_password{ "12345678" }
{}

ScribbleServer::User::User(const std::string & username, const std::string & password):
	m_username{ username },
	m_password{password}
{}

std::string ScribbleServer::User::GetUser()
{
	return m_username;
}

bool ScribbleServer::User::IsCorrectPass(const std::string& password)
{
	return password == m_password;
}
