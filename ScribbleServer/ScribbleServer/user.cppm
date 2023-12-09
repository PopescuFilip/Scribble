module;
import <string>;

export module user;

namespace ScribbleServer
{
	export class User 
	{
	public:
		User();
		User(const std::string& username, const std::string& password);
		
		int GetUserId() const;
		std::string GetUsername() const;
		std::string GetPassword() const;

		void SetUserId(const int& userId);
		void SetUsername(const std::string& user);
		void SetPassword(const std::string& password);

		bool IsCorrectPass(const std::string& password);
	private:
		int m_userId;
		std::string m_username;
		std::string m_password;
	};
}