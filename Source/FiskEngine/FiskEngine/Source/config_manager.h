#pragma once
#include <vector>
#include <string>
#include <sstream>

class ConfigSetting
{
public:
	const char *getName() { return m_name; }
	const char *getValue() { return m_value; }

	void setName(const char *name) { m_name = name; }
	void setValue(const char *value) { m_value = value; }

private:
	const char *m_name;
	const char *m_value;
};

class ConfigManager
{
public:
	ConfigManager()
	{
		// TODO - Is this actually necessary to clear vectors when initialising?
		m_configSettings.clear();
	}

	// Returns true on successful load - Probably should error out or something if false
	bool loadDefaultConfig(const char *filename);

	void debugAndTestCvars();

	// If our local.cfg file is not found, create an empty default - Return false if it fails, probably should error out in that case
	void createDefaultConfig();
	void addConfigSetting(const char *name, const char *value);

	template <typename T>
	T getSetting(const char *command)
	{
		T returnValue;

		for (int i = 0; i < m_configSettings.size(); i++)
		{
			if (!strcmp(command, m_configSettings[i].getName()))
			{
				std::stringstream convertType(m_configSettings[i].getValue());
				convertType >> returnValue;

				return returnValue;
			}
				
		}

		return returnValue;
	}

private:
	std::vector<ConfigSetting> m_configSettings;
};