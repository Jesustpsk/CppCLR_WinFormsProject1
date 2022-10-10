#include "pch.h"
#include "Form1.h"
#include <Windows.h>
#include "Gallery.h"


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

System::Void CppCLRWinFormsProject::Form1::contextMenuStrip1_Opening(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e)
{
	return System::Void();
}

System::Void CppCLRWinFormsProject::Form1::changePictureNameToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) //Context change pic name
{
	Gallery Gal;
	int ind = listViewImages->SelectedIndices[0];
	if (listViewImages->SelectedIndices->Count > 1)
		MessageBox::Show("Выбрано несколько фото!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	else
		Gal.ChangePictureName(ind, this->listViewImages);
}

System::Void CppCLRWinFormsProject::Form1::changePictureDescriptionToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) //Context change pic description
{
	Gallery Gal;
	int ind = listViewImages->SelectedIndices[0];
	if (listViewImages->SelectedIndices->Count > 1)
		MessageBox::Show("Выбрано несколько фото!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	else
		Gal.ChangePictureDescription(ind);
}

System::Void CppCLRWinFormsProject::Form1::changePictureToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) //Context change pic
{
	Gallery Gal;
	int ind = listViewImages->SelectedIndices[0];
	if (listViewImages->SelectedIndices->Count > 1)
		MessageBox::Show("Выбрано несколько фото!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	else
		Gal.ChangePicture(ind, this->imageList, this->listViewImages);
}

System::Void CppCLRWinFormsProject::Form1::deletePictureToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) //Context delete pic
{
	Gallery Gal;
	int ind = listViewImages->SelectedIndices[0];
	if (listViewImages->SelectedIndices->Count > 1)
		MessageBox::Show("Выбрано несколько фото!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	else
		Gal.DeletePicture(ind, this->imageList, this->listViewImages);
}

System::Void CppCLRWinFormsProject::Form1::showPictureStatsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) //Show picture stats
{
	Gallery Gal;
	int ind = listViewImages->SelectedIndices[0];
	if (listViewImages->SelectedIndices->Count > 1)
		MessageBox::Show("Выбрано несколько фото!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	else
		Gal.GetStats(ind);
}

System::Void CppCLRWinFormsProject::Form1::getInfoAboutAlbumToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) //Get info about album
{
	Gallery Gal;
	Gal.GetInfo();
}

//SEARCH

System::Void CppCLRWinFormsProject::Form1::searchByNumberToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) // BY NUMBER
{
	Gallery Gal;
	Gal.Search_Num(this->listViewImages);
}

System::Void CppCLRWinFormsProject::Form1::searchByDescriptionToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) // BY DESCRIPTION
{
	Gallery Gal;
	Gal.Search_Desc(this->listViewImages);
}

System::Void CppCLRWinFormsProject::Form1::searchByCreationDateToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) // BY CREATION DATE
{
	Gallery Gal;
	Gal.Search_Creation(this->listViewImages);
}

System::Void CppCLRWinFormsProject::Form1::modifiedDateToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) // BY MODIFIED DATE
{
	Gallery Gal;
	Gal.Search_Modified(this->listViewImages);
}

System::Void CppCLRWinFormsProject::Form1::unfinishedImagesToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Gallery Gal;
	Gal.Search_Unfinished(this->listViewImages);
}

//VIEW MODE

System::Void CppCLRWinFormsProject::Form1::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	Gallery Gal;
	if (BtnMode == false) {
		this->listViewImages->Width /= 2.;
		BtnMode = true;
		Gal.ViewMode(this->listViewImages, this->pictureBox1);
	}
	else if (BtnMode == true) {
		this->listViewImages->Width *= 2.;
		BtnMode = false;
	}
}



System::Void CppCLRWinFormsProject::Form1::button2_Click(System::Object^ sender, System::EventArgs^ e) //on first img
{
	Gallery Gal;
	Gal.GoToFirst(this->listViewImages, this->pictureBox1);
}

System::Void CppCLRWinFormsProject::Form1::button3_Click(System::Object^ sender, System::EventArgs^ e) //on last img
{
	Gallery Gal;
	Gal.GoToLast(this->listViewImages, this->pictureBox1);
}

System::Void CppCLRWinFormsProject::Form1::button4_Click(System::Object^ sender, System::EventArgs^ e) //prev img
{
	Gallery Gal;
	Gal.Prev_Img(this->listViewImages, this->pictureBox1);
}

System::Void CppCLRWinFormsProject::Form1::button5_Click(System::Object^ sender, System::EventArgs^ e) //next img
{
	Gallery Gal;
	Gal.Next_Img(this->listViewImages, this->pictureBox1);
}

System::Void CppCLRWinFormsProject::Form1::button6_Click(System::Object^ sender, System::EventArgs^ e) //get info
{
	Gallery Gal;
	// to be contuined 
}

