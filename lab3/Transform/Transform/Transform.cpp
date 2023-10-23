#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

#include "CCompressiveOutputStream.h"
#include "CDecompressiveInputStream.h"
#include "CDecryptInputStream.h"
#include "CEncryptOutputStream.h"
#include "CFileInputStream.h"
#include "CFileOutputStream.h"
#include "IDataStreams.h"

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::vector<std::string> options;
};

std::optional<Args> ParseArgs(const int argc, char* argv[])
{
	if (argc < 3)
	{
		return std::nullopt;
	}
	Args args;
	for (int i = 1; i < argc; i++)
	{
		if (i == argc - 2)
		{
			args.inputFileName = argv[i];
		}
		else if (i == argc - 1)
		{
			args.outputFileName = argv[i];
		}
		else
		{
			args.options.emplace_back(argv[i]);
		}
	}

	return args;
}

bool HandleStreams(std::unique_ptr<IInputDataStream> const& input, std::unique_ptr<IOutputDataStream>& output)
{
	while (!input->IsEOF())
	{
		output->WriteByte(input->ReadByte());
 	}

	return true;
}

bool SaveErrorHandling(std::unique_ptr<IOutputDataStream> const& output)
{
	if (!output->Flush())
	{
		std::cout << "Failed to save data on disk\n";
		return false;
	}
	return true;
}

bool ProcessArgError(const std::optional<Args>& args)
{
	if (!args.has_value())
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: transform.exe [options] <input file> <output file>\n";
		return false;
	}
	return true;
}

std::unique_ptr<IInputDataStream> MakeInputStream(std::string const& filename, std::vector<std::string> const& options)
{
	std::unique_ptr<IInputDataStream> strm = std::make_unique<CFileInputStream>(filename);
	for (auto it = options.rbegin(); it != options.rend(); ++it)
	{
		if (*it == "--decrypt")
		{
			strm = std::make_unique<CDecryptInputStream>(std::move(strm), std::stoi(*(it - 1)));
		}
		else if (*it == "--decompress")
		{
			strm = std::make_unique<CDecompressiveInputStream>(std::move(strm));
		}
	}

	return strm;
}

std::unique_ptr<IOutputDataStream> MakeOutputStream(std::string const& filename, std::vector<std::string> const& options)
{
	std::unique_ptr<IOutputDataStream> strm = std::make_unique<CFileOutputStream>(filename);
	for (size_t i = 0; i < options.size(); i++)
	{
		if (options[i] == "--encrypt")
		{
			strm = std::make_unique<CEncryptOutputStream>(std::move(strm), stoi(options[i + 1]));
		}
		else if (options[i] == "--compress")
		{
			strm = std::make_unique<CCompressiveOutputStream>(std::move(strm));
		}
	}

	return strm;
}

int main(const int argc, char* argv[])
{
	const auto args = ParseArgs(argc, argv);

	if (!ProcessArgError(args))
	{
		return 1;
	}

	const auto input = MakeInputStream(args->inputFileName, args->options);
	auto output = MakeOutputStream(args->outputFileName, args->options);

	if (!HandleStreams(input, output))
	{
		return 1;
	}

	if (!SaveErrorHandling(output))
	{
		return 1;
	}

	return 0;
}
