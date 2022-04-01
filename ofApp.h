/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "sj_common.h"

/************************************************************
************************************************************/
/**************************************************
**************************************************/
class CAL__A_FILTER{
private:
	const double fr = 1000;			// Hz
	const double fL = pow(10, 1.5);	// Hz
	const double fH = pow(10, 3.9);	// Hz
	const double D = sqrt(0.5);
	const double fA = pow(10, 2.45);	// Hz
	
	const double b = 1.0 / (1.0 - D) * (fr*fr + (fL*fL * fH*fH)/(fr*fr) - D * (fL*fL + fH*fH));
	const double c = fL * fL * fH * fH;
	
	const double f1 = sqrt( (-b - sqrt(b*b - 4*c))/2 );
	const double f4 = sqrt( (-b + sqrt(b*b - 4*c))/2 );
	const double f2 = (3 - sqrt(5))/2 * fA;
	const double f3 = (3 + sqrt(5))/2 * fA;
	
	double A_ofs = cal_Basic(1000);
	
	double cal_Basic(double f){
		return 20 * log10( (f4*f4 * f*f*f*f) / ( (f*f + f1*f1) * sqrt(f*f + f2*f2) * sqrt(f*f + f3*f3) * (f*f + f4*f4)  ) );
	}
	
public:
	CAL__A_FILTER()	{}
	~CAL__A_FILTER(){}
	
	void print_param(){
		printf("fr = %f\n", fr);
		printf("fL = %f\n", fL);
		printf("fH = %f\n", fH);
		printf("D  = %f\n", D);
		printf("fA = %f\n", fA);
		printf("b  = %f\n", b);
		printf("c  = %f\n", c);
		printf("f1 = %f\n", f1);
		printf("f2 = %f\n", f2);
		printf("f3 = %f\n", f3);
		printf("f4 = %f\n", f4);
	}
	
	void set__Zero_dB_at_Hz(double val) { A_ofs = cal_Basic(val); }
	
	double get_dB(double f){
		return cal_Basic(f) - A_ofs;
	}
	
	double get_X(double f){
		double dB = cal_Basic(f) - A_ofs;
		return pow(10, dB/20);
	}
};

/**************************************************
**************************************************/
class ofApp : public ofBaseApp{
private:
	/****************************************
	****************************************/
	vector <double> A_Filter;
	CAL__A_FILTER Cal__A_Filter;
	
	bool b_save = false;
	
	/****************************************
	****************************************/
	void setup_Gui();
	void set__A_Filter();
	void Log__A_Filter();
	
public:
	/****************************************
	****************************************/
	ofApp();
	~ofApp();
	void exit();
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
		
};
