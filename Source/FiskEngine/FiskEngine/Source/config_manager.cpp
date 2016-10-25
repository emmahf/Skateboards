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