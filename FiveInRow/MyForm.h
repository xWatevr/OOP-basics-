#pragma once
#include "GameLogic.h"

namespace FiveInRow {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			game = nullptr;

			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
			game = new Game();
			cellSize = 35;

			// відступ поля від лівого та верхнього краю вікна
			offsetX = 20;
			offsetY = 20;

			this->DoubleBuffered = true;
			this->Width = 620;
			this->Height = 650;
			this->Text = "П'ять у ряд";

			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseDown);
		}

	protected:
		
		~MyForm()
		{
			if (game != nullptr)
			{
				delete game;
				game = nullptr;
			}

			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		Game* game;
		int cellSize;
		int offsetX;
		int offsetY;

		System::ComponentModel::Container ^components;

		System::Void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
		{	//об'єкт для малювання
			Graphics^ g = e->Graphics;

			Pen^ gridPen = gcnew Pen(Color::Black, 1);

			const Board& board = game->getBoard();
			int size = board.getSize();

			// Малювання сітки
			for (int i = 0; i <= size; i++)
			{	// горизонтальні 
				g->DrawLine(
					gridPen,
					offsetX,
					offsetY + i * cellSize,
					offsetX + size * cellSize,
					offsetY + i * cellSize
				);

				// вертикальні
				g->DrawLine(
					gridPen,
					offsetX + i * cellSize,
					offsetY,
					offsetX + i * cellSize,
					offsetY + size * cellSize
				);
			}

			// Малювання фішок
			for (int row = 0; row < size; row++)
			{
				for (int col = 0; col < size; col++)
				{
					CellState cell = board.getCell(row, col);

					// переводимо координати клітинки в координати пікселів на екрані
					int x = offsetX + col * cellSize;
					int y = offsetY + row * cellSize;

					if (cell == CellState::X)
					{
						Pen^ xPen = gcnew Pen(Color::Blue, 3);

						g->DrawLine(
							xPen,
							x + 6,
							y + 6,
							x + cellSize - 6,
							y + cellSize - 6
						);

						g->DrawLine(
							xPen,
							x + cellSize - 6,
							y + 6,
							x + 6,
							y + cellSize - 6
						);
					}
					else if (cell == CellState::O)
					{
						Pen^ oPen = gcnew Pen(Color::Red, 3);

						g->DrawEllipse(
							oPen,
							x + 6,
							y + 6,
							cellSize - 12,
							cellSize - 12
						);
					}
				}
			}
		}

		System::Void MyForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
		{	
			// переводимо координату миші в клітинку
			int col = (e->X - offsetX) / cellSize;
			int row = (e->Y - offsetY) / cellSize;

			const Board& board = game->getBoard();

			if (!board.isInside(row, col))
			{
				return;
			}

			bool moveDone = game->makeMove(row, col);

			if (!moveDone)
			{
				return;
			}

			this->Invalidate();

			if (!game->isGameOver())
			{
				return;
			}

			String^ message;

			if (game->isDraw())
			{
				message = "Нічия!";
			}
			else if (game->getWinner() == CellState::X)
			{
				message = "Переміг гравець X!";
			}
			else
			{
				message = "Переміг гравець O!";
			}

			MessageBox::Show(message, "Кінець гри");
		}
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(833, 515);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
