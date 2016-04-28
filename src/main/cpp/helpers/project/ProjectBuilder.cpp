#include "ProjectBuilder.h"

Project* ProjectBuilder::getProjectFromJson(json::Object projectJson,
	json::Array runCommands)
{
	Project* project = ProjectBuilder::getProjectFromJson(projectJson);
	project->runCommands = ProjectBuilder::getCommandsFromJson(runCommands);
	return project;
}

//______________________PARSE_JSON
Module getModuleFromJson(json::Object moduleJson)
{
	Module module = Module();
	module.name = moduleJson["name"].ToString();
	module.active = moduleJson["active"].ToBool();
	module.absolute = moduleJson["absolute"].ToBool();
	json::Array lines = moduleJson["lines"].ToArray();
	module.linesSize = lines.size();
	module.lines = new std::string[lines.size()];
	for(int i = 0; i < lines.size(); i++)
	{
		module.lines[i] = lines[i].ToString();
	}
	return module;
}
Module* getModulesFromJson(json::Array modulesJson)
{
	Module* modules = new Module[modulesJson.size()];
	for(int i = 0; i < modulesJson.size(); i++)
	{
		modules[i] = getModuleFromJson(modulesJson[i]);
	}
	return modules;
}
Command getCommandModuleFromJsonOld(json::Object runCommandJson)
{
	CommandModule command = CommandModule(runCommandJson["name"].ToString(),
		runCommandJson["type"].ToInt());
	//
	json::Array pre = runCommandJson["pre"].ToArray();
	command.preSize = pre.size();
	command.pre = new std::string[pre.size()];
	for(int i = 0; i < pre.size(); i++)
	{
		command.pre[i] = pre[i].ToString();
	}
	//
	json::Array modulesJson = runCommandJson["modules"].ToArray();
	command.modulesSize = modulesJson.size();
	command.modules = getModulesFromJson(modulesJson);
	//
	json::Array post = runCommandJson["post"].ToArray();
	command.postSize = post.size();
	command.post = new std::string[post.size()];
	for(int i = 0; i < post.size(); i++)
	{
		command.post[i] = post[i].ToString();
	}
	//
	return command;
}
Command* getCommandModuleFromJson(json::Object runCommandJson)
{
	CommandModule *command = new CommandModule(runCommandJson["name"].ToString(),
		runCommandJson["type"].ToInt());
	//
	json::Array pre = runCommandJson["pre"].ToArray();
	command->preSize = pre.size();
	command->pre = new std::string[pre.size()];
	for(int i = 0; i < pre.size(); i++)
	{
		command->pre[i] = pre[i].ToString();
	}
	//
	json::Array modulesJson = runCommandJson["modules"].ToArray();
	command->modulesSize = modulesJson.size();
	command->modules = getModulesFromJson(modulesJson);
	//
	json::Array post = runCommandJson["post"].ToArray();
	command->postSize = post.size();
	command->post = new std::string[post.size()];
	for(int i = 0; i < post.size(); i++)
	{
		command->post[i] = post[i].ToString();
	}
	//
	return command;
}
Command* getCommandGroupFromJson(json::Object runCommandJson)
{
	CommandGroup* command = new CommandGroup(runCommandJson["name"].ToString(),
		runCommandJson["type"].ToInt());
	json::Array commands = runCommandJson["commands"].ToArray();
	command->commandsSize = commands.size();
	return command;
}
Command* getCommandFromJson(json::Object runCommandJson)
{
	if(runCommandJson["type"].ToInt() == TypesHelper::COMMAND_TYPE_GROUP)
	{
		return getCommandGroupFromJson(runCommandJson);
	}
	else
	{
		return getCommandModuleFromJson(runCommandJson);
	}
}
Project* ProjectBuilder::getProjectFromJson(json::Object projectJson)
{
	Project* project = new Project();
	project->projectSettings.name = projectJson["name"].ToString();
	project->projectSettings.rootDir = projectJson["rootDir"].ToString();
	project->projectSettings.type = projectJson["type"].ToInt();
	return project;
}
Command** ProjectBuilder::getCommandsFromJson(json::Array runCommandsJson)
{
	Command** runCommands = new Command*[runCommandsJson.size()];
	for(int i = 0; i < runCommandsJson.size(); i++)
	{
		runCommands[i] = getCommandFromJson(runCommandsJson[i]);
	}
	return runCommands;
}

//______________________BUILD_COMMANDS
std::string buildCommandModule(CommandModule* command, Project::settings projectSettings)
{
	std::string engage = "";
	//MODULES
	for(int i=0; i < command->modulesSize; i++)
	{
		if(!command->modules[i].active)
		{
			continue;
		}
		std::string prefix = "";
		if(!command->modules[i].absolute)
		{
			prefix = projectSettings.rootDir + "/";
		}
		for(int j=0; j < command->modules[i].linesSize; j++)
		{
			engage += " " + prefix + command->modules[i].lines[j];
		}
	}
	//EXECUTE_FILE_NAME
	if(projectSettings.type == TypesHelper::PROJECT_TYPE_CPP)
	{
		engage += " -o " + projectSettings.rootDir + "/" + projectSettings.name;
	}
	return engage;
}
std::string buildCommandCommandGroup(CommandGroup* command, Project::settings projectSettings)
{
	std::string engage = "";
	/*
	for(int i = 0; i < command->commandsSize; i++)
	{
		if(command->commands[i].type == TypesHelper::COMMAND_TYPE_GROUP)
		{
			engage += buildCommandCommandGroup((CommandModule)command->commands[i]) + "\n";
		}
		else
		{
			engage += buildCommandModule((CommandGroup)command->commands[i]) + "\n";
		}
	}
	*/
	return engage;
}
std::string ProjectBuilder::buildCommand(Command* command, Project::settings projectSettings)
{
	if(command->type == TypesHelper::COMMAND_TYPE_GROUP)
	{
		return buildCommandCommandGroup(((CommandGroup *)command), projectSettings);
	}
	else
	{
		return buildCommandModule(((CommandModule *)command), projectSettings);
	}
}