#include "testApp.h"

#include "ofxSeExpr.h"

ofxSeExpr expr;

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	
	ofBackground(30);
	
	// returns last value as ofVec3f
	assert(expr.eval("42").x == 42);
	
	// variable is ok
	expr.set("test", 10);
	assert(expr.eval("$test * 100").x == 1000);
	
	// you can use some math function
	float phase = ofRandom(TWO_PI);
	expr.set("phase", phase);
	assert(fabs(expr.eval("sin($phase)").x - sin(phase)) < 0.001);
	
	// more functuons, see... http://wdas.github.com/SeExpr/doxygen/userdoc.html
	
	// or you can load some file,
	expr.load("test.se");
	
	// and exec script,
	cout << "script returns = " << expr.exec() << endl;
	
	// also you can get script local variables
	cout << "$my_val = " << expr.get("my_val") << endl;
	
	ofExit(0);
}

//--------------------------------------------------------------
void testApp::update()
{

}

//--------------------------------------------------------------
void testApp::draw()
{

}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}