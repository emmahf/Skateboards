#include "config_manager.h"

bool ConfigManager::loadDefaultConfig(const char * fileName)
{
	// TODO - Check if the config file exists, call createDefaultConfig and return if not
	return true;
}

void ConfigManager::createDefaultConfig()
{
	// TODO - Create an empty config file in the correct folder if one does not exist already
}

void ConfigManager::addConfigSetting(const char *name, const char *value)
{
	ConfigSetting newConfigSetting;
	newConfigSetting.setName(name);
	newConfigSetting.setValue(value);

	m_configSettings.push_back(newConfigSetting);
}

void ConfigManager::debugAndTestCvars()
{
	// Get cvars as basic types
	int testInt = getSetting<int>("test_int");
	bool testBool = getSetting<bool>("test_bool");
	float testFloat = getSetting<float>("test_float");
	std::string testString = getSetting<std::string>("test_string");
}