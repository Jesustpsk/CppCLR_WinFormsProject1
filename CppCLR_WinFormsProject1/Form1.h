#pragma once

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListView^ listViewImages;
	protected:
	private: System::Windows::Forms::Button^ btnAddImgage;
	private: System::Windows::Forms::ImageList^ imageList;
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ changePictureNameToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ changePictureDescriptionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ changePictureToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ deletePictureToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ showPictureStatsToolStripMenuItem;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ optionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ getInfoAboutAlbumToolStripMenuItem;




	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->listViewImages = (gcnew System::Windows::Forms::ListView());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->showPictureStatsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->changePictureNameToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->changePictureDescriptionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->changePictureToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deletePictureToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->btnAddImgage = (gcnew System::Windows::Forms::Button());
			this->imageList = (gcnew System::Windows::Forms::ImageList(this->components));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->optionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->getInfoAboutAlbumToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->contextMenuStrip1->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// listViewImages
			// 
			this->listViewImages->ContextMenuStrip = this->contextMenuStrip1;
			this->listViewImages->HideSelection = false;
			this->listViewImages->Location = System::Drawing::Point(12, 27);
			this->listViewImages->Name = L"listViewImages";
			this->listViewImages->Size = System::Drawing::Size(885, 438);
			this->listViewImages->TabIndex = 0;
			this->listViewImages->UseCompatibleStateImageBehavior = false;
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->showPictureStatsToolStripMenuItem,
					this->changePictureNameToolStripMenuItem, this->changePictureDescriptionToolStripMenuItem, this->changePictureToolStripMenuItem,
					this->deletePictureToolStripMenuItem
			});
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(218, 114);
			this->contextMenuStrip1->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::contextMenuStrip1_Opening);
			// 
			// showPictureStatsToolStripMenuItem
			// 
			this->showPictureStatsToolStripMenuItem->Name = L"showPictureStatsToolStripMenuItem";
			this->showPictureStatsToolStripMenuItem->Size = System::Drawing::Size(217, 22);
			this->showPictureStatsToolStripMenuItem->Text = L"Show picture stats";
			this->showPictureStatsToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::showPictureStatsToolStripMenuItem_Click);
			// 
			// changePictureNameToolStripMenuItem
			// 
			this->changePictureNameToolStripMenuItem->Name = L"changePictureNameToolStripMenuItem";
			this->changePictureNameToolStripMenuItem->Size = System::Drawing::Size(217, 22);
			this->changePictureNameToolStripMenuItem->Text = L"Change picture name";
			this->changePictureNameToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::changePictureNameToolStripMenuItem_Click);
			// 
			// changePictureDescriptionToolStripMenuItem
			// 
			this->changePictureDescriptionToolStripMenuItem->Name = L"changePictureDescriptionToolStripMenuItem";
			this->changePictureDescriptionToolStripMenuItem->Size = System::Drawing::Size(217, 22);
			this->changePictureDescriptionToolStripMenuItem->Text = L"Change picture description";
			this->changePictureDescriptionToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::changePictureDescriptionToolStripMenuItem_Click);
			// 
			// changePictureToolStripMenuItem
			// 
			this->changePictureToolStripMenuItem->Name = L"changePictureToolStripMenuItem";
			this->changePictureToolStripMenuItem->Size = System::Drawing::Size(217, 22);
			this->changePictureToolStripMenuItem->Text = L"Change picture";
			this->changePictureToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::changePictureToolStripMenuItem_Click);
			// 
			// deletePictureToolStripMenuItem
			// 
			this->deletePictureToolStripMenuItem->Name = L"deletePictureToolStripMenuItem";
			this->deletePictureToolStripMenuItem->Size = System::Drawing::Size(217, 22);
			this->deletePictureToolStripMenuItem->Text = L"Delete picture";
			this->deletePictureToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::deletePictureToolStripMenuItem_Click);
			// 
			// btnAddImgage
			// 
			this->btnAddImgage->Location = System::Drawing::Point(12, 471);
			this->btnAddImgage->Name = L"btnAddImgage";
			this->btnAddImgage->Size = System::Drawing::Size(92, 38);
			this->btnAddImgage->TabIndex = 1;
			this->btnAddImgage->Text = L"Add Images";
			this->btnAddImgage->UseVisualStyleBackColor = true;
			this->btnAddImgage->Click += gcnew System::EventHandler(this, &Form1::btnAddImgage_Click);
			// 
			// imageList
			// 
			this->imageList->ColorDepth = System::Windows::Forms::ColorDepth::Depth32Bit;
			this->imageList->ImageSize = System::Drawing::Size(100, 100);
			this->imageList->TransparentColor = System::Drawing::Color::Transparent;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->optionsToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(910, 24);
			this->menuStrip1->TabIndex = 2;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// optionsToolStripMenuItem
			// 
			this->optionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->getInfoAboutAlbumToolStripMenuItem });
			this->optionsToolStripMenuItem->Name = L"optionsToolStripMenuItem";
			this->optionsToolStripMenuItem->Size = System::Drawing::Size(61, 20);
			this->optionsToolStripMenuItem->Text = L"Options";
			// 
			// getInfoAboutAlbumToolStripMenuItem
			// 
			this->getInfoAboutAlbumToolStripMenuItem->Name = L"getInfoAboutAlbumToolStripMenuItem";
			this->getInfoAboutAlbumToolStripMenuItem->Size = System::Drawing::Size(187, 22);
			this->getInfoAboutAlbumToolStripMenuItem->Text = L"Get info about album";
			this->getInfoAboutAlbumToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::getInfoAboutAlbumToolStripMenuItem_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(910, 521);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->btnAddImgage);
			this->Controls->Add(this->listViewImages);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->contextMenuStrip1->ResumeLayout(false);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: 
		System::Void btnAddImgage_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void contextMenuStrip1_Opening(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e);
		System::Void changePictureNameToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void changePictureDescriptionToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void changePictureToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void deletePictureToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void showPictureStatsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void getInfoAboutAlbumToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
};
}
