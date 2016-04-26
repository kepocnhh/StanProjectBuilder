#include "ProjectBuilder.h"

Project* ProjectBuilder::getProjectFromJson(json::Object projectJson, json::Object buildJson)
{
	Project* project = ProjectBuilder::getProjectFromJson(projectJson);
	project->build = ProjectBuilder::getBuildFromJson(buildJson);
	return project;
}

std::string ProjectBuilder::buildProject(Project* project)
{
	std::string engage = project->build->mainline.compile;
	//MODULES
	for(int i=0; i < project->build->mainline.modulesSize; i++)
	{
		if(!project->build->mainline.modules[i].active)
		{
			continue;
		}
		std::string prefix = "";
		if(!project->build->mainline.modules[i].absolute)
		{
			prefix = project->projectSettings.rootDir + "/";
		}
		for(int j=0; j < project->build->mainline.modules[i].linesSize; j++)
		{
			engage += " " + prefix + project->build->mainline.modules[i].lines[j];
		}
	}
	//EXECUTE_FILE_NAME
	engage += " -o " + project->projectSettings.name;
	//FLAGS
	for(int i=0; i < project->build->mainline.flagsSize; i++)
	{
		engage += " " + project->build->mainline.flags[i];
	}
	//LIBS
	for(int i=0; i < project->build->mainline.libsSize; i++)
	{
		engage += " " + project->build->mainline.libs[i];
	}
	return engage;
}

Project* ProjectBuilder::getProjectFromJson(json::Object projectJson)
{
	Project* project = new Project();
	project->projectSettings.name = projectJson["name"].ToString();
	project->projectSettings.rootDir = projectJson["rootDir"].ToString();
	project->projectSettings.type = projectJson["type"].ToString();
	return project;
}
Build* ProjectBuilder::getBuildFromJson(json::Object buildJson)
{
	Build* build = new Build();
	//
	json::Array pre = buildJson["pre"].ToArray();
	build->preSize = pre.size();
	build->pre = new std::string[pre.size()];
	for(int i = 0; i < pre.size(); i++)
	{
		build->pre[i] = pre[i].ToString();
	}
	//
	json::Object mainlineJson = buildJson["mainline"].ToObject();
	ProjectBuilder::getMainlineFromJson(build, mainlineJson);
	//
	json::Array post = buildJson["post"].ToArray();
	build->postSize = post.size();
	build->post = new std::string[post.size()];
	for(int i = 0; i < post.size(); i++)
	{
		build->post[i] = post[i].ToString();
	}
	return build;
}
Build* ProjectBuilder::getMainlineFromJson(Build* build, json::Object mainlineJson)
{
	build->mainline.compile = mainlineJson["compile"].ToString();
	//
	json::Array flags = mainlineJson["flags"].ToArray();
	build->mainline.flagsSize = flags.size();
	build->mainline.flags = new std::string[flags.size()];
	for(int i = 0; i < flags.size(); i++)
	{
		build->mainline.flags[i] = flags[i].ToString();
	}
	//
	json::Array modulesJson = mainlineJson["modules"].ToArray();
	build->mainline.modulesSize = modulesJson.size();
	build->mainline.modules = ProjectBuilder::getModulesFromJson(modulesJson);
	//
	json::Array libs = mainlineJson["libs"].ToArray();
	build->mainline.libsSize = libs.size();
	build->mainline.libs = new std::string[libs.size()];
	for(int i = 0; i < libs.size(); i++)
	{
		build->mainline.libs[i] = libs[i].ToString();
	}
	return build;
}
Module* ProjectBuilder::getModulesFromJson(json::Array modulesJson)
{
	Module* modules = new Module[modulesJson.size()];
	for(int i = 0; i < modulesJson.size(); i++)
	{
		modules[i] = ProjectBuilder::getModuleFromJson(modulesJson[i]);
	}
	return modules;
}
Module ProjectBuilder::getModuleFromJson(json::Object moduleJson)
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