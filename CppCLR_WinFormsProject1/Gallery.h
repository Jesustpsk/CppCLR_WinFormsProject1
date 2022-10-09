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
		PicturePath = "";
		PictureModified = "";
	}
	Gallery(string PicName_value, string PicDes_value, string PicDate_value, string PicPath_value) {
		PictureName = PicName_value;
		PictureDescription = PicDes_value;
		PictureDate = PicDate_value;
		PicturePath = PicPath_value;
		PictureModified = "";
	}
	~Gallery() {

	}
	static vector <Gallery> vec_Gal;
	static vector <string> Changes;
	string time_now();
	void addImage(array <String^>^ images, ImageList ^, ListView ^);
	void ChangePictureName(int ind, ListView^);
	void ChangePictureDescription(int ind);
	void ChangePicture(int ind, ImageList^, ListView^);
	void DeletePicture(int ind, ImageList^, ListView^);
	void GetStats(int ind);
	void GetInfo();
	void Search_Num(ListView^);
	void Search_Desc(ListView^);
	void Search_Creation(ListView^);
	void Search_Modified(ListView^);
	void Search_Unfinished(ListView^);
	void ViewMode(ListView^, PictureBox^);

private:
	string PictureName;
	string PictureDescription;
	string PictureDate;
	string PicturePath;
	string PictureModified;
};