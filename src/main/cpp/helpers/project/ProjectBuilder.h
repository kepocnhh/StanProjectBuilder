#include <stdio.h>
#include <fstream>
#include "json/json.h"
#include "../../core/project/Module.h"
#include "../../core/project/command/CommandGroup.h"
#include "../../core/project/command/CommandModule.h"
#include "../../core/project/Project.h"
#include "../../helpers/project/TypesHelper.h"

class ProjectBuilder
{
private:
    static Project* getProjectFromJson(json::Object projectJson);
	static Command** getCommandsFromJson(json::Array runCommandsJson);
	
public:
    static Project* getProjectFromJson(json::Object projectJson, json::Array runCommands);
	static std::string buildCommand(Command* command, Project::settings projectSettings);

protected:
};