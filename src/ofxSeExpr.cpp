#include "ofxSeExpr.h"

ofxSeExpr::ofxSeExpr() : auto_reload(false), has_error(false)
{
	reset();
}

void ofxSeExpr::set(const string& name, float value)
{
	vars[name] = Val(value);
}

void ofxSeExpr::set(const string& name, ofVec3f value)
{
	vars[name] = Val(value.x, value.y, value.z);
}

ofVec3f ofxSeExpr::get(const string& name)
{
	ofVec3f value(0, 0, 0);
	
	const LocalVarTable &t = getLocalVars();
	LocalVarTable::const_iterator it = t.find(name);
	if (it == t.end()) return value;
	const SeVec3d& val = it->second.val;
	
	value.x = val[0];
	value.y = val[1];
	value.z = val[2];
	return value;
}

ofVec3f ofxSeExpr::eval(const string& expr)
{
	setExpr(expr);
	if (!isValid())
	{
		return ofVec3f(0, 0, 0);
	}
	else
	{
		SeVec3d v = evaluate();
		return ofVec3f(v[0], v[1], v[2]);
	}
}

bool ofxSeExpr::load(string path, bool auto_reload)
{
	this->auto_reload = auto_reload;
	file = Poco::File(ofToDataPath(path));
	return reload();
}

bool ofxSeExpr::reload()
{
	Poco::Timestamp t = file.getLastModified();
	if (timestamp == t) return false;
	timestamp = t;
	
	has_error = false;
	
	setExpr(ofBufferFromFile(file.path()).getText());
	
	if (!syntaxOK())
	{
		has_error = true;
		ofLogError("ofxSeExpr", parseError().c_str());
		return false;
	}
	
	ofLogVerbose("ofxSeExpr", "reloaded");
	
	return true;
}

ofVec3f ofxSeExpr::exec()
{
	if (auto_reload) reload();
	if (has_error) return ofVec3f(0, 0, 0);
	
	SeVec3d v = evaluate();
	return ofVec3f(v[0], v[1], v[2]);
}

SeExprVarRef* ofxSeExpr::resolveVar(const std::string& name) const
{
    std::map<std::string, Val>::iterator it = vars.find(name);
    if(it != vars.end()) return &it->second;
    return NULL;
}