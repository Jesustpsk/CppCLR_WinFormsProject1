#include "pch.h"
#include "Gallery.h"
#include "Form1.h"
#include <Windows.h>
#include <time.h>
#include <vector>
#include <string>
#include <msclr/marshal_cppstd.h>
#include <fstream>
#include <algorithm>

using std::ifstream;
using std::ofstream;
using std::vector;
using std::string;

using namespace msclr::interop;
using namespace CppCLRWinFormsProject;

vector <Gallery> Gallery::vec_Gal;
vector <string> Gallery::Changes;

int Gallery::PicView_ind = 0;
int Gallery::PicView_mode = 0;
double Gallery::min_x = 0;
double Gallery::min_y = 0;
double Gallery::max_x = 0;
double Gallery::max_y = 0;
string Gallery::Gal_path = "data_Gal.txt";
string Gallery::Changes_path = "data_Changes.txt";

Image_ Img_;

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
			if (std_description == "")
				std_description = "None.";
			String^ path = images[i];
			string std_path = marshal_as<string>(path);
			vec_Gal.push_back(Gallery(std_name, std_description, std_time, std_path));
		
			item->ImageIndex = imageList->Images->Count - 1;
			listViewImages->EndUpdate();
			listViewImages->LargeImageList = imageList;	
			listViewImages->Refresh();
		}
	}
	AutoSave();
}

void Gallery::ChangePictureName(int ind, ListView^ listViewImages)
{
	String^ NewName = Microsoft::VisualBasic::Interaction::InputBox("Введите новое имя фото:", "New Name", "", 100, 100);
	string NName = marshal_as<string>(NewName);
	vec_Gal.at(ind).PictureName = NName;
	listViewImages->Items[ind]->Text = NewName;
	string time = time_now();
	Changes.push_back(time);
	vec_Gal.at(ind).PictureModified = time;
	AutoSave();
}
void Gallery::ChangePictureDescription(int ind)
{
	String^ NewDescription = Microsoft::VisualBasic::Interaction::InputBox("Введите новое описание фото:", "New Description", "", 100, 100);
	string NDesc = marshal_as<string>(NewDescription);
	vec_Gal.at(ind).PictureDescription = NDesc;
	string time = time_now();
	Changes.push_back(time);
	vec_Gal.at(ind).PictureModified = time;
	AutoSave();
}
void Gallery::ChangePicture(int ind, ImageList^ imageList, ListView^ listViewImages)
{
	ImageList^ IList = gcnew ImageList();
	IList->ColorDepth = ColorDepth::Depth32Bit;

	OpenFileDialog^ ofd = gcnew OpenFileDialog();
	ofd->Filter = "Image Files(*.JPG; *.PNG) |*.JPG; *.PNG|All files (*.*)|*.*";
	ofd->FilterIndex = 2;
	ofd->RestoreDirectory = true;

	if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		for (int i = 0; i < imageList->Images->Count; i++) {
			if (i != ind) {
				string path = vec_Gal.at(i).PicturePath;
				Image^ img = Image::FromFile(marshal_as<String^>(path));
				IList->Images->Add(img);
			}
			else {
				Image^ img = Image::FromFile(ofd->FileName);
				IList->Images->Add(img);
				vec_Gal.at(i).PicturePath = marshal_as<string>(ofd->FileName);
			}
		}

		imageList->Images->Clear();
		for (int i = 0; i < IList->Images->Count; i++) {
			string path = vec_Gal.at(i).PicturePath;
			Image^ img = Image::FromFile(marshal_as<String^>(path));
			imageList->Images->Add(img);
		}

		listViewImages->BeginUpdate();
		listViewImages->Items->Clear();
		for (int i = 0; i < imageList->Images->Count; i++) {
			ListViewItem^ item = listViewImages->Items->Add(gcnew ListViewItem(marshal_as<String^>(vec_Gal.at(i).PictureName), i));
			item->ImageIndex = i;
		}
		listViewImages->EndUpdate();
		listViewImages->Refresh();
	}
	string time = time_now();
	Changes.push_back(time);
	vec_Gal.at(ind).PictureModified = time;
	AutoSave();
}
void Gallery::DeletePicture(int ind, ImageList^ imageList, ListView^ listViewImages)
{
	ImageList^ IList = gcnew ImageList();
	IList->ColorDepth = ColorDepth::Depth32Bit;

	for (int i = 0; i < imageList->Images->Count; i++) {
		if (i != ind) {
			string path = vec_Gal.at(i).PicturePath;
			Image^ img = Image::FromFile(marshal_as<String^>(path));
			IList->Images->Add(img);
		}
	}
	vec_Gal.erase(vec_Gal.begin() + ind);

	imageList->Images->Clear();
	for (int i = 0; i < IList->Images->Count; i++) {
		string path = vec_Gal.at(i).PicturePath;
		Image^ img = Image::FromFile(marshal_as<String^>(path));
		imageList->Images->Add(img);
	}

	listViewImages->BeginUpdate();
	listViewImages->Items->Clear();
	for (int i = 0; i < imageList->Images->Count; i++) {
		ListViewItem^ item = listViewImages->Items->Add(gcnew ListViewItem(marshal_as<String^>(vec_Gal.at(i).PictureName), i));
		item->ImageIndex = i;
	}
	listViewImages->EndUpdate();
	listViewImages->Refresh();
	string time = time_now();
	Changes.push_back(time);
	AutoSave();
}

void Gallery::GetStats(int ind)
{
	String^ answ = "";
	String^ name = marshal_as<String^>(vec_Gal.at(ind).PictureName);
	String^ date = marshal_as<String^>(vec_Gal.at(ind).PictureDate);
	String^ description = marshal_as<String^>(vec_Gal.at(ind).PictureDescription);
	String^ path = marshal_as<String^>(vec_Gal.at(ind).PicturePath);

	answ += "Name: " + name + "\nDate: " + date + "\nDescription: " + description + "\nPath: " + path;
	MessageBox::Show(answ, "Stats", MessageBoxButtons::OK, MessageBoxIcon::Information);
}
void Gallery::GetInfo()
{
	try {
		String^ ImageCount = Convert::ToString(vec_Gal.size());
		String^ LastAdd = marshal_as<String^>(vec_Gal.at(vec_Gal.size() - 1).PictureDate);
		String^ LastChange;
		if (Changes.size() > 0)
			LastChange = marshal_as<String^>(Changes.at(Changes.size() - 1));
		else
			LastChange = "None.";
		String^ answ = "";
		answ += "Количество изображений в альбоме: " + ImageCount + "\nДата последнего добавления: " + LastAdd + "\nДата последнего изменения: " + LastChange;
		MessageBox::Show(answ, "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
	catch (Exception^ e) {
		MessageBox::Show("Альбом пустой!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
string Gallery::GetPath(int ind){
	return vec_Gal.at(ind).PicturePath;
}

void Gallery::Search(ListView^ listViewImages, String^ search_in, PictureBox^ PB)
{
	if (listViewImages->Items->Count > 0) {
		for (int i = 0; i < listViewImages->Items->Count; i++)
			listViewImages->Items[i]->Selected = false;
		if ((search_in == "") || (search_in == " ") || (search_in == "None.")) { //Unfinished
			for (int i = 0; i < vec_Gal.size(); i++) {
				if (vec_Gal[i].PictureDescription == "None.")
					listViewImages->Items[i]->Selected = true;
			}
		}
		else {
			try {																//number
				int num = Convert::ToInt32(search_in);
				num--;
				listViewImages->Items[num]->Selected = true;
			}
			catch (Exception^ e) {												//date creat. or mod.
				string search = marshal_as<string>(search_in);
				int hyphen = 0;
				int colon = 0;
				int space = 0;
				for (int i = 0; i < search.size(); i++) {
					if (search[i] == '-')
						hyphen++;
					if (search[i] == ':')
						colon++;
					if (search[i] == ' ')
						space++;
				}
				if ((hyphen == 2) && (colon == 2) && (space == 1)) {
					for (int i = 0; i < vec_Gal.size(); i++) {
						if ((vec_Gal[i].PictureDate == search) || (vec_Gal[i].PictureModified == search))
							listViewImages->Items[i]->Selected = true;
					}
				}
				else {
					for (int i = 0; i < vec_Gal.size(); i++) {				//description
						if (vec_Gal[i].PictureDescription.find(search) != -1)
							listViewImages->Items[i]->Selected = true;
					}
				}
			}
		}
		Form1 f;
		if (f.BtnMode == true) {
			string path = GetPath(listViewImages->SelectedIndices[0]);
			Image^ img = Image::FromFile(marshal_as<String^>(path));
			PB->Image = img;
			Img_.ImgResize(img, PB);
		}
	}
	else MessageBox::Show("Альбом пустой!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
}
void Gallery::SearchPatterns(){
	MessageBox::Show("Шаблоны поиска:\n1. Для поиска по номеру изображения введите целое число.\n2. Для поиска по дате создания или изменения изображения введите дату (Format: YYYY-MM-DD HH:MM:SS)\n3. Для поиска по комментарию к изображению введите комментарий полностью или частично\n4. Для поиска незаконченых изображений не вводите ничего (Либо введите знак пробела или слово None.)", "Search Patterns", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

void Image_::ImgResize(Image^ img, PictureBox^ PB, Form1^ form) {
	Point Loc;
	double x, y;
	double per, out;
	if (PicView_mode == 0) {
		Loc = Point(485, 27);
		PB->Size = System::Drawing::Size(400, 400);
	}
	else if (PicView_mode == 1) {
		double form_x = form->Width;
		double form_y = form->Height;
		double size_x = form_x - (form_x / 2);
		Loc = Point((form_x / 2) - (size_x / 2), 30);
		
		PB->Size = System::Drawing::Size(form_x - (form_x / 2), form_y - (form_y / 10));
		
	}
	PB->Location = Loc;
	x = img->Width;
	y = img->Height;
	if (abs(x - y) < 100) {
		PB->Location = Loc;
	}
	else if (x > y) {
		per = PB->Width - x;
		per = abs(per);
		per = per / x * 100.;
		per = 100 - per;
		out = y * (per / 100.);
		PB->Height = out;
		Point p(PB->Location.X, PB->Location.Y + ((PB->Width - PB->Height) / 2));
		PB->Location = p;
	}
	else if (x < y) {
		per = PB->Height - y;
		per = abs(per);
		per = per / y * 100.;
		per = 100 - per;
		out = x * (per / 100.);
		PB->Width = out;
		Point p(PB->Location.X + ((PB->Height - PB->Width) / 2), PB->Location.Y);
		PB->Location = p;
	}
}
void Image_::ImgResize(Image^ img, PictureBox^ PB) {
	Point Loc;
	double x, y;
	double per, out;
	Loc = Point(485, 27);
	PB->Size = System::Drawing::Size(400, 400);
	PB->Location = Loc;
	x = img->Width;
	y = img->Height;
	if (abs(x - y) < 100) {
		PB->Location = Loc;
	}
	else if (x > y) {
		per = PB->Width - x;
		per = abs(per);
		per = per / x * 100.;
		per = 100 - per;
		out = y * (per / 100.);
		PB->Height = out;
		Point p(PB->Location.X, PB->Location.Y + ((PB->Width - PB->Height) / 2));
		PB->Location = p;
	}
	else if (x < y) {
		per = PB->Height - y;
		per = abs(per);
		per = per / y * 100.;
		per = 100 - per;
		out = x * (per / 100.);
		PB->Width = out;
		Point p(PB->Location.X + ((PB->Height - PB->Width) / 2), PB->Location.Y);
		PB->Location = p;
	}
}

void Image_::ViewMode(ListView^ listViewImages, PictureBox^ PB, Form1^ form)
{
	if (listViewImages->Items->Count > 0) {
		(listViewImages->SelectedIndices->Count > 0) ? PicView_ind = listViewImages->SelectedIndices[0] : PicView_ind = 0;
		Image^ img = Image::FromFile(marshal_as<String^>(GetPath(PicView_ind)));
		
		Img_.ImgResize(img, PB, form);
		PB->Image = img; 
		PB->SizeMode = PictureBoxSizeMode::StretchImage;
		PB->Refresh();
	}
}
void Image_::ChangeMode(ListView^ listViewImages, PictureBox^ PB, Form1^ form, array<Button^>^ Buts, PictureBox^ back1, PictureBox^ back2, Label^ L, TextBox^ TB)
{
	if (PicView_mode == 0) {
		PicView_mode = 1;

		form->TopMost = true;
		form->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
		form->WindowState = System::Windows::Forms::FormWindowState::Maximized;
		double form_x = form->Width;
		double form_y = form->Height;
		double size_x = form_x - (form_x / 2);

		Point p_back1((form_x / 2) + (size_x / 2), 25);
		back1->Size = System::Drawing::Size((form_x / 2), form_y);
		back1->Location = p_back1;
		back1->Visible = true;
		Bitmap^ img = gcnew Bitmap("background.png");
		back2->Image = img;

		Point p_back2(0, (form_y / 2) + (size_x / 2) - 20);
		back2->Size = System::Drawing::Size(form_x, form_y);
		back2->Location = p_back2;
		back2->Visible = true;
		back2->Image = img;

		Point pt(form_x - 102, form_y - 47);
		listViewImages->Visible = false;
		Buts[0]->Visible = false;
		Buts[1]->Visible = false;
		Buts[7]->Location = pt;
		Buts[7]->BringToFront();
		Point pt2((form_x / 2) - 50, form_y - 60);
		Buts[6]->Size = System::Drawing::Size(50, 50);
		Buts[6]->Location = pt2;
		Buts[6]->BringToFront();
		Point pt3((form_x / 2) - 110, form_y - 60);
		Buts[4]->Size = System::Drawing::Size(50, 50);
		Buts[4]->Location = pt3;
		Buts[4]->BringToFront();
		Point pt4((form_x / 2) + 10, form_y - 60);
		Buts[5]->Size = System::Drawing::Size(50, 50);
		Buts[5]->Location = pt4;
		Buts[5]->BringToFront();
		Point pt5((form_x / 2) - 170, form_y - 60);
		Buts[2]->Size = System::Drawing::Size(50, 50);
		Buts[2]->Location = pt5;
		Buts[2]->BringToFront();
		Point pt6((form_x / 2) + 70, form_y - 60);
		Buts[3]->Size = System::Drawing::Size(50, 50);
		Buts[3]->Location = pt6;
		Buts[3]->BringToFront();
		Point pt7((form_x / 2) - 230, form_y - 60);
		Buts[8]->Location = pt7;
		Buts[8]->Visible = true;
		Buts[8]->BringToFront();
		Point pt8((form_x / 2) + 130, form_y - 60);
		Buts[9]->Location = pt8;
		Buts[9]->Visible = true;
		Buts[9]->BringToFront();
		Point pt9((form_x / 2) + (size_x / 2) + 20, (form_y / 2) - 60);
		Buts[10]->Location = pt9;
		Buts[10]->Visible = true;
		Buts[10]->BringToFront();
		Point pt10((form_x / 2) + (size_x / 2) + 20, (form_y / 2) + 10);
		Buts[11]->Location = pt10;
		Buts[11]->Visible = true;
		Buts[11]->BringToFront();
		Buts[12]->Visible = false;
		L->Visible = false;
		TB->Visible = false;
		PB->Size = System::Drawing::Size(form_x - (form_x / 2), form_y - (form_y / 10));
		Point pb((form_x / 2) - (size_x / 2), 30);
		PB->Location = pb;
		min_x = PB->Width;
		min_y = PB->Height;
		max_x = min_x * 3.;
		max_y = min_y * 3.;
		if(PB->Image != nullptr)
			Img_.ImgResize(PB->Image, PB, form);
	}
	else {
		PicView_mode = 0;

		form->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
		form->WindowState = FormWindowState::Normal;

		listViewImages->Visible = true;
		Buts[0]->Visible = true;
		Buts[1]->Visible = true;

		Point pt(792, 472);
		Buts[7]->Location = pt;

		Point pt2(673, 434);
		Buts[6]->Size = System::Drawing::Size(21, 22);
		Buts[6]->Location = pt2;

		Point pt3(590, 434);
		Buts[4]->Size = System::Drawing::Size(75, 23);
		Buts[4]->Location = pt3;

		Point pt4(701, 434);
		Buts[5]->Size = System::Drawing::Size(75, 23);
		Buts[5]->Location = pt4;

		Point pt5(484, 434);
		Buts[2]->Size = System::Drawing::Size(28, 23);
		Buts[2]->Location = pt5;

		Point pt6(856, 434);
		Buts[3]->Size = System::Drawing::Size(28, 23);
		Buts[3]->Location = pt6;

		Point pb(484, 27);
		PB->Size = System::Drawing::Size(400, 400);
		PB->Location = pb;

		Buts[8]->Visible = false;
		Buts[9]->Visible = false;
		Buts[10]->Visible = false;
		Buts[11]->Visible = false;
		Buts[12]->Visible = true;
		L->Visible = true;
		TB->Visible = true;
		back1->Visible = false;
		back2->Visible = false;
		listViewImages->BringToFront();
		if (PB->Image != nullptr)
			Img_.ImgResize(PB->Image, PB, form);
	}
}

void Image_::GoToFirst(ListView^ listViewImages, PictureBox^ PB, Form1^ form)
{
	if (PicView_ind != 0) {
		PicView_ind = 0;
		PB->Image = Image::FromFile(marshal_as<String^>(GetPath(0)));
		PB->SizeMode = PictureBoxSizeMode::StretchImage;
		PB->Refresh();
		if(PicView_mode == 1)
			PB->Size = System::Drawing::Size(min_x, min_y);
		Img_.ImgResize(PB->Image, PB, form);
	}
}
void Image_::GoToLast(ListView^ listViewImages, PictureBox^ PB, Form1^ form)
{
	if (PicView_ind != vec_Gal.size() - 1) {
		PicView_ind = vec_Gal.size() - 1;
		PB->Image = Image::FromFile(marshal_as<String^>(GetPath(vec_Gal.size() - 1)));
		PB->SizeMode = PictureBoxSizeMode::StretchImage;
		PB->Refresh();
		if (PicView_mode == 1)
			PB->Size = System::Drawing::Size(min_x, min_y);
		Img_.ImgResize(PB->Image, PB, form);
	}
}
void Image_::Prev_Img(ListView^ listViewImages, PictureBox^ PB, Form1^ form)
{
	if (PicView_ind != 0) {
		PicView_ind--;
		PB->Image = Image::FromFile(marshal_as<String^>(GetPath(PicView_ind)));
		PB->SizeMode = PictureBoxSizeMode::StretchImage;
		PB->Refresh();
		if (PicView_mode == 1)
			PB->Size = System::Drawing::Size(min_x, min_y);
		Img_.ImgResize(PB->Image, PB, form);
	}
}
void Image_::Next_Img(ListView^ listViewImages, PictureBox^ PB, Form1^ form)
{
	if (PicView_ind != vec_Gal.size() - 1) {
		PicView_ind++;
		PB->Image = Image::FromFile(marshal_as<String^>(GetPath(PicView_ind)));
		PB->SizeMode = PictureBoxSizeMode::StretchImage;
		PB->Refresh();
		if (PicView_mode == 1)
			PB->Size = System::Drawing::Size(min_x, min_y);
		Img_.ImgResize(PB->Image, PB, form);
	}
}
void Image_::Rotate_Img(ListView^ listViewImages, PictureBox^ PB, Form1^ form)
{
	PB->Image->RotateFlip(RotateFlipType::Rotate90FlipNone);
	double x, y;
	x = PB->Size.Width;
	y = PB->Size.Height;
	std::swap(x, y);
	PB->Size = System::Drawing::Size(x, y);
	Img_.ImgResize(PB->Image, PB, form);
	PB->Refresh();

}
void Image_::Flip_Img(ListView^ listViewImages, PictureBox^ PB)
{
	PB->Image->RotateFlip(RotateFlipType::RotateNoneFlipX);
	PB->Refresh();
}
void Image_::Img_minus(ListView^ listViewImages, PictureBox^ PB)
{
	if ((PB->Width >= min_x) && (PB->Height >= min_y))  {
		PB->Width -= 50;
		PB->Height -= 50;
	}
}
void Image_::Img_plus(ListView^ listViewImages, PictureBox^ PB)
{
	if ((PB->Width <= max_x) && (PB->Height <= max_y)) {
		PB->Width += 50;
		PB->Height += 50;
	}
}

void Gallery::AutoSave()
{
	ofstream ofile;
	ofstream ofile2;
	ofile.open(Gal_path, std::ios::out);
	for (int i = 0; i < vec_Gal.size(); i++)
		ofile << vec_Gal.at(i).PictureName << '\n' << vec_Gal.at(i).PictureDescription << '\n' << vec_Gal.at(i).PictureDate << '\n' << vec_Gal.at(i).PicturePath << '\n' << vec_Gal.at(i).PictureModified << '\n';
	ofile.close();
	if (Changes.size() > 0) {
		ofile2.open(Changes_path, std::ios::out);
		for (int i = 0; i < Changes.size(); i++)
			ofile2 << Changes.at(i) << '\n';
		ofile2.close();
	}
}
void Gallery::AutoLoad(ImageList^ imageList, ListView^ listViewImages)
{
	ifstream ifile;
	ifstream ifile2;
	string line;
	int count = 0;
	int x = 0;
	int size = 0;
	ifile.open(Gal_path);
	if (ifile.peek() != EOF) {
		while (!ifile.eof()) {
			std::getline(ifile, line);
			size++;
		}
		size--; //потому что последняя строка пустая и не относится ни к одному из файлов
		size /= 5;
		for (int i = 0; i < size; i++)
			vec_Gal.push_back(Gallery());
		ifile.close();
		ifile.open(Gal_path);
		while (x < size) {
			std::getline(ifile, line);
			if (count == 0) {
				vec_Gal.at(x).PictureName = line;
			}
			else if (count == 1) {
				vec_Gal.at(x).PictureDescription = line;
			}
			else if (count == 2) {
				vec_Gal.at(x).PictureDate = line;
			}
			else if (count == 3) {
				vec_Gal.at(x).PicturePath = line;
			}
			else if (count == 4) {
				vec_Gal.at(x).PictureModified = line;
			}
			if (count < 4)
				count++;
			else {
				count = 0;
				x++;
			}
		}

		for (int i = 0; i < size; i++) {
			string std_time = vec_Gal.at(i).PictureDate;
			if (vec_Gal.at(i).PicturePath != "")
			{
				imageList->Images->Add(Image::FromFile(marshal_as<String^>(vec_Gal.at(i).PicturePath)));
				listViewImages->BeginUpdate();
				ListViewItem^ item = listViewImages->Items->Add(gcnew ListViewItem(marshal_as<String^>(vec_Gal.at(i).PictureName), imageList->Images->Count - 1));
				item->ImageIndex = imageList->Images->Count - 1;
				listViewImages->EndUpdate();
				listViewImages->LargeImageList = imageList;
				listViewImages->Refresh();
			}
		}
	}
	ifile.close();
	ifile2.open(Changes_path);
	if (ifile2.peek() != EOF) {
		while (std::getline(ifile2, line)) {
			Changes.push_back(line);
		}
	}
	ifile2.close();
}
void Gallery::DeleteData(ImageList^ imageList, ListView^ listViewImages, PictureBox^ PB)
{
	ofstream ofile;
	ofstream ofile2;
	ofile.open(Gal_path, std::ios::out);
	ofile.close();
	ofile2.open(Changes_path, std::ios::out);
	ofile2.close();
	MessageBox::Show("Сохраненные данные были очищены!", "Delete data", MessageBoxButtons::OK, MessageBoxIcon::Information);
	vec_Gal.clear();
	Changes.clear();
	imageList->Images->Clear();
	listViewImages->Clear();
	PB->Image = nullptr;
}