#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {

    ofGLFWWindowSettings settings;
    settings.setSize(640, 360);
    settings.numSamples = 0;
    auto window = ofCreateWindow(settings);
    auto app = make_shared<ofApp>();
    ofRunApp(window, app);
    ofRunMainLoop();
}
