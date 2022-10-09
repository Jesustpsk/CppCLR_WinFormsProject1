#include "pch.h"
#include "Gallery.h"
#include "Form1.h"
#include <Windows.h>
#include <time.h>
#include <vector>
#include <string>
#include <msclr/marshal_cppstd.h>

using std::vector;
using std::string;
using namespace msclr::interop;
using namespace CppCLRWinFormsProject;
vector <Gallery> Gallery::vec_Gal;

string Gallery::time_now(){
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}

void Gallery::addImage(array<String^>^ images, ImageList^ imageList, ListView ^listViewImages)
{
	Gallery Gal;
	string std_time = time_now();

	int size = images->Length;
	SIZE_GLOBAL += images->Length;

	for (int i = I_GLOBAL; i < SIZE_GLOBAL; i++) {
		
		if (images[i] != "")
		{
			imageList->Images->Add(Image::FromFile(images[i]));
			listViewImages->BeginUpdate();
			ListViewItem^ item = listViewImages->Items->Add(gcnew ListViewItem("Picture " + Convert::ToString(imageList->Images->Count), imageList->Images->Count - 1));
			
			String^ description = Microsoft::VisualBasic::Interaction::InputBox("¬ведите комментарий к фото:", "", "", 100, 100);
			string std_name = marshal_as<string>("Picture " + Convert::ToString(imageList->Images->Count));
			string std_description = marshal_as<string>(description);
			String^ path = images[i];
			string std_path = marshal_as<string>(path);
			Gal.vec_Gal.push_back(Gallery(std_name, std_description, std_time, std_path));
				
			item->ImageIndex = imageList->Images->Count - 1;
			listViewImages->EndUpdate();
			listViewImages->LargeImageList = imageList;
			listViewImages->Refresh();
		}
	}
	I_GLOBAL = SIZE_GLOBAL;
}

void Gallery::ChangePictureName(int ind)
{
	Gallery Gal;
	String^ NewName = Microsoft::VisualBasic::Interaction::InputBox("¬ведите новое им€ фото:", "New Name", "", 100, 100);
	string NName = marshal_as<string>(NewName);
	Gal.vec_Gal.at(ind).PictureName = NName;
}

void Gallery::ChangePictureDescription(int ind)
{
	Gallery Gal;
	String^ NewDescription = Microsoft::VisualBasic::Interaction::InputBox("¬ведите новое описание фото:", "New Description", "", 100, 100);
	string NDesc = marshal_as<string>(NewDescription);
	Gal.vec_Gal.at(ind).PictureDescription = NDesc;
}

void Gallery::ChangePicture(int ind, ImageList^ imageList, ListView^ listViewImages)
{
	
}

void Gallery::DeletePicture(int ind, ImageList^ imageList, ListView^ listViewImages)
{
	Gallery Gal;

	ImageList^ IList = gcnew ImageList();
	IList->ColorDepth = ColorDepth::Depth32Bit;
	ListView^ LView = gcnew ListView();
	for (int i = 0; i < imageList->Images->Count; i++) {
		if (i != ind) {
			string path = Gal.vec_Gal[i].PicturePath;
			Image^ img = Image::FromFile(marshal_as<String^>(path));
			IList->Images->Add(img);
		}
	}
	Gal.vec_Gal.erase(vec_Gal.begin() + ind);
	SIZE_GLOBAL--;
	I_GLOBAL--;

	imageList->Images->Clear();
	for (int i = 0; i < IList->Images->Count; i++) {
		string path = Gal.vec_Gal[i].PicturePath;
		Image^ img = Image::FromFile(marshal_as<String^>(path));
		imageList->Images->Add(img);
	}

	listViewImages->BeginUpdate();
	listViewImages->Items->Clear();
	for (int i = 0; i < imageList->Images->Count; i++) {
		ListViewItem^ item = listViewImages->Items->Add(gcnew ListViewItem(marshal_as<String^>(Gal.vec_Gal[i].PictureName), i));
		item->ImageIndex = i;
	}
	listViewImages->EndUpdate();
	listViewImages->Refresh();
}

void Gallery::GetStats(int ind)
{
	Gallery Gal;
	String^ answ = "";
	String^ name = marshal_as<String^>(Gal.vec_Gal.at(ind).PictureName);
	String^ date = marshal_as<String^>(Gal.vec_Gal.at(ind).PictureDate);
	String^ description = marshal_as<String^>(Gal.vec_Gal.at(ind).PictureDescription);
	String^ path = marshal_as<String^>(Gal.vec_Gal.at(ind).PicturePath);

	answ += "Name: " + name + "\nDate: " + date + "\nDescription: " + description + "\nPath: " + path;
	MessageBox::Show(answ, "Stats", MessageBoxButtons::OK, MessageBoxIcon::Information);
}


