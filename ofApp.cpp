#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(0);
	ofSetWindowTitle("Insta");

	this->cap.open(1);

	this->frame_img.allocate(this->cap.get(CV_CAP_PROP_FRAME_WIDTH) * 0.25, this->cap.get(CV_CAP_PROP_FRAME_HEIGHT) * 0.25, OF_IMAGE_COLOR);
	this->frame = cv::Mat(this->frame_img.getHeight(), this->frame_img.getWidth(), CV_MAKETYPE(CV_8UC3, this->frame_img.getPixels().getNumChannels()), this->frame_img.getPixels().getData(), 0);

	cout << this->cap.get(CV_CAP_PROP_FRAME_WIDTH) << " : " << this->cap.get(CV_CAP_PROP_FRAME_HEIGHT) << endl;
}

//--------------------------------------------------------------
void ofApp::update() {

	if (!this->cap.isOpened()) { return; }

	cv::Mat src;
	this->cap >> src;
	if (src.empty()) { return; }

	cv::cvtColor(src, src, CV_RGB2BGR);
	cv::flip(src, src, 1);
	cv::resize(src, this->frame, cv::Size(), 0.25, 0.25);

	if (ofGetFrameNum() == 1) {
		this->frame.copyTo(this->save_frame);
	}

	if (ofGetFrameNum() > 2) {
		for (int y = 0; y < this->frame.rows; y += 1) {
			for (int x = 0; x < this->frame.cols; x += 1) {
				/*if (this->frame.at<cv::Vec3b>(y, x)[0] > 100 && this->frame.at<cv::Vec3b>(y, x)[0] < 255) &&
					this->frame.at<cv::Vec3b>(y, x)[1] > 0 && this->frame.at<cv::Vec3b>(y, x)[1] < 100 &&
					this->frame.at<cv::Vec3b>(y, x)[2] > 0 && this->frame.at<cv::Vec3b>(y, x)[2] < 100 ){ */
				if(this->frame.at<cv::Vec3b>(y, x)[0] + this->frame.at<cv::Vec3b>(y, x)[1] + this->frame.at<cv::Vec3b>(y, x)[2] > 172){
					this->frame.at<cv::Vec3b>(y, x) = this->save_frame.at<cv::Vec3b>(y, x);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	this->cam.begin();
	
	ofTranslate(-this->frame_img.getWidth() / 2, -this->frame_img.getHeight() / 2);

	this->frame_img.update();
	this->frame_img.draw(0, 0);

	this->cam.end();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's') {
		if (!this->cap.isOpened()) { return; }

		cv::Mat src;
		this->cap >> src;
		if (src.empty()) { return; }

		cv::cvtColor(src, src, CV_RGB2BGR);
		cv::flip(src, src, 1);
		cv::resize(src, this->frame, cv::Size(), 0.25, 0.25);

		this->frame.copyTo(this->save_frame);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	cout << "x = " << x << " y = " << y << endl;

	cout << "R = " << (int)this->frame.at<cv::Vec3b>(y, x)[0] << " G = " << (int)this->frame.at<cv::Vec3b>(y, x)[1] << " B = " << (int)this->frame.at<cv::Vec3b>(y, x)[2] << endl;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
