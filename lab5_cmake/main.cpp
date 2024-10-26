

#include "document/Document.h"
#include "document/IDocument.h"
#include "menu/Menu.h"

#include <iostream>
#include <memory>

const Path STORAGE_DIR = "storage";

size_t GetPos(std::string const& str)
{
	if (str == "end")
	{
		return 0;
	}

	return std::stoull(str);
}

void AddCommands(Menu& menu, IDocumentPtr const& document)
{
	menu.AddItem("exit", "exit menu", [&](auto&) {
		menu.Exit();
	});

	menu.AddItem("help", "", [&](auto&) {
		menu.ShowInstructions();
	});

	menu.AddItem("InsertParagraph", "<position|end> <text>", [&](auto& input) {
		std::string pos;
		input >> pos;
		std::string text;
		std::getline(input, text);
		document->InsertParagraph(text, GetPos(pos));
	});

	menu.AddItem("InsertImage", "<position|end> <width> <height> <path>", [&](auto& input) {
		std::string pos;
		input >> pos;
		int width;
		input >> width;
		int height;
		input >> height;
		std::string path;
		input >> path;
		document->InsertImage(path, width, height, GetPos(pos));
	});

	menu.AddItem("SetTitle", "<title>", [&](auto& input) {
		std::string title;
		input >> title;
		document->SetTitle(title);
	});

	menu.AddItem("List", "", [&](auto&) {
		document->List();
	});

	menu.AddItem("ReplaceText", "<position> <text>", [&](auto& input) {
		std::string pos;
		input >> pos;
		std::string text;
		input >> text;
		if (auto p = document->GetItem(GetPos(pos)).GetParagraph())
		{
			p->SetText(text);
		}
		else
		{
			throw std::runtime_error("No paragraph found");
		}
	});

	menu.AddItem("ResizeImage", "<position> <width> <height>", [&](auto& input) {
		std::string pos;
		input >> pos;
		int width;
		input >> width;
		int height;
		input >> height;
		if (const auto img = document->GetItem(GetPos(pos)).GetImage())
		{
			img->Resize(width, height);
		}
		else
		{
			throw std::runtime_error("No image found");
		}
	});

	menu.AddItem("DeleteItem", "<position|end>", [&](auto& input) {
		std::string pos;
		input >> pos;
		document->DeleteItem(GetPos(pos));
	});

	menu.AddItem("Undo", "", [&](auto& input) {
		document->Undo();
	});

	menu.AddItem("Redo", "", [&](auto& input) {
		document->Redo();
	});

	menu.AddItem("Save", "<path>", [&](auto& input) {
		std::string path;
		input >> path;
		document->Save(path);
	});
}

// Исключения
// Нумерация
// Улучшить склеивания
int main()
{
	create_directory(STORAGE_DIR);
	const std::shared_ptr<IDocument> document = std::make_shared<Document>(STORAGE_DIR);
	Menu menu(std::cin, std::cout);
	AddCommands(menu, document);

	try
	{
		menu.Run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
