#include "pch.h"
#include "Gallery.h"
#include "Form1.h"
#include <Windows.h>
#include <time.h>
#include <vector>
#include <string>
#include <msclr/marshal_cppstd.h>
#include <fstream>

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

Gallery Gal;

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
			Gal.vec_Gal.push_back(Gallery(std_name, std_description, std_time, std_path));
		
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
	Gal.vec_Gal.at(ind).PictureName = NName;
	listViewImages->Items[ind]->Text = NewName;
	string time = time_now();
	Gal.Changes.push_back(time);
	Gal.vec_Gal.at(ind).PictureModified = time;
	AutoSave();
}

void Gallery::ChangePictureDescription(int ind)
{
	String^ NewDescription = Microsoft::VisualBasic::Interaction::InputBox("Введите новое описание фото:", "New Description", "", 100, 100);
	string NDesc = marshal_as<string>(NewDescription);
	Gal.vec_Gal.at(ind).PictureDescription = NDesc;
	string time = time_now();
	Gal.Changes.push_back(time);
	Gal.vec_Gal.at(ind).PictureModified = time;
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
	AutoSave();
}

void Gallery::DeletePicture(int ind, ImageList^ imageList, ListView^ listViewImages)
{
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
	AutoSave();
}

void Gallery::GetStats(int ind)
{
	String^ answ = "";
	String^ name = marshal_as<String^>(Gal.vec_Gal.at(ind).PictureName);
	String^ date = marshal_as<String^>(Gal.vec_Gal.at(ind).PictureDate);
	String^ description = marshal_as<String^>(Gal.vec_Gal.at(ind).PictureDescription);
	String^ path = marshal_as<String^>(Gal.vec_Gal.at(ind).PicturePath);

	answ += "Name: " + name + "\nDate: " + date + "\nDescription: " + description + "\nPath: " + path;
	MessageBox::Show(answ, "Stats", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

void Gallery::GetInfo() // починить!!!!!!!
{
	try {
		String^ ImageCount = Convert::ToString(Gal.vec_Gal.size());
		String^ LastAdd = marshal_as<String^>(Gal.vec_Gal.at(Gal.vec_Gal.size() - 1).PictureDate);
		String^ LastChange = marshal_as<String^>(Gal.Changes.at(Gal.Changes.size() - 1)); // tut
		String^ answ = "";
		answ += "Количество изображений в альбоме: " + ImageCount + "\nДата последнего добавления: " + LastAdd + "\nДата последнего изменения: " + LastChange;
		MessageBox::Show(answ, "Info", MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
	catch (Exception^ e) {
		MessageBox::Show("Альбом пустой!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}


void Gallery::Search_Num(ListView^ listViewImages)
{
	for(int i = 0; i < listViewImages->Items->Count; i++)
		listViewImages->Items[i]->Selected = false;
	String^ Num = Microsoft::VisualBasic::Interaction::InputBox("Введите номер изображения для поиска: ", "Input number", "", 100, 100);
	int num = Convert::ToInt32(Num);
	num--;
	
	listViewImages->Items[num]->Selected = true;
}

void Gallery::Search_Desc(ListView^ listViewImages)
{
	for (int i = 0; i < listViewImages->Items->Count; i++)
		listViewImages->Items[i]->Selected = false;
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
	for (int i = 0; i < Gal.vec_Gal.size(); i++) {
		if (Gal.vec_Gal[i].PictureDescription == "None.")
			listViewImages->Items[i]->Selected = true;
	}
}

void Gallery::ImgResize(Image^ img, PictureBox^ PB, Form1^ form) {
	Point Loc;
	if (Gal.PicView_mode == 0) {
		Loc = Point(485, 27);
		PB->Size = System::Drawing::Size(400, 400);
	}
	else if (Gal.PicView_mode == 1) {
		double form_x = form->Width;
		double form_y = form->Height;
		double size_x = form_x - (form_x / 2);
		Loc = Point((form_x / 2) - (size_x / 2), 30);
		PB->Size = System::Drawing::Size(form_x - (form_x / 2), form_y - (form_y / 10));
	}
	PB->Location = Loc;
	double x, y;
	double per, out;
	x = img->Width;
	y = img->Height;
	if (abs(x - y) < 50) {
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

void Gallery::ViewMode(ListView^ listViewImages, PictureBox^ PB, Form1^ form)
{
	if (listViewImages->Items->Count > 0) {
		(listViewImages->SelectedIndices->Count > 0) ? Gal.PicView_ind = listViewImages->SelectedIndices[0] : Gal.PicView_ind = 0;
		Image^ img = Image::FromFile(marshal_as<String^>(Gal.vec_Gal.at(PicView_ind).PicturePath));
		Gal.ImgResize(img, PB, form);
		PB->Image = img; 
		PB->SizeMode = PictureBoxSizeMode::StretchImage;
		PB->Refresh();
	}
}

void Gallery::ChangeMode(ListView^ listViewImages, PictureBox^ PB, Form1^ form, Button^ b1, Button^ b2, Button^ b3, Button^ b4, Button^ b5, Button^ b6, Button^ b7, Button^ b0, Button^ b8, Button^ b9, Button^ b10, Button^ b11, PictureBox^ back1, PictureBox^ back2)
{
	if (Gal.PicView_mode == 0) {
		Gal.PicView_mode = 1;

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
		b0->Visible = false;
		b1->Visible = false;
		b7->Location = pt;
		b7->BringToFront();
		Point pt2((form_x / 2) - 50, form_y - 60);
		b6->Size = System::Drawing::Size(50, 50);
		b6->Location = pt2;
		b6->BringToFront();
		Point pt3((form_x / 2) - 110, form_y - 60);
		b4->Size = System::Drawing::Size(50, 50);
		b4->Location = pt3;
		b4->BringToFront();
		Point pt4((form_x / 2) + 10, form_y - 60);
		b5->Size = System::Drawing::Size(50, 50);
		b5->Location = pt4;
		b5->BringToFront();
		Point pt5((form_x / 2) - 170, form_y - 60);
		b2->Size = System::Drawing::Size(50, 50);
		b2->Location = pt5;
		b2->BringToFront();
		Point pt6((form_x / 2) + 70, form_y - 60);
		b3->Size = System::Drawing::Size(50, 50);
		b3->Location = pt6;
		b3->BringToFront();
		Point pt7((form_x / 2) - 230, form_y - 60);
		b8->Location = pt7;
		b8->Visible = true;
		b8->BringToFront();
		Point pt8((form_x / 2) + 130, form_y - 60);
		b9->Location = pt8;
		b9->Visible = true;
		b9->BringToFront();
		Point pt9((form_x / 2) + (size_x / 2) + 20, (form_y / 2) - 60);
		b10->Location = pt9;
		b10->Visible = true;
		b10->BringToFront();
		Point pt10((form_x / 2) + (size_x / 2) + 20, (form_y / 2) + 10);
		b11->Location = pt10;
		b11->Visible = true;
		b11->BringToFront();
		PB->Size = System::Drawing::Size(form_x - (form_x / 2), form_y - (form_y / 10));
		Point pb((form_x / 2) - (size_x / 2), 30);
		PB->Location = pb;
		Gal.min_x = form_x - (form_x / 2);
		Gal.min_y = form_y - (form_y / 10);
		Gal.max_x = min_x * 3.;
		Gal.max_y = min_y * 3.;
		Gal.ImgResize(PB->Image, PB, form);
	}
	else {
		Gal.PicView_mode = 0;

		form->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
		form->WindowState = FormWindowState::Normal;

		listViewImages->Visible = true;
		b0->Visible = true;
		b1->Visible = true;

		Point pt(792, 472);
		b7->Location = pt;

		Point pt2(673, 434);
		b6->Size = System::Drawing::Size(21, 22);
		b6->Location = pt2;

		Point pt3(590, 434);
		b4->Size = System::Drawing::Size(75, 23);
		b4->Location = pt3;

		Point pt4(701, 434);
		b5->Size = System::Drawing::Size(75, 23);
		b5->Location = pt4;

		Point pt5(484, 434);
		b2->Size = System::Drawing::Size(28, 23);
		b2->Location = pt5;

		Point pt6(856, 434);
		b3->Size = System::Drawing::Size(28, 23);
		b3->Location = pt6;

		Point pb(484, 27);
		PB->Size = System::Drawing::Size(400, 400);
		PB->Location = pb;

		b8->Visible = false;
		b9->Visible = false;
		b10->Visible = false;
		b11->Visible = false;
		back1->Visible = false;
		back2->Visible = false;
		listViewImages->BringToFront();
		Gal.ImgResize(PB->Image, PB, form);
	}
}


void Gallery::GoToFirst(ListView^ listViewImages, PictureBox^ PB, Form1^ form)
{
	if (Gal.PicView_ind != 0) {
		Gal.PicView_ind = 0;
		PB->Image = Image::FromFile(marshal_as<String^>(Gal.vec_Gal.at(0).PicturePath));
		PB->SizeMode = PictureBoxSizeMode::StretchImage;
		PB->Refresh();
		if(Gal.PicView_mode == 1)
			PB->Size = System::Drawing::Size(Gal.min_x, Gal.min_y);
		Gal.ImgResize(PB->Image, PB, form);
	}
}

void Gallery::GoToLast(ListView^ listViewImages, PictureBox^ PB, Form1^ form)
{
	if (Gal.PicView_ind != Gal.vec_Gal.size() - 1) {
		Gal.PicView_ind = Gal.vec_Gal.size() - 1;
		PB->Image = Image::FromFile(marshal_as<String^>(Gal.vec_Gal.at(Gal.vec_Gal.size() - 1).PicturePath));
		PB->SizeMode = PictureBoxSizeMode::StretchImage;
		PB->Refresh();
		if (Gal.PicView_mode == 1)
			PB->Size = System::Drawing::Size(Gal.min_x, Gal.min_y);
		Gal.ImgResize(PB->Image, PB, form);
	}
}

void Gallery::Prev_Img(ListView^ listViewImages, PictureBox^ PB, Form1^ form)
{
	if (Gal.PicView_ind != 0) {
		Gal.PicView_ind--;
		PB->Image = Image::FromFile(marshal_as<String^>(Gal.vec_Gal.at(Gal.PicView_ind).PicturePath));
		PB->SizeMode = PictureBoxSizeMode::StretchImage;
		PB->Refresh();
		if (Gal.PicView_mode == 1)
			PB->Size = System::Drawing::Size(Gal.min_x, Gal.min_y);
		Gal.ImgResize(PB->Image, PB, form);
	}
}

void Gallery::Next_Img(ListView^ listViewImages, PictureBox^ PB, Form1^ form)
{
	if (Gal.PicView_ind != Gal.vec_Gal.size() - 1) {
		Gal.PicView_ind++;
		PB->Image = Image::FromFile(marshal_as<String^>(Gal.vec_Gal.at(Gal.PicView_ind).PicturePath));
		PB->SizeMode = PictureBoxSizeMode::StretchImage;
		PB->Refresh();
		if (Gal.PicView_mode == 1)
			PB->Size = System::Drawing::Size(Gal.min_x, Gal.min_y);
		Gal.ImgResize(PB->Image, PB, form);
	}
}

void Gallery::Rotate_Img(ListView^ listViewImages, PictureBox^ PB)
{
	PB->Image->RotateFlip(RotateFlipType::Rotate90FlipNone);
	PB->Refresh();
}

void Gallery::Flip_Img(ListView^ listViewImages, PictureBox^ PB)
{
	PB->Image->RotateFlip(RotateFlipType::RotateNoneFlipX);
	PB->Refresh();
}

void Gallery::Img_minus(ListView^ listViewImages, PictureBox^ PB)
{
	if ((PB->Width >= Gal.min_x) && (PB->Height >= Gal.min_y))  {
		PB->Width -= 50;
		PB->Height -= 50;
	}
}

void Gallery::Img_plus(ListView^ listViewImages, PictureBox^ PB)
{
	if ((PB->Width <= Gal.max_x) && (PB->Height <= Gal.max_y)) {
		PB->Width += 50;
		PB->Height += 50;
	}
}


void Gallery::AutoSave()
{
	ofstream ofile;
	ofstream ofile2;
	ofile.open(Gal.Gal_path, std::ios::out);
	for (int i = 0; i < Gal.vec_Gal.size(); i++)
		ofile << Gal.vec_Gal.at(i).PictureName << '\n' << Gal.vec_Gal.at(i).PictureDescription << '\n' << Gal.vec_Gal.at(i).PictureDate << '\n' << Gal.vec_Gal.at(i).PicturePath << '\n' << Gal.vec_Gal.at(i).PictureModified << '\n';
	ofile.close();
	if (Gal.Changes.size() > 0) {
		ofile2.open(Gal.Changes_path, std::ios::out);
		for (int i = 0; i < Gal.Changes.size(); i++)
			ofile2 << Gal.Changes.at(i) << '\n';
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
	ifile.open(Gal.Gal_path);
	if (ifile.peek() != EOF) {
		while (!ifile.eof()) {
			std::getline(ifile, line);
			size++;
		}
		size--; //потому что последняя строка пустая и не относится ни к одному из файлов
		size /= 5;
		for (int i = 0; i < size; i++)
			Gal.vec_Gal.push_back(Gallery());
		ifile.close();
		ifile.open(Gal.Gal_path);
		while (x < size) {
			std::getline(ifile, line);
			if (count == 0) {
				Gal.vec_Gal.at(x).PictureName = line;
			}
			else if (count == 1) {
				Gal.vec_Gal.at(x).PictureDescription = line;
			}
			else if (count == 2) {
				Gal.vec_Gal.at(x).PictureDate = line;
			}
			else if (count == 3) {
				Gal.vec_Gal.at(x).PicturePath = line;
			}
			else if (count == 4) {
				Gal.vec_Gal.at(x).PictureModified = line;
			}
			if (count < 4)
				count++;
			else {
				count = 0;
				x++;
			}
		}

		for (int i = 0; i < size; i++) {
			string std_time = Gal.vec_Gal.at(i).PictureDate;
			if (Gal.vec_Gal.at(i).PicturePath != "")
			{
				imageList->Images->Add(Image::FromFile(marshal_as<String^>(Gal.vec_Gal.at(i).PicturePath)));
				listViewImages->BeginUpdate();
				ListViewItem^ item = listViewImages->Items->Add(gcnew ListViewItem(marshal_as<String^>(Gal.vec_Gal.at(i).PictureName), imageList->Images->Count - 1));
				item->ImageIndex = imageList->Images->Count - 1;
				listViewImages->EndUpdate();
				listViewImages->LargeImageList = imageList;
				listViewImages->Refresh();
			}
		}
	}
	ifile.close();
	ifile2.open(Gal.Changes_path);
	if (ifile2.peek() != EOF) {
		while (std::getline(ifile2, line)) {
			Gal.Changes.push_back(line);
		}
	}
	ifile2.close();
}

void Gallery::DeleteData(ImageList^ imageList, ListView^ listViewImages, PictureBox^ PB)
{
	ofstream ofile;
	ofstream ofile2;
	ofile.open(Gal.Gal_path, std::ios::out);
	ofile.close();
	ofile2.open(Gal.Changes_path, std::ios::out);
	ofile2.close();
	MessageBox::Show("Сохраненные данные были очищены!", "Delete data", MessageBoxButtons::OK, MessageBoxIcon::Information);
	Gal.vec_Gal.clear();
	Gal.Changes.clear();
	imageList->Images->Clear();
	listViewImages->Clear();
	PB->Image = nullptr;
}