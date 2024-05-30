#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_BUTTON(10000, OnButtonClicked)

wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "FancyApp v1", wxPoint(600, 400), wxSize(1200, 900))
{
	btn = new wxButton * [nFieldWidth * nFieldHeight];
	wxGridSizer* grid = new wxGridSizer(nFieldWidth, nFieldHeight, 0, 0);

	nField = new int[nFieldWidth * nFieldHeight];

	wxFont font(25, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int i = 0; i < nFieldWidth; i++)
		for (int j = 0; j < nFieldHeight; j++)
		{
			btn[j * nFieldWidth + i] = new wxButton(this, 10000 + (j * nFieldWidth + i));
			btn[j * nFieldWidth + i]->SetFont(font);
			btn[j * nFieldWidth + i]->SetForegroundColour(wxColour(165, 165, 165));
			grid->Add(btn[j * nFieldWidth + i], 1, wxEXPAND | wxALL);

			btn[j * nFieldWidth + i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
			nField[j * nFieldWidth + i] = 0;
		}
	this->SetSizer(grid);
	this->SetBackgroundColour(wxColour(110, 110, 110));
	grid->Layout();
}

cMain::~cMain()
{
	delete[]btn;
}

void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	int x = (evt.GetId() - 10000) % nFieldWidth;
	int y = (evt.GetId() - 10000) / nFieldWidth;

	if (btnFirstClick)
	{
		int mines = 40;

		while (mines)
		{
			int rx = rand() % nFieldWidth;
			int ry = rand() % nFieldHeight;

			if (nField[ry * nFieldWidth + rx] == 0 && rx != x && ry != y)
			{
				nField[ry * nFieldWidth + rx] = -1;
				mines--;
			}
		}

		btnFirstClick = false;
	}

	btn[y * nFieldWidth + x]->Enable(false);

	if (nField[y * nFieldWidth + x] == -1)
	{
		wxMessageBox(" ! GAME OVER !");

		btnFirstClick = true;
		for (int i = 0; i < nFieldWidth; i++)
			for (int j = 0; j < nFieldHeight; j++)
			{
				nField[j * nFieldWidth + i] = 0;
				btn[j * nFieldWidth + i]->SetLabel("");
				btn[j * nFieldWidth + i]->Enable(true);
			}
	}
	else
	{
		int mines = 0;
		for (int i = -1; i < 2; i++)
			for (int j = -1; j < 2; j++)
			{
				if (x + i >= 0 && x + i < nFieldWidth && y + j >= 0 && y + j < nFieldHeight)
				{
					if (nField[(y + j) * nFieldWidth + (x + i)] == -1)
						mines++;
				}
			}
		if (mines > 0)
		{
			btn[y * nFieldWidth + x]->SetLabel(std::to_string(mines));
		}
	}
	evt.Skip();
}






