#pragma once
#include <functional>
#include <iostream>
#include <istream>
#include <sstream>
#include <utility>

class Menu
{
public:
	typedef std::function<void(std::istream&)> Command;

	struct MenuItem
	{
		MenuItem(
			std::string shortcut,
			std::string description,
			Command command)
			: shortcut(std::move(shortcut))
			  , description(std::move(description))
			  , command(std::move(command))
		{
		}

		std::string shortcut;
		std::string description;
		Command command;
	};

	explicit Menu(std::istream& input, std::ostream& output, std::vector<MenuItem> items = {})
		: m_items(std::move(items))
		, m_input(input)
		, m_output(output)
	{
	}

	void AddItem(
		const std::string& shortcut,
		const std::string& description,
		const Command& command)
	{
		m_items.emplace_back(shortcut, description, command);
	}

	void Run()
	{
		ShowInstructions();

		std::string command;
		while (m_output << "> " && std::getline(m_input, command))
		{
			try
			{
				if (!ExecuteCommand(command))
				{
					break;
				}
			}
			catch (std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
		}
	}

	void Exit()
	{
		m_exit = true;
	}

	void ShowInstructions() const
	{
		m_output << "Commands list:" << std::endl;
		for (auto& item : m_items)
		{
			m_output << "  " << item.shortcut << ": " << item.description << std::endl;
		}
	}

private:
	bool ExecuteCommand(std::string const& command)
	{
		m_exit = false;
		std::string shortcut;
		std::istringstream commandStream(command);
		commandStream >> shortcut;
		const auto it = std::find_if(m_items.begin(), m_items.end(), [&](const MenuItem& item) {
			return item.shortcut == shortcut;
		});
		if (it != m_items.end())
		{
			it->command(commandStream);
		}
		else
		{
			m_output << "Unknown command" << std::endl;
		}

		return !m_exit;
	}

	std::vector<MenuItem> m_items;
	std::istream& m_input;
	std::ostream& m_output;
	bool m_exit = false;
};
