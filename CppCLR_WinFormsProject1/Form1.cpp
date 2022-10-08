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
		Gal.ChangePictureName(ind);
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
