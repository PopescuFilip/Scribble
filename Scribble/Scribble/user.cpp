import user;

using Scribble::User;

Scribble::User::User():
	m_username{ "defaultUser" },
	m_password{ "12345678" }
{}

Scribble::User::User(const std::string & username, const std::string & password):
	m_username{ username },
	m_password{password}
{}

std::string Scribble::User::GetUser()
{
	return m_username;
}

bool Scribble::User::IsCorrectPass(const std::string& password)
{
	return password == m_password;
}
