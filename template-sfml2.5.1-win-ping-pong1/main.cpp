#include <SFML/Graphics.hpp>
#include<iostream>
#include<sstream>

using namespace sf;
using namespace std;

int board[8][8] = { 0, 0, 0,  0,  0, 0, 0, 0,
					0, 0, 0,  0,  0, 0, 0, 0,
					0, 0, 0,  0,  0, 0, 0, 0,
					0, 0, 0, -1,  1, 0, 0, 0,
					0, 0, 0,  1, -1, 0, 0, 0,
					0, 0, 0,  0,  0, 0, 0, 0,
					0, 0, 0,  0,  0, 0, 0, 0,
					0, 0, 0,  0,  0, 0, 0, 0
};



class Person { // ����� ���������� �� ������������
protected:
	int number�hips;

public:
	Person()
	{
		number�hips = 0;
	}
	~Person() {};
	
	void getNumber(int a)
	{
		number�hips = a;
	}
};

class Fishka : protected Person {
private:

public:

	Image image;
	Texture texture;
	Sprite sprite;

	Fishka()
	{
		image.loadFromFile("Image/Fishka.png");
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setScale(0.4f, 0.4f);
	}
	~Fishka() {};

	

	void getColorF(int number)
	{
		if (number == 1)
		{
			sprite.setTextureRect(IntRect(239, 192, 96, 94));
			sprite.setColor(Color::White);
		}
		else if (number == -1)
		{
			sprite.setTextureRect(IntRect(139, 192, 96, 94));
			sprite.setColor(Color::White);
		}
		else
		{
			sprite.setColor(Color(0, 0, 0, 0));
		}
	}
	
	friend bool reset(int a, int stepy, int stepx, int dy, int dx);
	
	//bool getStep(int dx, int dy, int playerNum)
	//{
	//	int p;

	//	if (playerNum) p = 1;
	//	else p = -1;

	//	// board[dy - 1][dx - 1] == a  �������� �� �������� ����� � ����� �������    |
	//	// board[dy + 1][dx + 1] == a  �������� �� �������� ����� � ������ ������     \ �������� 
	//	// board[dy - 1][dx + 1] == a  �������� �� �������� ����� � ����� ������	  /		 �����
	//	// board[dy + 1][dx - 1] == a  �������� �� �������� ����� � ������ �������   |

	//	// board[dy][dx - 1] == a  �������� �� �������� ����� � �����   |
	//	// board[dy][dx + 1] == a  �������� �� �������� ����� � ������	 \   ��������
	//	// board[dy - 1][dx] == a  �������� �� �������� ����� � �������	 /		  ������
	//	// board[dy + 1][dx] == a  �������� �� �������� ����� � ������	|

	//	for(int i=-1; i <=1; i++)
	//		for (int j = -1; j <= 1; j++)
	//			reset(p, i, j, dy, dx);


	//}
};

bool reset(int a, int stepy, int stepx, int dy, int dx)
{
	
	if (board[dy + stepy][dx + stepx] == a * -1)
	{
		if (reset(a, stepy, stepx, dy + stepy, dx + stepx))
		{
			board[dy + stepy][dx + stepx] = a;
		}
	}
	else if (board[dy + stepy][dx + stepx] == 0)
	{
		return 0;
	}
	else if(board[dy + stepy][dx + stepx] == a)
	{
		return 1;
	}
	

};

int main()
{
	setlocale(LC_ALL, "Russian"); // ������� ��������� ���������� 

	Font font;
	font.loadFromFile("arkhip_font.ttf");
	Text text1("", font, 14);
	text1.setStyle(Text::Bold);

	text1.setFillColor(Color::White);
	text1.setPosition(50, 370);

	Text text2("", font, 14);
	text2.setStyle(Text::Bold);

	/*text.setString("�������� ���:");*/

	text2.setFillColor(Color::Black);
	text2.setPosition(200, 370);

	const int COUNT = 64; // ������������ ����� ����� 64

	RenderWindow window(VideoMode(346, 400), "Otello!");// ������, �������, ����������, �������� ������� ����� ����������

	Texture texture1;
	texture1.loadFromFile("Image/Doska.png");
	Sprite sprite1(texture1); //��� ����� ��� ����

	Fishka f[COUNT]; // ������� 64 �����
	Person person1, person2;

	int c = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			f[c].getColorF(board[i][j]);
			c++;
		}
	}


	int playerNum = 1;
	int dx = 0, dy = 0;
	int countWhite = 0, countBlack = 0;
	while (window.isOpen()) // ������� ���� ����������: �����������, ���� ������� ����
	{
		Vector2i pos = Mouse::getPosition(window); // ������� �����


		Event event;
		while (window.pollEvent(event)) // ������������ ������� � �����
		{
			if (event.type == Event::Closed) // ������������ ����� �� �������� � ����� ������� ����?
				window.close(); // ����� ��������� ���

			if (event.type == Event::MouseButtonPressed)// ��������� �������
			{
				if (event.key.code == Mouse::Left)      // ����� ������ ����
				{
					dx = pos.x / 39;
					dy = pos.y / 39;

					for (int i = -1; i <= 1; i++)
					{
						for (int j = -1; j <= 1; j++)
						{
							if (i != 0 || j != 0)
							{
								reset(playerNum, i, j, dy, dx);
							}
						}
					}
					if (playerNum == 1)
					{
						board[dy][dx] = 1;
						playerNum = -1;
					}
					else if(playerNum == -1)
					{
						board[dy][dx] = -1;
						playerNum = 1;
					}


					c = 0;
					countWhite = 0, countBlack = 0;
					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 8; j++)
						{
							f[c].getColorF(board[i][j]);
							c++;
							if (board[i][j] == 1) countWhite++;
							else if(board[i][j] == -1) countBlack++;

						}
					}

					/////////////����� ������ ��� ��������/////////////////
					/*cout << endl << "fp = " << (pos.y / 39) * 8 << endl;
					cout << "f = " << ((pos.y / 39) * 8 + (pos.x / 39)) << endl;

					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 8; j++)
						{
							cout << board[i][j] << " ";
						}
						cout << endl;
					}*/
				}
			}
		}
		ostringstream count1, count2;

		count1 << countWhite;
		text1.setString(L"����� 1:" + count1.str());//���������� ����. ���������� �����
		count2 << countBlack;
		text2.setString(L"����� 2:" + count2.str());//���������� ����. ���������� ������

		////////////����� �� �������/////////////////////////
		window.clear(Color::Green);
		window.draw(text1);
		window.draw(text2);
		window.draw(sprite1);

		for (int i = 0; i < 64; i++)
		{
			f[i].sprite.setPosition(17 + 39 * (i % 8), 17 + 39 * (i / 8));
			window.draw(f[i].sprite);
		}
		window.display();// ��������� ����
	}

	system("pause");
	return 0;
}
