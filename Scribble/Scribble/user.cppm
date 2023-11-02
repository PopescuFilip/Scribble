module;
export module user;

import <string>;

namespace Scribble
{
	export class User 
	{
	public:
		User();
		User(const std::string& username, const std::string& password);
		std::string GetUser();
		bool IsCorrectPass(const std::string& password);
	private:
		std::string m_username;
		std::string m_password;
	};
}