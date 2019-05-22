#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>

#include <Windows.h>
#include <iostream>
#include <string>
#include <fileapi.h>

#include "maindec.h"

using namespace sf;

std::string open()
{
	char filename[MAX_PATH];

	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "Text Files\0*.txt\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Choose a file";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameA(&ofn))
	{
		std::cout << "Path to file: " << filename << std::endl;
	}
	else
	{
		std::cout << "You didn't make a choice." << std::endl;
	}

	return filename;
}

bool click(Sprite check, RenderWindow &window)
{
	Vector2f mouse_pos = window.mapPixelToCoords(Mouse::getPosition(window));

	FloatRect bounds = check.getGlobalBounds();

	if (bounds.contains(mouse_pos))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool click_rect(RectangleShape check, RenderWindow &window)
{
	Vector2f mouse_pos = window.mapPixelToCoords(Mouse::getPosition(window));

	FloatRect bounds = check.getGlobalBounds();

	if (bounds.contains(mouse_pos))
	{
		return true;
	}
	else
	{
		return false;
	}
}

output_options gui()
{

	std::string path_input = "";
	bool quant_b = false;
	bool chart_b = false;
	bool cutout_b = false;
	bool color_b = false;
	bool flag_in = false;
	bool flag_exit = false;

	bool shorten_once = false;

	double button_size_x;

	double window_width = VideoMode::getDesktopMode().width;
	double window_height = VideoMode::getDesktopMode().height;

	double scale_width = window_width / 1366;
	double scale_height = window_height / 768;

	cout << 1024 / 1366 << endl;
	cout << VideoMode::getDesktopMode().width << " " << VideoMode::getDesktopMode().height << endl;
	cout << scale_width << " " << scale_height << endl;

	auto mode = VideoMode::getDesktopMode();
	mode.height += 1;
	RenderWindow window(mode, "Program functions definition", Style::None);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(true);

	window.setActive(true);

	std::string quant_val = "";

	Font font1;
	if (!font1.loadFromFile("gothic.ttf"))
	{
		cout << "Font loading error" << endl;
	}

	RectangleShape exit(Vector2f(40, 40));
	exit.setFillColor(Color::Black);
	exit.setOutlineColor(Color::White);
	exit.setOutlineThickness(2);
	exit.setPosition(window.getSize().x - exit.getSize().x - exit.getOutlineThickness(), 0 + exit.getOutlineThickness());

	Texture ok_button;
	ok_button.loadFromFile("textures\\ok.png");

	Texture yes;
	yes.loadFromFile("textures\\yes.png");

	Texture no;
	no.loadFromFile("textures\\no.png");

	Texture yes_s;
	yes_s.loadFromFile("textures\\yes_s.png");

	Texture no_s;
	no_s.loadFromFile("textures\\no_s.png");

	Texture file_texture;
	file_texture.loadFromFile("textures\\file.png");

	Texture white;
	white.loadFromFile("textures\\white.png");

	Texture black;
	black.loadFromFile("textures\\black.png");

	Texture white_s;
	white_s.loadFromFile("textures\\white_s.png");

	Texture black_s;
	black_s.loadFromFile("textures\\black_s.png");

	Texture blank;
	blank.loadFromFile("textures\\blank.png");

	Texture blank_s;
	blank_s.loadFromFile("textures\\blank_s.png");

	button_size_x = blank.getSize().x;

	yes.setSmooth(true);
	yes.setRepeated(false);

	yes_s.setSmooth(true);
	yes_s.setRepeated(false);

	no.setSmooth(true);
	no.setRepeated(false);

	no_s.setSmooth(true);
	no_s.setRepeated(false);

	file_texture.setSmooth(true);
	file_texture.setRepeated(false);

	ok_button.setSmooth(true);
	ok_button.setRepeated(false);

	white.setSmooth(true);
	white.setRepeated(false);

	white_s.setSmooth(true);
	white_s.setRepeated(false);

	black.setSmooth(true);
	black.setRepeated(false);

	black_s.setSmooth(true);
	black_s.setRepeated(false);

	blank.setSmooth(true);
	blank.setRepeated(false);

	blank_s.setSmooth(true);
	blank_s.setRepeated(false);

	Sprite st_quant;
	Sprite sn_quant;

	st_quant.setPosition((window_width / 4) - 30 - button_size_x, 6 * (window_height / 8));
	sn_quant.setPosition((window_width / 4) + 30, 6 * (window_height / 8));

	Sprite st_chart;
	Sprite sn_chart;

	st_chart.setPosition((window_width / 4) - 30 - button_size_x, 4 * (window_height / 8));
	sn_chart.setPosition((window_width / 4) + 20, 4 * (window_height / 8));

	Sprite st_cutout;
	Sprite sn_cutout;

	st_cutout.setPosition(((window_width / 2) + (window_width / 4)) - 30 - button_size_x, 4 * (window_height / 8));
	sn_cutout.setPosition(((window_width / 2) + (window_width / 4)) + 30, 4 * (window_height / 8));

	Sprite s_ok;
	s_ok.setPosition(window.getSize().x - ok_button.getSize().x, window.getSize().y - ok_button.getSize().y - 1);

	Sprite s_file;
	s_file.setPosition(window_width / 2 - file_texture.getSize().x / 2, (window_height / 8));

	Sprite s_black;
	s_black.setPosition(((window_width / 2) + (window_width / 4)) - 30 - button_size_x, 6 * (window_height / 8));

	Sprite s_white;
	s_white.setPosition(((window_width / 2) + (window_width / 4)) + 30, 6 * (window_height / 8));

	Sprite s_blank;
	s_blank.setPosition((window_width / 4) - button_size_x / 2, 7 * (window_height / 8));

	Text title;
	title.setFont(font1);
	title.setFillColor(Color::White);

	Text text0;
	text0.setFont(font1);
	text0.setFillColor(Color::White);
	text0.setPosition(210, 150);

	Text text1;
	text1.setFont(font1);
	text1.setFillColor(Color::White);
	text1.setString("Quantization");
	text1.setPosition(window_width / 4 - text1.getLocalBounds().width / 2, 5 * (window_height / 8));
	text1.setCharacterSize(30 * scale_height);

	Text text2;
	text2.setFont(font1);
	text2.setFillColor(Color::White);
	text2.setString("Chart");
	text2.setPosition(window_width / 4 - text2.getLocalBounds().width / 2, 3 * (window_height / 8));
	text2.setCharacterSize(30 * scale_height);

	Text text3;
	text3.setFont(font1);
	text3.setFillColor(Color::White);
	text3.setString("Spectrum fragment erasing");
	text3.setPosition((window_width / 2 + window_width / 4) - text3.getLocalBounds().width / 2, 3 * (window_height / 8));
	text3.setCharacterSize(30 * scale_height);

	Text text4;
	text4.setFont(font1);
	text4.setFillColor(Color::White);
	text4.setString("Texture color");
	text4.setPosition((window_width / 2 + window_width / 4) - text4.getLocalBounds().width / 2, 5 * (window_height / 8));
	text4.setCharacterSize(30 * scale_height);

	Text quant_val_str;
	quant_val_str.setFont(font1);
	quant_val_str.setFillColor(Color::White);
	quant_val_str.setPosition(450, 214);
	quant_val_str.setCharacterSize(18);

	while (window.isOpen())
	{
		window.clear(Color::Black);

		title.setCharacterSize((int)(36 * scale_height));
		cout << title.getCharacterSize() << endl;
		title.setPosition(window.getSize().x / 2 - title.getLocalBounds().width / 2, 10);
		title.setString("Welcome to CGH!");

		if (path_input == "") 
		{
			text0.setString("File path - not selected yet." + path_input);
		}
		else
		{
			int last_slash = 0;
			int last_slash2 = 0;
			int size = path_input.size();

			if (size >= 75 && shorten_once == false)
			{
				for (int i = 0; i < 4; i++)
				{
					last_slash = path_input.find("\\", last_slash + 1);
				}

				for (int i = 0; i < 7; i++)
				{
					last_slash2 = path_input.find("\\", last_slash2 + 1);
				}

				path_input.erase(last_slash + 1, last_slash2 - last_slash - 1);
				path_input.insert(last_slash + 1, "[...]");

				shorten_once = true;
			}

			cout << "4th slash = " << last_slash << ". 7th slash = " << last_slash2 << endl;

			text0.setString("File path - " + path_input);
		}

		text0.setCharacterSize(24 * scale_height);
		text0.setPosition(window.getSize().x / 2 - text0.getLocalBounds().width / 2, 2 * (window_height / 8));

		quant_val_str.setString(quant_val);

		s_ok.setTexture(ok_button);
		s_file.setTexture(file_texture);

		if (quant_b == false)
		{
			st_quant.setTexture(yes);
			sn_quant.setTexture(no_s);
		}
		if (quant_b == true)
		{
			st_quant.setTexture(yes_s);
			sn_quant.setTexture(no);
		}

		if (chart_b == false)
		{
			st_chart.setTexture(yes);
			sn_chart.setTexture(no_s);
		}
		if (chart_b == true)
		{
			st_chart.setTexture(yes_s);
			sn_chart.setTexture(no);
		}

		if (cutout_b == false)
		{
			st_cutout.setTexture(yes);
			sn_cutout.setTexture(no_s);
		}
		if (cutout_b == true)
		{
			st_cutout.setTexture(yes_s);
			sn_cutout.setTexture(no);
		}

		if (color_b == false)
		{
			s_black.setTexture(black_s);
			s_white.setTexture(white);
		}
		if (color_b == true)
		{
			s_black.setTexture(black);
			s_white.setTexture(white_s);
		}

		if (flag_in == false)
		{
			s_blank.setTexture(blank);
		}
		if (flag_in == true)
		{
			s_blank.setTexture(blank_s);
		}

		window.draw(title);
		window.draw(text1);
		window.draw(text2);
		window.draw(text3);
		window.draw(text4);

		window.draw(st_quant);
		window.draw(sn_quant);

		window.draw(st_chart);
		window.draw(sn_chart);

		window.draw(st_cutout);
		window.draw(sn_cutout);

		window.draw(s_black);
		window.draw(s_white);

		window.draw(s_ok);
		window.draw(s_file);

		window.draw(text0);

		window.draw(exit);

		if (quant_b == true)
		{
			window.draw(s_blank);
			window.draw(quant_val_str);
		}

		Event ev;

		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case Event::MouseButtonPressed:
			{

				if (click(st_quant, window) == true)
				{
					quant_b = true;
				}
				if (click(sn_quant, window) == true)
				{
					quant_b = false;
				}

				if (click(st_cutout, window) == true)
				{
					cutout_b = true;
				}
				if (click(sn_cutout, window) == true)
				{
					cutout_b = false;
				}

				if (click(st_chart, window) == true)
				{
					chart_b = true;
				}
				if (click(sn_chart, window) == true)
				{
					chart_b = false;
				}

				if (click(s_white, window) == true)
				{
					color_b = true;
				}
				if (click(s_black, window) == true)
				{
					color_b = false;
				}
			
				if (click(s_ok, window) == true)
				{
					if (path_input != "")
					{
						window.close();
					}
				}
			
				if (click(s_file, window) == true)
				{
					path_input = open();
				}

				if (click(s_blank, window) == false)
				{
					flag_in = false;
				}

				if (click(s_blank, window) == true)
				{
					flag_in = true;
				}

				if (click_rect(exit, window) == true)
				{
					window.close();
					flag_exit = true;
				}
			}

			case Event::KeyPressed:
			{

				if (flag_in == true)
				{

					if (quant_val.size() < 8)
					{

						if (Keyboard::isKeyPressed(Keyboard::Num1))
						{
							quant_val.append("1");
						}
						if (Keyboard::isKeyPressed(Keyboard::Num2))
						{
							quant_val.append("2");
						}
						if (Keyboard::isKeyPressed(Keyboard::Num3))
						{
							quant_val.append("3");
						}
						if (Keyboard::isKeyPressed(Keyboard::Num4))
						{
							quant_val.append("4");
						}
						if (Keyboard::isKeyPressed(Keyboard::Num5))
						{
							quant_val.append("5");
						}
						if (Keyboard::isKeyPressed(Keyboard::Num6))
						{
							quant_val.append("6");
						}
						if (Keyboard::isKeyPressed(Keyboard::Num7))
						{
							quant_val.append("7");
						}
						if (Keyboard::isKeyPressed(Keyboard::Num8))
						{
							quant_val.append("8");
						}
						if (Keyboard::isKeyPressed(Keyboard::Num9))
						{
							quant_val.append("9");
						}
						if (Keyboard::isKeyPressed(Keyboard::Num0))
						{
							quant_val.append("0");
						}
					}

					if (Keyboard::isKeyPressed(Keyboard::BackSpace))
					{
						if (quant_val.size() > 0)
						{
							quant_val.pop_back();
						}
					}
				}
			}
			}
		}

		window.display();
	}

	return {
		path_input,
		quant_val,
		quant_b,
		chart_b,
		cutout_b,
		color_b,
		flag_in,
		flag_exit
	};

}