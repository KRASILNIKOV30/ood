#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include "CommandHandler.h"
#include "Picture.h"

using namespace std;

struct Args
{
	string svg;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		return nullopt;
	}
	Args args;
	args.svg = argv[1];
	return args;
}

bool OpenStreamsErrorHandling(ofstream& output)
{
	if (!output.is_open())
	{
		cout << "Failed to open file for writing\n";
		return false;
	}
	return true;
}

bool SaveErrorHandling(ofstream& output)
{
	if (!output.flush())
	{
		cout << "Failed to save data on disk\n";
		return false;
	}
	return true;
}

bool ProcessArgError(const optional<Args>& args)
{
	if (!args.has_value())
	{
		cout << "Invalid arguments count\n";
		cout << "Usage: shapes.exe <svg file>\n";
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);

	if (!ProcessArgError(args))
	{
		return 1;
	}

	ofstream svgFile(args->svg);

	if (!OpenStreamsErrorHandling(svgFile))
	{
		return 1;
	}

	Picture picture;
	CommandHandler commandHandler(cin, cout, picture, svgFile);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!commandHandler.HandleCommand())
		{
			cout << "Error!" << std::endl;
		}
	}

	if (!SaveErrorHandling(svgFile))
	{
		return 1;
	}

	return 0;
}
