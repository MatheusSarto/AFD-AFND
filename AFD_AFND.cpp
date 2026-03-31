#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstring>
class AFD
{
public:
	AFD(std::unordered_map<char, std::vector<char>> automataTransitions, char finishToken = '\0')
	{
		m_AutomataTransitions = automataTransitions;
	};
	void inline SetFinishToken(char finishToken)
	{
		m_FinishToken = finishToken;
	}
	bool validateAutomata(const char* stateSequence)
	{
		bool automataResult = Accepts(stateSequence);
		m_CurrentState = '\0';
		return automataResult;
	};
private:
	// Key: entry , Value: vector of possible next states
	std::unordered_map<char, std::vector<char>> m_AutomataTransitions;
	char m_CurrentState = '\0';
	char m_FinishToken = '\0';

private:
	bool IsSymbolValid(char currentState, char symbol)
	{
		char currentSymbol = std::toupper(symbol);
		if (m_FinishToken != '\0' && currentSymbol == std::toupper(m_FinishToken))
		{
			std::cout << "Finished on state: '" << currentState << "' by finishToken";
			return true;
		}
		auto validTransitions = m_AutomataTransitions.find(currentState);
		if (validTransitions == m_AutomataTransitions.end())
		{
			std::cout << "Invalid state: " << currentState;
			return false;
		}
		size_t validTransitionsSize = validTransitions->second.size();
		for (int j = 0; j < validTransitionsSize; j++)
		{
			if (std::toupper(validTransitions->second[j]) == currentSymbol)
			{
				m_CurrentState = validTransitions->second[j];
				return true;
			}
		}
		std::cout << "Symbol not mapped: " << currentSymbol;
		return false;
	};

	bool Accepts(const char* stateSequence)
	{
		size_t currentArraySize = strlen(stateSequence);
		if (currentArraySize == 0)
		{
			return false;
		}

		for (int i = 0; i < currentArraySize; i++)
		{
			char entrySymbol = std::toupper(stateSequence[i]);

			if (!IsSymbolValid(m_CurrentState, entrySymbol))
			{
				return false;
			}
		}

		return true;
	};
};

int main()
{
	std::cout << "Starting program..." << std::endl;
	std::cout << "Creating automata rules..." << std::endl;

	std::unordered_map<char, std::vector<char>> atomataTransitions;

	atomataTransitions.insert({ '\0', {'T','E','V','F','P','G','A','K','D'} });   // 0 - Inicial
	atomataTransitions.insert({ 'T', {'T','E','V','F','P','G','A','K','D'} });   // T - Terra
	atomataTransitions.insert({ 'E', {'T','E','V','F','P','G','K','D'} });       // E - Eletrico
	atomataTransitions.insert({ 'V', {'D'} });                                   // V - Voador
	atomataTransitions.insert({ 'F', {'T','E','V','F','G','A','K','D'} });       // F - Fantasma
	atomataTransitions.insert({ 'P', {'T','E','V','F','P','G','A','K','D'} });   // P - Psiquico
	atomataTransitions.insert({ 'G', {'T','E','V','F','P','G','A','K','D'} });   // G - Grama
	atomataTransitions.insert({ 'A', {'T','V','F','P','G','A','K','D'} });       // A - Agua
	atomataTransitions.insert({ 'K', {'V', 'D'} });                              // F - Fogo
	atomataTransitions.insert({ 'D', {'T','E','V','F','P','G','A','K','D'} });    // D - Dragao

	const char* sequence = "TEFzGD";
	std::cout << "Automata rules created!" << std::endl;
	std::cout << "Creating automata..." << std::endl;

	AFD automata = AFD(atomataTransitions);
	automata.SetFinishToken('z');

	std::cout << std::endl << "Automata created!" << std::endl;
	std::cout << std::endl << "Starting process of inputs '" << sequence << "' " << std::endl;

	bool isPossible = automata.validateAutomata(sequence);
	std::cout << std::endl << "Automata process result: " << isPossible << std::endl;
}