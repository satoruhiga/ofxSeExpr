#pragma once

#include "ofMain.h"

#include "SeExpression.h"
#include "Poco/File.h"

class ofxSeExpr : protected SeExpression
{
public:
	
	ofxSeExpr();

	// variable stuff
	void set(const string& name, float value);
	void set(const string& name, ofVec3f value);
	ofVec3f get(const string& name);
	
	// eval oneliner
	ofVec3f eval(const string& expr);
	
	// load script and execute
	bool load(string path, bool auto_reload = true);
	bool reload();
	ofVec3f exec();
	
	bool isValid() { return SeExpression::isValid(); }
	
protected:
	
	struct Val;
	mutable std::map<std::string, Val> vars;

	bool has_error;
	bool auto_reload;
	Poco::Timestamp timestamp;
	Poco::File file;

	SeExprVarRef* resolveVar(const std::string& name) const;
	
	struct Val : public SeExprVectorVarRef
    {
		union
		{
			float v[3];
			struct {
				float x, y, z;
			};
			
			float c[3];
			struct {
				float r, g, b;
			};
		};
		
		bool is_vec;

		inline Val() {}
        inline Val(const float x) : x(x), y(0), z(0), is_vec(false) {}
		inline Val(const float x, const float y) : x(x), y(y), z(0), is_vec(true) {}
		inline Val(const float x, const float y, const float z) : x(x), y(y), z(z), is_vec(true) {}
		
        inline void eval(const SeExprVarNode*, SeVec3d& result)
		{
			if (is_vec)
			{
				result[0] = x;
				result[1] = y;
				result[2] = z;
			}
			else
			{
				result = x;
			}
		}
		
		inline bool isVec()
		{
			return is_vec;
		}
    };

};
