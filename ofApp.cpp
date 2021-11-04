#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(290);
	
	auto small_radius = 0.f; 
	for (auto radius = 50; radius <= 360; radius += small_radius * 2) {

		auto deg_span = 10;
		small_radius = (radius * 2 * PI) / 360 * deg_span * 0.5;
		auto size = (small_radius * 2) / sqrt(3);
		auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
		auto deg_start = ofGetFrameNum();

		for (int deg = deg_start; deg < deg_start + 360; deg += deg_span) {

			auto location = glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0);

			auto rotate_x = ofMap(ofNoise(glm::vec4(noise_seed.x, location * 0.0015)), 0, 1, -360, 360);
			auto rotate_y = ofMap(ofNoise(glm::vec4(noise_seed.y, location * 0.0015)), 0, 1, -360, 360);
			auto rotate_z = ofMap(ofNoise(glm::vec4(noise_seed.z, location * 0.0015)), 0, 1, -360, 360);

			ofPushMatrix();
			ofTranslate(location);

			ofRotateZ(rotate_z);
			ofRotateY(rotate_y);
			ofRotateX(rotate_x);

			ofFill();
			ofSetColor(0);
			ofDrawBox(size);

			ofNoFill();
			ofSetColor(255);
			ofDrawBox(size);

			ofPopMatrix();
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
