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
vector <string> Gallery::Changes;
int Gallery::PicView_ind = 0;

string Gallery::time_now(){
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

	return buf;
}

void Gallery::addImage(array<String^>^ images, ImageList^ imageList, ListView ^listViewImages)
{
	Gallery Gal;
	

	int size = images->Length;

	for (int i = 0; i < size; i++) {
		string std_time = time_now();
		if (images[i] != "")
		{
			imageList->Images->Add(Image::FromFile(images[i]));
			listViewImages->BeginUpdate();
			ListViewItem^ item = listViewImages->Items->Add(gcnew ListViewItem("Picture " + Convert::ToString(imageList->Images->Count), imageList->Images->Count - 1));
			
			String^ description = Microsoft::VisualBasic::Interaction::InputBox("Введите комментарий к фото:", "Input description", "", 100, 100);
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
}

void Gallery::ChangePictureName(int ind, ListView^ listViewImages)
{
	Gallery Gal;
	String^ NewName = Microsoft::VisualBasic::Interaction::InputBox("Введите новое имя фото:", "New Name", "", 100, 100);
	string NName = marshal_as<string>(NewName);
	Gal.vec_Gal.at(ind).PictureName = NName;
	listViewImages->Items[ind]->Text = NewName;
	string time = time_now();
	Gal.Changes.push_back(time);
	Gal.vec_Gal.at(ind).PictureModified = time;
}

void Gallery::ChangePictureDescription(int ind)
{
	Gallery Gal;
	String^ NewDescription = Microsoft::VisualBasic::Interaction::InputBox("Введите новое описание фото:", "New Description", "", 100, 100);
	string NDesc = marshal_as<string>(NewDescription);
	Gal.vec_Gal.at(ind).PictureDescription = NDesc;
	string time = time_now();
	Gal.Changes.push_back(time);
	Gal.vec_Gal.at(ind).PictureModified = time;
}

void Gallery::ChangePicture(int ind, ImageList^ imageList, ListView^ listViewImages)
{
	Gallery Gal;

	ImageList^ IList = gcnew ImageList();
	IList->ColorDepth = ColorDepth::Depth32Bit;

	OpenFileDialog^ ofd = gcnew OpenFileDialog();
	ofd->Filter = "Image Files(*.JPG; *.PNG) |*.JPG; *.PNG|All files (*.*)|*.*";
	ofd->FilterIndex = 2;
	ofd->RestoreDirectory = true;

	if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		for (int i = 0; i < imageList->Images->Count; i++) {
			if (i != ind) {
				string path = Gal.vec_Gal.at(i).PicturePath;
				Image^ img = Image::FromFile(marshal_as<String^>(path));
				IList->Images->Add(img);
			}
			else {
				Image^ img = Image::FromFile(ofd->FileName);
				IList->Images->Add(img);
				Gal.vec_Gal.at(i).PicturePath = marshal_as<string>(ofd->FileName);
			}
		}

		imageList->Images->Clear();
		for (int i = 0; i < IList->Images->Count; i++) {
			string path = Gal.vec_Gal.at(i).PicturePath;
			Image^ img = Image::FromFile(marshal_as<String^>(path));
			imageList->Images->Add(img);
		}

		listViewImages->BeginUpdate();
		listViewImages->Items->Clear();
		for (int i = 0; i < imageList->Images->Count; i++) {
			ListViewItem^ item = listViewImages->Items->Add(gcnew ListViewItem(marshal_as<String^>(Gal.vec_Gal.at(i).PictureName), i));
			item->ImageIndex = i;
		}
		listViewImages->EndUpdate();
		listViewImages->Refresh();
	}
	string time = time_now();
	Gal.Changes.push_back(time);
	Gal.vec_Gal.at(ind).PictureModified = time;
}

void Gallery::DeletePicture(int ind, ImageList^ imageList, ListView^ listViewImages)
{
	Gallery Gal;

	ImageList^ IList = gcnew ImageList();
	IList->ColorDepth = ColorDepth::Depth32Bit;

	for (int i = 0; i < imageList->Images->Count; i++) {
		if (i != ind) {
			string path = Gal.vec_Gal.at(i).PicturePath;
			Image^ img = Image::FromFile(marshal_as<String^>(path));
			IList->Images->Add(img);
		}
	}
	Gal.vec_Gal.erase(vec_Gal.begin() + ind);

	imageList->Images->Clear();
	for (int i = 0; i < IList->Images->Count; i++) {
		string path = Gal.vec_Gal.at(i).PicturePath;
		Image^ img = Image::FromFile(marshal_as<String^>(path));
		imageList->Images->Add(img);
	}

	listViewImages->BeginUpdate();
	listViewImages->Items->Clear();
	for (int i = 0; i < imageList->Images->Count; i++) {
		ListViewItem^ item = listViewImages->Items->Add(gcnew ListViewItem(marshal_as<String^>(Gal.vec_Gal.at(i).PictureName), i));
		item->ImageIndex = i;
	}
	listViewImages->EndUpdate();
	listViewImages->Refresh();
	string time = time_now();
	Gal.Changes.push_back(time);
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

void Gallery::GetInfo()
{
	Gallery Gal;
	String^ ImageCount = Convert::ToString(Gal.vec_Gal.size());
	String^ LastAdd = marshal_as<String^>(Gal.vec_Gal.at(Gal.vec_Gal.size() - 1).PictureDate);
	String^ LastChange = marshal_as<String^>(Gal.Changes.at(Gal.Changes.size() - 1));
	String^ answ = "";
	answ += "Количество изображений в альбоме: " + ImageCount + "\nДата последнего добавления: " + LastAdd + "\nДата последнего изменения: " + LastChange;
	MessageBox::Show(answ, "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
}


void Gallery::Search_Num(ListView^ listViewImages)
{
	for(int i = 0; i < listViewImages->Items->Count; i++)
		listViewImages->Items[i]->Selected = false;
	Gallery Gal;
	String^ Num = Microsoft::VisualBasic::Interaction::InputBox("Введите номер изображения для поиска: ", "Input number", "", 100, 100);
	int num = Convert::ToInt32(Num);
	num--;
	
	listViewImages->Items[num]->Selected = true;
}

void Gallery::Search_Desc(ListView^ listViewImages)
{
	for (int i = 0; i < listViewImages->Items->Count; i++)
		listViewImages->Items[i]->Selected = false;
	Gallery Gal;
	String^ Description = Microsoft::VisualBasic::Interaction::InputBox("Введите описание изображения для поиска: ", "Input description", "", 100, 100);
	string std_desc = marshal_as<string>(Description);
	for (int i = 0; i < Gal.vec_Gal.size(); i++) {
		if (Gal.vec_Gal[i].PictureDescription.find(std_desc) != -1)
			listViewImages->Items[i]->Selected = true;
	}
}

void Gallery::Search_Creation(ListView^ listViewImages)
{
	for (int i = 0; i < listViewImages->Items->Count; i++)
		listViewImages->Items[i]->Selected = false;
	Gallery Gal;
	String^ Creation = Microsoft::VisualBasic::Interaction::InputBox("Введите дату создания изображения для поиска: \nFormat: YYYY-MM-DD HH:MM:SS", "Input creation date", "", 100, 100);
	string std_creat = marshal_as<string>(Creation);
	for (int i = 0; i < Gal.vec_Gal.size(); i++) {
		if (Gal.vec_Gal[i].PictureDate == std_creat)
			listViewImages->Items[i]->Selected = true;
	}
}

void Gallery::Search_Modified(ListView^ listViewImages)
{
	for (int i = 0; i < listViewImages->Items->Count; i++)
		listViewImages->Items[i]->Selected = false;
	Gallery Gal;
	String^ Modified = Microsoft::VisualBasic::Interaction::InputBox("Введите дату изменения изображения для поиска: \nFormat: YYYY-MM-DD HH:MM:SS", "Input modified date", "", 100, 100);
	string std_mod = marshal_as<string>(Modified);
	for (int i = 0; i < Gal.vec_Gal.size(); i++) {
		if ((Gal.vec_Gal[i].PictureModified == std_mod) && (Gal.vec_Gal[i].PictureModified != ""))
			listViewImages->Items[i]->Selected = true;
	}
}

void Gallery::Search_Unfinished(ListView^ listViewImages)
{
	for (int i = 0; i < listViewImages->Items->Count; i++)
		listViewImages->Items[i]->Selected = false;
	Gallery Gal;
	
	for (int i = 0; i < Gal.vec_Gal.size(); i++) {
		if ((Gal.vec_Gal[i].PictureDescription == "") || (Gal.vec_Gal[i].PictureDescription == " "))
			listViewImages->Items[i]->Selected = true;
	}
}

void Gallery::ViewMode(ListView^ listViewImages, PictureBox^ PB)
{
	Gallery Gal;
	
	if (listViewImages->Items->Count > 0) {
		(listViewImages->SelectedIndices->Count > 0) ? Gal.PicView_ind = listViewImages->SelectedIndices[0] : Gal.PicView_ind = 0;
		PB->Image = Image::FromFile(marshal_as<String^>(Gal.vec_Gal.at(PicView_ind).PicturePath));
		PB->SizeMode = PictureBoxSizeMode::StretchImage;
		PB->Refresh();
	}
}

void Gallery::GoToFirst(ListView^ listViewImages, PictureBox^ PB)
{
	Gallery Gal;
	if (Gal.PicView_ind != 0) {
		Gal.PicView_ind = 0;
		PB->Image = Image::FromFile(marshal_as<String^>(Gal.vec_Gal.at(0).PicturePath));
		PB->SizeMode = PictureBoxSizeMode::StretchImage;
		PB->Refresh();
	}
}

void Gallery::GoToLast(ListView^ listViewImages, PictureBox^ PB)
{
	Gallery Gal;
	if (Gal.PicView_ind != Gal.vec_Gal.size() - 1) {
		Gal.PicView_ind = Gal.vec_Gal.size() - 1;
		PB->Image = Image::FromFile(marshal_as<String^>(Gal.vec_Gal.at(Gal.vec_Gal.size() - 1).PicturePath));
		PB->SizeMode = PictureBoxSizeMode::StretchImage;
		PB->Refresh();
	}
}

void Gallery::Prev_Img(ListView^ listViewImages, PictureBox^ PB)
{
	Gallery Gal;
	if (Gal.PicView_ind != 0) {
		Gal.PicView_ind--;
		PB->Image = Image::FromFile(marshal_as<String^>(Gal.vec_Gal.at(Gal.PicView_ind).PicturePath));
		PB->SizeMode = PictureBoxSizeMode::StretchImage;
		PB->Refresh();
	}
}

void Gallery::Next_Img(ListView^ listViewImages, PictureBox^ PB)
{
	Gallery Gal;
	if (Gal.PicView_ind != Gal.vec_Gal.size() - 1) {
		Gal.PicView_ind++;
		PB->Image = Image::FromFile(marshal_as<String^>(Gal.vec_Gal.at(Gal.PicView_ind).PicturePath));
		PB->SizeMode = PictureBoxSizeMode::StretchImage;
		PB->Refresh();
	}
}


