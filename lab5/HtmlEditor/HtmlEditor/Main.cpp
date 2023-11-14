#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include "CMenu.h"
#include "CDocument.h"


//Исправить сохранение в папку html2
int main()
{
	std::shared_ptr<IDocument> document = std::make_shared<CDocument>();
	CMenu menu(std::cin, std::cout, document);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		menu.HandleCommand();
	}

	return 0;
}
