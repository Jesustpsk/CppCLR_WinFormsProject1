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
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Button^ button7;
	public:
		static bool BtnMode = false;
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
	private: System::Windows::Forms::ToolStripMenuItem^ searchByToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ searchByNumberToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ searchByDescriptionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ searchByCreationDateToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ modifiedDateToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ unfinishedImagesToolStripMenuItem;
	private: System::Windows::Forms::Button^ button1;




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
			this->searchByToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->searchByNumberToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->searchByDescriptionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->searchByCreationDateToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->modifiedDateToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->unfinishedImagesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->contextMenuStrip1->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// listViewImages
			// 
			this->listViewImages->ContextMenuStrip = this->contextMenuStrip1;
			this->listViewImages->HideSelection = false;
			this->listViewImages->Location = System::Drawing::Point(16, 33);
			this->listViewImages->Margin = System::Windows::Forms::Padding(4);
			this->listViewImages->Name = L"listViewImages";
			this->listViewImages->Size = System::Drawing::Size(1180, 538);
			this->listViewImages->TabIndex = 0;
			this->listViewImages->UseCompatibleStateImageBehavior = false;
			this->listViewImages->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::listViewImages_SelectedIndexChanged);
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->showPictureStatsToolStripMenuItem,
					this->changePictureNameToolStripMenuItem, this->changePictureDescriptionToolStripMenuItem, this->changePictureToolStripMenuItem,
					this->deletePictureToolStripMenuItem
			});
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(257, 124);
			this->contextMenuStrip1->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::contextMenuStrip1_Opening);
			// 
			// showPictureStatsToolStripMenuItem
			// 
			this->showPictureStatsToolStripMenuItem->Name = L"showPictureStatsToolStripMenuItem";
			this->showPictureStatsToolStripMenuItem->Size = System::Drawing::Size(256, 24);
			this->showPictureStatsToolStripMenuItem->Text = L"Show picture stats";
			this->showPictureStatsToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::showPictureStatsToolStripMenuItem_Click);
			// 
			// changePictureNameToolStripMenuItem
			// 
			this->changePictureNameToolStripMenuItem->Name = L"changePictureNameToolStripMenuItem";
			this->changePictureNameToolStripMenuItem->Size = System::Drawing::Size(256, 24);
			this->changePictureNameToolStripMenuItem->Text = L"Change picture name";
			this->changePictureNameToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::changePictureNameToolStripMenuItem_Click);
			// 
			// changePictureDescriptionToolStripMenuItem
			// 
			this->changePictureDescriptionToolStripMenuItem->Name = L"changePictureDescriptionToolStripMenuItem";
			this->changePictureDescriptionToolStripMenuItem->Size = System::Drawing::Size(256, 24);
			this->changePictureDescriptionToolStripMenuItem->Text = L"Change picture description";
			this->changePictureDescriptionToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::changePictureDescriptionToolStripMenuItem_Click);
			// 
			// changePictureToolStripMenuItem
			// 
			this->changePictureToolStripMenuItem->Name = L"changePictureToolStripMenuItem";
			this->changePictureToolStripMenuItem->Size = System::Drawing::Size(256, 24);
			this->changePictureToolStripMenuItem->Text = L"Change picture";
			this->changePictureToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::changePictureToolStripMenuItem_Click);
			// 
			// deletePictureToolStripMenuItem
			// 
			this->deletePictureToolStripMenuItem->Name = L"deletePictureToolStripMenuItem";
			this->deletePictureToolStripMenuItem->Size = System::Drawing::Size(256, 24);
			this->deletePictureToolStripMenuItem->Text = L"Delete picture";
			this->deletePictureToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::deletePictureToolStripMenuItem_Click);
			// 
			// btnAddImgage
			// 
			this->btnAddImgage->Location = System::Drawing::Point(16, 580);
			this->btnAddImgage->Margin = System::Windows::Forms::Padding(4);
			this->btnAddImgage->Name = L"btnAddImgage";
			this->btnAddImgage->Size = System::Drawing::Size(123, 47);
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
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->optionsToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1213, 30);
			this->menuStrip1->TabIndex = 2;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// optionsToolStripMenuItem
			// 
			this->optionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->getInfoAboutAlbumToolStripMenuItem,
					this->searchByToolStripMenuItem
			});
			this->optionsToolStripMenuItem->Name = L"optionsToolStripMenuItem";
			this->optionsToolStripMenuItem->Size = System::Drawing::Size(75, 24);
			this->optionsToolStripMenuItem->Text = L"Options";
			// 
			// getInfoAboutAlbumToolStripMenuItem
			// 
			this->getInfoAboutAlbumToolStripMenuItem->Name = L"getInfoAboutAlbumToolStripMenuItem";
			this->getInfoAboutAlbumToolStripMenuItem->Size = System::Drawing::Size(234, 26);
			this->getInfoAboutAlbumToolStripMenuItem->Text = L"Get info about album";
			this->getInfoAboutAlbumToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::getInfoAboutAlbumToolStripMenuItem_Click);
			// 
			// searchByToolStripMenuItem
			// 
			this->searchByToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->searchByNumberToolStripMenuItem,
					this->searchByDescriptionToolStripMenuItem, this->searchByCreationDateToolStripMenuItem, this->modifiedDateToolStripMenuItem,
					this->unfinishedImagesToolStripMenuItem
			});
			this->searchByToolStripMenuItem->Name = L"searchByToolStripMenuItem";
			this->searchByToolStripMenuItem->Size = System::Drawing::Size(234, 26);
			this->searchByToolStripMenuItem->Text = L"Search by...";
			// 
			// searchByNumberToolStripMenuItem
			// 
			this->searchByNumberToolStripMenuItem->Name = L"searchByNumberToolStripMenuItem";
			this->searchByNumberToolStripMenuItem->Size = System::Drawing::Size(214, 26);
			this->searchByNumberToolStripMenuItem->Text = L"Number";
			this->searchByNumberToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::searchByNumberToolStripMenuItem_Click);
			// 
			// searchByDescriptionToolStripMenuItem
			// 
			this->searchByDescriptionToolStripMenuItem->Name = L"searchByDescriptionToolStripMenuItem";
			this->searchByDescriptionToolStripMenuItem->Size = System::Drawing::Size(214, 26);
			this->searchByDescriptionToolStripMenuItem->Text = L"Description";
			this->searchByDescriptionToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::searchByDescriptionToolStripMenuItem_Click);
			// 
			// searchByCreationDateToolStripMenuItem
			// 
			this->searchByCreationDateToolStripMenuItem->Name = L"searchByCreationDateToolStripMenuItem";
			this->searchByCreationDateToolStripMenuItem->Size = System::Drawing::Size(214, 26);
			this->searchByCreationDateToolStripMenuItem->Text = L"Creation date";
			this->searchByCreationDateToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::searchByCreationDateToolStripMenuItem_Click);
			// 
			// modifiedDateToolStripMenuItem
			// 
			this->modifiedDateToolStripMenuItem->Name = L"modifiedDateToolStripMenuItem";
			this->modifiedDateToolStripMenuItem->Size = System::Drawing::Size(214, 26);
			this->modifiedDateToolStripMenuItem->Text = L"Modified date";
			this->modifiedDateToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::modifiedDateToolStripMenuItem_Click);
			// 
			// unfinishedImagesToolStripMenuItem
			// 
			this->unfinishedImagesToolStripMenuItem->Name = L"unfinishedImagesToolStripMenuItem";
			this->unfinishedImagesToolStripMenuItem->Size = System::Drawing::Size(214, 26);
			this->unfinishedImagesToolStripMenuItem->Text = L"Unfinished images";
			this->unfinishedImagesToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::unfinishedImagesToolStripMenuItem_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(147, 580);
			this->button1->Margin = System::Windows::Forms::Padding(4);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(123, 46);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Photo View Mode";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(645, 33);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(533, 492);
			this->pictureBox1->TabIndex = 4;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &Form1::pictureBox1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(645, 534);
			this->button2->Margin = System::Windows::Forms::Padding(4);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(37, 28);
			this->button2->TabIndex = 5;
			this->button2->Text = L"<<";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(1141, 534);
			this->button3->Margin = System::Windows::Forms::Padding(4);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(37, 28);
			this->button3->TabIndex = 6;
			this->button3->Text = L">>";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(787, 534);
			this->button4->Margin = System::Windows::Forms::Padding(4);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(100, 28);
			this->button4->TabIndex = 7;
			this->button4->Text = L"Prev";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(934, 534);
			this->button5->Margin = System::Windows::Forms::Padding(4);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(100, 28);
			this->button5->TabIndex = 8;
			this->button5->Text = L"Next";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(897, 534);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(28, 27);
			this->button6->TabIndex = 9;
			this->button6->Text = L"\?";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Form1::button6_Click);
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(1056, 581);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(123, 46);
			this->button7->TabIndex = 10;
			this->button7->Text = L"Change Mode";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Visible = false;
			this->button7->Click += gcnew System::EventHandler(this, &Form1::button7_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1213, 641);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->btnAddImgage);
			this->Controls->Add(this->listViewImages);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button6);
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Gallery";
			this->contextMenuStrip1->ResumeLayout(false);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
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
		System::Void searchByNumberToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void searchByDescriptionToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void searchByCreationDateToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void modifiedDateToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void unfinishedImagesToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {};

		System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void button2_Click(System::Object^ sender, System::EventArgs^ e); //first img
		System::Void button3_Click(System::Object^ sender, System::EventArgs^ e); //last img
		System::Void button4_Click(System::Object^ sender, System::EventArgs^ e); //prev img
		System::Void button5_Click(System::Object^ sender, System::EventArgs^ e); //next img
		System::Void button6_Click(System::Object^ sender, System::EventArgs^ e); //get info
		System::Void button7_Click(System::Object^ sender, System::EventArgs^ e); //change view mode

		System::Void listViewImages_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {};
};
}
