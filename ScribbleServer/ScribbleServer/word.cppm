
module;
export module word;

import <string>;
import <unordered_set>;


export class Word
{
public:
	Word();
	Word(const std::string& word);

	int GetWordId() const;
	std::string GetWord() const;

	void SetWordId(int wordId);
	void SetWord(const std::string& word);

	size_t GetWordSize() const;
	std::string GetVisibleCharacters() const;
	std::string GetEmptyWord() const;
	uint16_t GetNoOfCharacters() const;

	void RevealRandomCharacter();
	bool IsRevealed() const;

	bool operator ==(const std::string& word) const;

private:
	int m_wordId;
	std::string m_word;

	std::unordered_set<int> m_revealedCharacters;

};

