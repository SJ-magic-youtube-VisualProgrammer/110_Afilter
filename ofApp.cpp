/************************************************************
************************************************************/
#include "ofApp.h"

/************************************************************
************************************************************/

/******************************
******************************/
ofApp::ofApp(){
}

/******************************
******************************/
ofApp::~ofApp(){
}
/******************************
******************************/
void ofApp::exit(){
}

/******************************
******************************/
void ofApp::setup(){
	/********************
	********************/
	ofSetBackgroundAuto(true);
	
	ofSetWindowTitle("fft:Visualize");
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	ofSetWindowShape(MAIN_WINDOW_W, MAIN_WINDOW_H);
	ofSetEscapeQuitsApp(false);
	
	/********************
	********************/
	fp_Log = fopen("../../../data/Log.csv", "w");
	setup_Gui();

	/********************
	********************/
	A_Filter.assign(AUDIO_BUF_SIZE/2, 0.0);
	Cal__A_Filter.print_param();
}

/******************************
description
	memoryを確保は、app start後にしないと、
	segmentation faultになってしまった。
******************************/
void ofApp::setup_Gui()
{
	/********************
	********************/
	Gui_Global = new GUI_GLOBAL;
	Gui_Global->setup("param", "gui.xml", 10, 10);
}

/******************************
******************************/
void ofApp::set__A_Filter(){
	double Base_Freq = double(AUDIO_SAMPLERATE) / AUDIO_BUF_SIZE;
	
	A_Filter[0] = 0;
	for(int i = 1; i < A_Filter.size(); i++){
		// A_Filter[i] = Cal__A_Filter.get_dB(Base_Freq * i);
		A_Filter[i] = Cal__A_Filter.get_X(Base_Freq * i);
	}
}

/******************************
******************************/
void ofApp::Log__A_Filter(){
	FILE* fp = fopen("../../../data/A_Filter.csv", "w");
	if(fp){
		double Base_Freq = double(AUDIO_SAMPLERATE) / AUDIO_BUF_SIZE;
		
		for(int i = 1; i < A_Filter.size(); i++){
			fprintf(fp, "%d,%f,%f\n", i, Base_Freq * i, A_Filter[i]);
		}
		
		fclose(fp);
	}
}

/******************************
******************************/
void ofApp::update(){
	/********************
	********************/
	// int t_from = ofGetElapsedTimeMillis();
	int t_from = ofGetElapsedTimeMicros();
	
	/********************
	********************/
	Cal__A_Filter.set__Zero_dB_at_Hz(Gui_Global->A_Filter__Zero_dB_at_Hz);
	set__A_Filter();
	
	/********************
	********************/
	if(b_save){
		b_save = false;
		
		Log__A_Filter();
		printf("update time = %.2f[ms]\n", (float)(ofGetElapsedTimeMicros() - t_from) / 1000);
	}
}

/******************************
******************************/
void ofApp::draw(){
	ofBackground(200);
	
	Gui_Global->gui.draw();
}

/******************************
******************************/
void ofApp::keyPressed(int key){
	switch(key){
		case ' ':
			b_save = true;
			break;
	}
}

/******************************
******************************/
void ofApp::keyReleased(int key){

}

/******************************
******************************/
void ofApp::mouseMoved(int x, int y ){

}

/******************************
******************************/
void ofApp::mouseDragged(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mousePressed(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseReleased(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseEntered(int x, int y){

}

/******************************
******************************/
void ofApp::mouseExited(int x, int y){

}

/******************************
******************************/
void ofApp::windowResized(int w, int h){

}

/******************************
******************************/
void ofApp::gotMessage(ofMessage msg){

}

/******************************
******************************/
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
