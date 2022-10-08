#pragma once
#include "Form1.h"
#include <Windows.h>
#include "pch.h"
#include <vector>
#include <string>

using namespace CppCLRWinFormsProject;
using std::vector;
using std::string;

class Gallery {
public:
	Gallery() {
		PictureName = "";
		PictureDescription = "";
		PictureDate = "";
	}
	Gallery(string PicName_value, string PicDes_value, string PicDate_value) {
		PictureName = PicName_value;
		PictureDescription = PicDes_value;
		PictureDate = PicDate_value;
	}
	~Gallery() {

	}
	int SIZE_GLOBAL = 0;
	int I_GLOBAL = 0;
	vector <Gallery> vec_Gal;

	string time_now();
	void addImage(array <String^>^ images, ImageList ^, ListView ^);
	void ChangePictureName();
	void ChangePictureDescription();
	void ShowPictureDate();
	void DeletePicture();
	void GetStats(int ind);

private:
	string PictureName;
	string PictureDescription;
	string PictureDate;
};