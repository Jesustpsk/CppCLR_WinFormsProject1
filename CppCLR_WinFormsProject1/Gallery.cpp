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
			vec_Gal.push_back(Gallery(std_name, std_description, std_time));
				
			item->ImageIndex = imageList->Images->Count - 1;
			listViewImages->EndUpdate();
			listViewImages->LargeImageList = imageList;
			listViewImages->Refresh();
		}
	}
	I_GLOBAL = SIZE_GLOBAL;
	//vec_Gal.resize(SIZE_GLOBAL);
}

void Gallery::ChangePictureName()
{
    
}

void Gallery::ChangePictureDescription()
{
    throw gcnew System::NotImplementedException();
}

void Gallery::ShowPictureDate()
{
    throw gcnew System::NotImplementedException();
}

void Gallery::DeletePicture()
{
    throw gcnew System::NotImplementedException();
}

void Gallery::GetStats(int ind)
{
	String^ answ = "";
	String^ name = marshal_as<String^>(vec_Gal.at(ind).PictureName);
	String^ date = marshal_as<String^>(vec_Gal.at(ind).PictureDate);
	String^ description = marshal_as<String^>(vec_Gal.at(ind).PictureDescription);

	answ += "Name: " + name + "\nDate: " + date + "\nDescription: " + description;
	MessageBox::Show(answ, "Stats", MessageBoxButtons::OK, MessageBoxIcon::Information);
}


