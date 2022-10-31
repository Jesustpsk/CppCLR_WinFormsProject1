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
		PictureModified = "None.";
	}
	~Gallery() {

	}
	static vector <Gallery> vec_Gal;
	static vector <string> Changes;
	static int PicView_ind;
	static int PicView_mode;
	static double min_x;
	static double min_y;
	static double max_x;
	static double max_y;
	static string Gal_path;
	static string Changes_path;

	string time_now();

	void addImage(array <String^>^ images, ImageList ^, ListView ^);

	void ChangePictureName(int ind, ListView^);
	void ChangePictureDescription(int ind);
	void ChangePicture(int ind, ImageList^, ListView^);
	void DeletePicture(int ind, ImageList^, ListView^);

	void GetStats(int ind);
	void GetInfo();
	string GetPath(int);

	void Search(ListView^, String^, PictureBox^);
	void SearchPatterns();

	void AutoSave();
	void AutoLoad(ImageList^, ListView^);
	void DeleteData(ImageList^, ListView^, PictureBox^);
private:
	string PictureName;
	string PictureDescription;
	string PictureDate;
	string PicturePath;
	string PictureModified;
};

class Image_ : public Gallery {
public:
	Image_(){}
	~Image_(){}

	void ImgResize(Image^, PictureBox^, Form1^);
	void ImgResize(Image^, PictureBox^);

	void ViewMode(ListView^, PictureBox^, Form1^);
	void ChangeMode(ListView^, PictureBox^, Form1^, array<Button^>^, PictureBox^, PictureBox^, Label^, TextBox^);

	void GoToFirst(ListView^, PictureBox^, Form1^);
	void GoToLast(ListView^, PictureBox^, Form1^);
	void Prev_Img(ListView^, PictureBox^, Form1^);
	void Next_Img(ListView^, PictureBox^, Form1^);
	void Img_minus(ListView^, PictureBox^);
	void Img_plus(ListView^, PictureBox^);

	void Rotate_Img(ListView^, PictureBox^, Form1^);
	void Flip_Img(ListView^, PictureBox^);
};