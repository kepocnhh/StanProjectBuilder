#include "json/json.h"
#include "../../core/project/Project.h"

class ProjectBuilder
{
private:
    static Project* getProjectFromJson(json::Object projectJson);
    static Run* getRunFromJson(json::Object runJson);
    static Build* getBuildFromJson(json::Object buildJson);
	static Build* getMainlineFromJson(Build* build, json::Object mainlineJson);
	static Module* getModulesFromJson(json::Array modulesJson);
	static Module getModuleFromJson(json::Object moduleJson);
public:
    static Project* getProjectFromJson(json::Object projectJson, json::Object buildJson, json::Object runJson);
	static std::string buildProject(Project*);
	static std::string runProject(Project*);

protected:
};