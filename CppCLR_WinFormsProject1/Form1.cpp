#include "pch.h"
#include "Form1.h"
#include <Windows.h>
#include "Gallery.h"
#include <fstream>

System::Void CppCLRWinFormsProject::Form1::btnAddImgage_Click(System::Object^ sender, System::EventArgs^ e) //Button Add Image
{
	Gallery Gal;
	OpenFileDialog^ ofd = gcnew OpenFileDialog();
	ofd->Multiselect = true;
	ofd->Filter = "Image Files(*.JPG; *.PNG) |*.JPG; *.PNG|All files (*.*)|*.*";
	ofd->FilterIndex = 2;
	ofd->RestoreDirectory = true;

	if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		Gal.addImage(ofd->FileNames, this->imageList, this->listViewImages);
	}
}

System::Void CppCLRWinFormsProject::Form1::changePictureNameToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) //Context change pic name
{
	try {
		Gallery Gal;
		int ind = listViewImages->SelectedIndices[0];
		if (listViewImages->SelectedIndices->Count > 1)
			MessageBox::Show("Выбрано несколько фото!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		else
			Gal.ChangePictureName(ind, this->listViewImages);
	}
	catch (Exception^ e) {
		MessageBox::Show("Не выбрано изображение!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

System::Void CppCLRWinFormsProject::Form1::changePictureDescriptionToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) //Context change pic description
{
	try {
		Gallery Gal;
		int ind = listViewImages->SelectedIndices[0];
		if (listViewImages->SelectedIndices->Count > 1)
			MessageBox::Show("Выбрано несколько фото!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		else
			Gal.ChangePictureDescription(ind);
	}
	catch (Exception^ e) {
		MessageBox::Show("Не выбрано изображение!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

System::Void CppCLRWinFormsProject::Form1::changePictureToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) //Context change pic
{
	try {
		Gallery Gal;
		int ind = listViewImages->SelectedIndices[0];
		if (listViewImages->SelectedIndices->Count > 1)
			MessageBox::Show("Выбрано несколько фото!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		else
			Gal.ChangePicture(ind, this->imageList, this->listViewImages);
	}
	catch (Exception^ e) {
		MessageBox::Show("Не выбрано изображение!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

System::Void CppCLRWinFormsProject::Form1::deletePictureToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) //Context delete pic
{
	try {
		Gallery Gal;
		int ind = listViewImages->SelectedIndices[0];
		if (listViewImages->SelectedIndices->Count > 1)
			MessageBox::Show("Выбрано несколько фото!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		else
			Gal.DeletePicture(ind, this->imageList, this->listViewImages);
	}
	catch (Exception^ e) {
		MessageBox::Show("Не выбрано изображение!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

System::Void CppCLRWinFormsProject::Form1::showPictureStatsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) //Show picture stats
{
	try {
		Gallery Gal;
		int ind = listViewImages->SelectedIndices[0];
		if (listViewImages->SelectedIndices->Count > 1)
			MessageBox::Show("Выбрано несколько фото!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		else
			Gal.GetStats(ind);
	}
	catch (Exception^ e) {
		MessageBox::Show("Не выбрано изображение!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

System::Void CppCLRWinFormsProject::Form1::getInfoAboutAlbumToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) //Get info about album
{
	Gallery Gal;
	Gal.GetInfo();
}

//VIEW MODE

System::Void CppCLRWinFormsProject::Form1::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	Gallery Gal;
	if (BtnMode == false) {
		this->listViewImages->Width /= 2.;
		this->listViewImages->Width += 10;
		this->button7->Visible = true;
		BtnMode = true;
		Gal.ViewMode(this->listViewImages, this->pictureBox1, this);
	}
	else if (BtnMode == true) {
		this->listViewImages->Width -= 10;
		this->listViewImages->Width *= 2.;
		this->button7->Visible = false;
		BtnMode = false;
	}
}



System::Void CppCLRWinFormsProject::Form1::button2_Click(System::Object^ sender, System::EventArgs^ e) //on first img
{
	try {
		Gallery Gal;
		Gal.GoToFirst(this->listViewImages, this->pictureBox1, this);
	}
	catch (Exception^ e) {
		MessageBox::Show("Альбом пустой!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

System::Void CppCLRWinFormsProject::Form1::button3_Click(System::Object^ sender, System::EventArgs^ e) //on last img
{
	try {
		Gallery Gal;
		Gal.GoToLast(this->listViewImages, this->pictureBox1, this);
	}
	catch (Exception^ e) {
		MessageBox::Show("Альбом пустой!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

System::Void CppCLRWinFormsProject::Form1::button4_Click(System::Object^ sender, System::EventArgs^ e) //prev img
{
	try {
		Gallery Gal;
		Gal.Prev_Img(this->listViewImages, this->pictureBox1, this);
	}
	catch (Exception^ e) {
		MessageBox::Show("Альбом пустой!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

System::Void CppCLRWinFormsProject::Form1::button5_Click(System::Object^ sender, System::EventArgs^ e) //next img
{
	try {
		Gallery Gal;
		Gal.Next_Img(this->listViewImages, this->pictureBox1, this);
	}
	catch (Exception^ e) {
		MessageBox::Show("Альбом пустой!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

System::Void CppCLRWinFormsProject::Form1::button6_Click(System::Object^ sender, System::EventArgs^ e) //get info
{
	try {
		Gallery Gal;
		Gal.GetStats(Gal.PicView_ind);
	}
	catch (Exception^ e) {
		MessageBox::Show("Альбом пустой!", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

System::Void CppCLRWinFormsProject::Form1::button7_Click(System::Object^ sender, System::EventArgs^ e) //change mode
{
	Gallery Gal;
	Gal.ChangeMode(this->listViewImages, this->pictureBox1, this, this->button1, this->button2, this->button3, this->button4, this->button5, this->button6, this->button7, this->btnAddImgage, this->button8, this->button9, this->button10, this->button11, this->pictureBox2, this->pictureBox3);
}



System::Void CppCLRWinFormsProject::Form1::button8_Click(System::Object^ sender, System::EventArgs^ e) //flip left
{
	Gallery Gal;
	Gal.Rotate_Img(this->listViewImages, this->pictureBox1, this);
}

System::Void CppCLRWinFormsProject::Form1::button9_Click(System::Object^ sender, System::EventArgs^ e) //flip right
{
	Gallery Gal;
	Gal.Flip_Img(this->listViewImages, this->pictureBox1);
}

System::Void CppCLRWinFormsProject::Form1::button10_Click(System::Object^ sender, System::EventArgs^ e) //-
{
	Gallery Gal;
	Gal.Img_minus(this->listViewImages, this->pictureBox1);
}

System::Void CppCLRWinFormsProject::Form1::button11_Click(System::Object^ sender, System::EventArgs^ e) //+
{
	Gallery Gal;
	Gal.Img_plus(this->listViewImages, this->pictureBox1);
}

System::Void CppCLRWinFormsProject::Form1::AutoLoad_Click(System::Object^ sender, System::EventArgs^ e) //autoload
{
	Gallery Gal;
	Gal.AutoLoad(this->imageList, this->listViewImages);
}

System::Void CppCLRWinFormsProject::Form1::deleteDataToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Gallery Gal;
	Gal.DeleteData(this->imageList, this->listViewImages, this->pictureBox1);
}

System::Void CppCLRWinFormsProject::Form1::button12_Click(System::Object^ sender, System::EventArgs^ e)
{
	Gallery Gal;
	Gal.Search(this->listViewImages, textBox1->Text->ToString());
	textBox1->Text = "";
}

System::Void CppCLRWinFormsProject::Form1::searchPatternsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Gallery Gal;
	Gal.SearchPatterns();
}

