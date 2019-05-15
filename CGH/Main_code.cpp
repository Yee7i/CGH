#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>

#include <Windows.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fileapi.h>
#include <iomanip>
#include <complex>

const int N = 64;
const int p = 6;

void ft(double sign, std::complex<double> tab_SQ[N][N]);
void quant_a(double input[N][N], int quant);
void quant_p(double input[N][N], int quant);
std::string level_quant(int quant);

double error_psi(double tab_Ampl[N][N], double tab_Ampl_object[N][N]);
double SNR(double tab_Ampl_object[N][N], double tab_Ampl[N][N], double tab_Phase_object[N][N], double tab_Phase[N][N]);

std::string open()
{
	char filename[MAX_PATH];

	OPENFILENAME ofn;
	ZeroMemory(&filename, sizeof(filename));
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "Text Files\0*.txt\0Any File\0*.*\0";
	ofn.lpstrFile = filename;
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrTitle = "Choose a file";
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameA(&ofn))
	{
		std::cout << "Path to file: " << filename << "\n";
	}
	else
	{
		return 0;
	}

	return filename;
}

using namespace sf;
using namespace std;

bool click(Sprite check, RenderWindow& window)
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

int main()
{

	std::string path_input = "";

	RenderWindow window(VideoMode(600, 740), "Program functions definition", Style::None);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(true);

	window.setActive(true);

	bool quant_b = false;
	bool chart_bool = false;
	bool cutout_b = false;
	bool color_b = false;
	bool flag_input = false;

	std::string quant_val = "";

	Font font1;
	if (!font1.loadFromFile("gothic.ttf"))
	{
		cout << "Font loading error" << endl;
	}

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

	st_quant.setPosition(200, 200);
	sn_quant.setPosition(320, 200);

	Sprite st_chart;
	Sprite sn_chart;

	st_chart.setPosition(200, 330);
	sn_chart.setPosition(320, 330);

	Sprite st_cutout;
	Sprite sn_cutout;

	st_cutout.setPosition(200, 460);
	sn_cutout.setPosition(320, 460);

	Sprite s_ok;
	s_ok.setPosition(250, 650);

	Sprite s_file;
	s_file.setPosition(260, 20);
	
	Sprite s_black;
	s_black.setPosition(200, 580);
	
	Sprite s_white;
	s_white.setPosition(320, 580);

	Sprite s_blank;
	s_blank.setPosition(440, 200);

	Text text0;
	text0.setFont(font1);
	text0.setFillColor(Color::White);
	text0.setPosition(210, 150);

	Text text1;
	text1.setFont(font1);
	text1.setFillColor(Color::White);
	text1.setString("Quantization");
	text1.setPosition(210, 140);

	Text text2;
	text2.setFont(font1);
	text2.setFillColor(Color::White);
	text2.setString("Chart");
	text2.setPosition(265, 270);

	Text text3;
	text3.setFont(font1);
	text3.setFillColor(Color::White);
	text3.setString("Spectrum fragment erasing");
	text3.setPosition(100, 400);

	Text text4;
	text4.setFont(font1);
	text4.setFillColor(Color::White);
	text4.setString("Texture color");
	text4.setPosition(220, 530);

	Text quant_val_str;
	quant_val_str.setFont(font1);
	quant_val_str.setFillColor(Color::White);
	quant_val_str.setPosition(450, 214);
	quant_val_str.setCharacterSize(18);

	while (window.isOpen())
	{
		window.clear(Color::Black);

		text0.setString(path_input);
		text0.setCharacterSize(18);
		text0.setPosition(window.getSize().x / 2 - text0.getLocalBounds().width / 2, 90);

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

		if (chart_bool == false)
		{
			st_chart.setTexture(yes);
			sn_chart.setTexture(no_s);
		}
		if (chart_bool == true)
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

		if (flag_input == false)
		{
			s_blank.setTexture(blank);
		}
		if (flag_input == true)
		{
			s_blank.setTexture(blank_s);
		}

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
						chart_bool = true;
					}
					if (click(sn_chart, window) == true)
					{
						chart_bool = false;
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

						flag_input = false;

					}

					if (click(s_blank, window) == true)
					{

						flag_input = true;
				
					}
				}

				case Event::KeyPressed:
				{

					if (flag_input == true)
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
	
	bool chart_b = chart_bool;
	bool quantization_b = quant_b;

	if (color_b == true)
	{
		color_b = false;
	}
	else
	{
		color_b = true;
	}

	bool mode_b = color_b;
	bool cutout_alt_b = cutout_b;

	const double M_PI = 3.14159265358979323846;

	complex<double> numImaginary(0.0, 1.0);

	complex<double> tab_SQ[N][N];

	double tab_Ampl[N][N] = { 0 };
	double tab_Phase[N][N] = { 0 };

	double tab_Ampl_old[N][N] = { 0 };
	double tab_Phase_old[N][N] = { 0 };

	double tab_Ampl_object[N][N] = { 0 };
	double tab_Phase_object[N][N] = { 0 };

	int tab_objectA[N][N] = { 0 };	
	int tab_objectP[N][N] = { 0 };

	int i, j;

	double ampl_old = 0;
	double phase_old = 0;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			tab_SQ[i][j] = polar(0.0, 0.0);
		}
	}

	float pi = 3.14159265358979323846;

	int space = 0;
	int pspace = 0;
	int count_lin = 0;

	int slash_pos = 0;
	int slash_last_pos = 0;

	char* path;
	_get_pgmptr(&path);

	std::string curr_path = path;

	std::string in_line = "";

	std::string line;
	std::string bef;
	std::string stringchar;

	std::string name_target_phase;
	std::string name_target_ampl;

	std::string name_target_fold;
	std::string name_target_fold_object;
	std::string name_target_fold_spectrum;
	std::string name_target_fold_input;

	while (curr_path.find('\\', slash_last_pos) != -1) {

		slash_pos = curr_path.find('\\', slash_last_pos);

		slash_last_pos = slash_pos + 1;

	}

	int str_dl = curr_path.size();

	for (int i = slash_pos; i < str_dl; i++) {

		curr_path.pop_back();

	}

	name_target_fold = curr_path + "\\output";

	if (CreateDirectory(name_target_fold.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
		cout << "Created 'output' folder" << endl;
	}
	else
	{
		cout << "Couldn't create output folder" << endl;
	}

	name_target_fold_object = curr_path + "\\output\\image";

	if (CreateDirectory(name_target_fold_object.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
		cout << "Created 'image' folder" << endl;
	}
	else
	{
		cout << "Couldn't create output folder" << endl;
	}

	name_target_fold_spectrum = curr_path + "\\output\\spectrum";

	if (CreateDirectory(name_target_fold_spectrum.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
		cout << "Created 'spectrum' folder" << endl;
	}
	else
	{
		cout << "Couldn't create output folder" << endl;
	}

	name_target_fold_input = curr_path + "\\output\\input";

	if (CreateDirectory(name_target_fold_input.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
		cout << "Created 'input' folder" << endl;
	}
	else
	{
		cout << "Couldn't create output folder" << endl;
	}

	cout << "Copying input files... ";

	std::string name_target_input = name_target_fold + "\\input\\input.txt";

	CopyFile(path_input.c_str(), name_target_input.c_str(), false);

	cout << "Done." << endl;

	ifstream input(name_target_input.c_str(), ios::in);

	j = 0;

	while (getline(input, in_line))
	{
		int size = in_line.size();
		
		if (size > N) 
		{
			return 0;
		}

		for (int i = 0; i < size; i++)
		{
			if ((int)in_line[i] - 48 == 1)
			{
				tab_SQ[j][i] = polar(1.0, 0.0);
				tab_Ampl_object[j][i] = 1.0;
				tab_Phase_object[j][i] = 0.0;

				tab_objectA[j][i] = 1;
				tab_objectP[j][i] = 0;
			}
		}

		j++;

		if (j > N) 
		{
			return 0;
		}
	}

	input.close();

	ft(1.0, tab_SQ);

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			tab_Ampl[i][j] = abs(tab_SQ[i][j]);
			tab_Phase[i][j] = arg(tab_SQ[i][j]);
		}
	}

	cout << endl;

	int quant_level = 0;
	stringstream quant_sstream;

	quant_sstream << quant_val;
	quant_sstream >> quant_level;

	if (quantization_b == true)
	{
		quant_a(tab_Ampl, quant_level);
		quant_p(tab_Phase, quant_level);
	}

	if (cutout_alt_b == true)
	{
		int il_pol = 0;
		int index1, index2, index3, index4;

		cout << "How many fields to cut out?: ";
		cin >> il_pol;

		for (int i = 0; i < il_pol; i++)
		{
			cout << "Input the indexes of field " << i + 1 << ", please. "<<endl;
			cout << "Beginning - x axis: ";
			cin >> index2;
			cout << "Beginning - y axis: ";
			cin >> index1;
			cout << "End - x axis: ";
			cin >> index4;
			cout << "End - y axis: ";
			cin	>> index3;

			for (int i = index1; i <= index3; i++)
			{
				for (int j = index2; j <= index4; j++)
				{
					tab_Ampl[i][j] = 0.0;
				}
			}
		}
	}
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			tab_Ampl_old[i][j] = tab_Ampl[i][j];
			tab_Phase_old[i][j] = tab_Phase[i][j];
		}
	}


	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			tab_SQ[i][j] = polar(tab_Ampl[i][j],tab_Phase[i][j]);
		}
	}

	std::string path_out_SQ_1 = curr_path + "\\output\\spectrum\\tab_SQ_spectrum.txt";
	ofstream save1(path_out_SQ_1.c_str(), ios::out | ios::trunc);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{

			save1 << tab_SQ[i][j];
			save1 << " ";

		}

		save1 << endl;
	}

	save1.close();

	std::string path_out_AM_2 = curr_path + "\\output\\spectrum\\tab_AM_spectrum.txt";
	ofstream save2(path_out_AM_2.c_str(), ios::out | ios::trunc);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{

			save2 << tab_Ampl_old[i][j];
			save2 << " ";

		}

		save2 << endl;
	}

	save2.close();

	std::string path_out_PH_2 = curr_path + "\\output\\spectrum\\tab_PH_spectrum.txt";
	ofstream save3(path_out_PH_2.c_str(), ios::trunc | ios::out);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{

			save3 << tab_Phase_old[i][j];
			save3 << " ";

		}

		save3 << endl;
	}

	save3.close();
	
	ft(-1.0, tab_SQ);

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			tab_Ampl[i][j] = abs(tab_SQ[i][j]);
			tab_Phase[i][j] = arg(tab_SQ[i][j]);

			if (tab_Phase[i][j] < 0) {
				tab_Phase[i][j] += pi * 2;
			}
		}
	}
		
	double psi = error_psi(tab_Ampl_object, tab_Ampl);
	double snr = SNR(tab_Ampl_object, tab_Ampl, tab_Phase_object, tab_Phase);

	stringstream snr_sstream;
	stringstream psi_sstream;

	snr_sstream << scientific << snr;
	psi_sstream << setprecision(6) << fixed << psi;

	std::string snr_str;
	std::string psi_str;

	snr_sstream >> snr_str;
	psi_sstream >> psi_str;
	
	RenderTexture texture;
	RenderTexture texture2;
	RenderTexture texture3;
	RenderTexture texture4;

	texture.create(2908, 2980);
	texture2.create(2908, 2980);
	texture3.create(2908, 2980);
	texture4.create(2908, 2980);

	Font font;

	Text text_object;
	Text text_image;
	Text text_spectrum;
	Text text_hologram;

	if (!font.loadFromFile(curr_path+"\\gothic.ttf"))
	{
		cout<<"Error on loading font"<<endl;
	}

	text_object.setFont(font);
	text_image.setFont(font);
	text_spectrum.setFont(font);
	text_hologram.setFont(font);

	if (mode_b == true)
	{
		text_object.setFillColor(Color::White);
		text_spectrum.setFillColor(Color::White);
		text_image.setFillColor(Color::White);
	}
	else
	{
		text_object.setFillColor(Color::Black);
		text_spectrum.setFillColor(Color::Black);
		text_image.setFillColor(Color::Black);
	}

	text_hologram.setFillColor(Color::White);

	text_object.setPosition(20, texture.getSize().y - 60);
	text_image.setPosition(20, texture.getSize().y - 60);
	text_spectrum.setPosition(20, texture.getSize().y - 60);
	text_hologram.setPosition(20, texture.getSize().y - 60);

	RectangleShape chart(Vector2f(45, 45));
	chart.setOutlineColor(Color::Yellow);
	chart.setOutlineThickness(1);
	chart.setOrigin(chart.getSize().x / 2, chart.getSize().y / 2);

	RectangleShape disp_rectangle(Vector2f(15, 45));
	disp_rectangle.setOrigin(disp_rectangle.getSize().x / 2, disp_rectangle.getSize().y / 2);

	CircleShape dot(1.875);
	dot.setFillColor(Color::Red);
	dot.setPointCount(100);
	dot.setOrigin(1.875, 1.875);

	if (mode_b == true)
	{
		disp_rectangle.setFillColor(Color::White);
		chart.setFillColor(Color::Black);
	}
	else
	{
		disp_rectangle.setFillColor(Color::Black);
		chart.setFillColor(Color::White);
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			tab_Ampl_old[i][j] = pow(tab_Ampl_old[i][j], 2);
		}
	}

	bool flag1 = false;

	double max_amp = tab_Ampl_old[0][0];
	double max_amp2 = tab_Ampl[0][0];

	double total_amp = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			tab_Ampl_old[i][j] = log(tab_Ampl_old[i][j] + 1);
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (tab_Ampl_old[i][j] > max_amp)
			{
	
				max_amp = tab_Ampl_old[i][j];

			}

			total_amp += tab_Ampl_old[i][j];

		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (tab_Ampl[i][j] > max_amp2)
			{
				max_amp2 = tab_Ampl[i][j];
			}
		}
	}

	std::string text_image_comb = "Image - quantization " + level_quant(quant_level) + ", PSI - " + psi_str + ", SNR - " + snr_str + ".";
	std::string text_spectrum_comb = "Spectrum - quantization " + level_quant(quant_level) + ", maximum intensity - " + to_string(max_amp) + ", total intensity - " + to_string(total_amp) + ".";
	std::string text_holo_comb = "Hologram - quantization " + level_quant(quant_level) + ", maximum intensity - " + to_string(max_amp) + ", total intensity - " + to_string(total_amp) + ".";

	text_object.setString("Object");
	text_image.setString(text_image_comb);
	text_spectrum.setString(text_spectrum_comb);
	text_hologram.setString(text_holo_comb);

	if (mode_b == true)
	{
		texture.clear(Color::Black);
		texture2.clear(Color::Black);
		texture3.clear(Color::Black);
		texture4.clear(Color::Black);
	}
	else
	{
		texture.clear(Color::White);
		texture2.clear(Color::White);
		texture3.clear(Color::White);
		texture4.clear(Color::Black);
	}

	int offset_x = 30;
	int offset_y = 30;

	for (int f = 0; f < 4; f++)
	{

		offset_x = 30;
		offset_y = 30;

		for (int j = 0; j < N; j++)
		{

			for (int i = 0; i < N; i++)
			{

				float phase;
				float amplitude = 0;

				if (f == 0 || f == 3) 
				{
					phase = tab_Phase_old[j][i];
					amplitude = tab_Ampl_old[j][i];
				}
				else if (f == 1)
				{
					phase = tab_Phase[j][i];
					amplitude = tab_Ampl[j][i];
				}
				else
				{
					phase = tab_objectP[j][i];
					amplitude = tab_objectA[j][i];
				}

				if (phase > pi)
				{
					phase -= pi * 2;
				}

				float phase_p = (chart.getSize().x * 2 / 3) / (pi * 2) * phase;

				if (f == 0)
				{
					disp_rectangle.setSize(Vector2f(45 * amplitude / max_amp, 45 * amplitude / max_amp));
					disp_rectangle.setPosition((offset_x - 15) + (45 - disp_rectangle.getSize().x) / 2, offset_y + (45 - disp_rectangle.getSize().y) / 2);
				}

				if (f == 1)
				{
					disp_rectangle.setSize(Vector2f((45 * amplitude) / max_amp2, 45 * amplitude / max_amp2));
					disp_rectangle.setPosition((offset_x - 15) + (45 - disp_rectangle.getSize().x) / 2, offset_y + (45 - disp_rectangle.getSize().y) / 2);
				}

				if (f == 2)
				{
					disp_rectangle.setSize(Vector2f(45, 45 * amplitude));
					disp_rectangle.setPosition(offset_x - 15, offset_y);
				}

				if (f == 3)
				{
					disp_rectangle.setSize(Vector2f(15, (45 * amplitude) / max_amp));
					disp_rectangle.setPosition(offset_x + phase_p, offset_y + (45 - disp_rectangle.getSize().y) / 2);
					disp_rectangle.setFillColor(Color::White);
					chart.setFillColor(Color::Black);
				}

				chart.setPosition(offset_x, offset_y);
				dot.setPosition(offset_x, offset_y);

				if (f == 0)
				{
					texture.setActive(true);

					if (chart_b == true) {
						texture.draw(chart);
					}

					texture.draw(disp_rectangle);

					if (chart_b == true) {
						texture.draw(dot);
					}
				}
				else if (f == 1)
				{
					texture2.setActive(true);

					if (chart_b == true) {
						texture2.draw(chart);
					}

					texture2.draw(disp_rectangle);

					if (chart_b == true) {
						texture2.draw(dot);
					}
				}
				else if (f == 2)
				{
					texture3.setActive(true);

					if (chart_b == true)
					{
						texture3.draw(chart);
					}

					texture3.draw(disp_rectangle);

					if (chart_b == true)
					{
						texture3.draw(dot);
					}
				}
				else if (f == 3)
				{
					texture4.setActive(true);

					if (chart_b == true) {
						texture4.draw(chart);
					}

					texture4.draw(disp_rectangle);

					if (chart_b == true) {
						texture4.draw(dot);
					}
				}

				offset_x += 45;

			}

			offset_y += 45;
			offset_x = 30;

			texture.draw(text_spectrum);
			texture2.draw(text_image);
			texture3.draw(text_object);
			texture4.draw(text_hologram);

			texture.display();
			texture2.display();
			texture3.display();
			texture4.display();

		}
	}

		if (flag1 == false) 
		{
			texture.display();
			texture2.display();
			texture3.display();
			texture4.display();

			std::string path = curr_path + "\\output\\spectrum.png";
			std::string path2 = curr_path + "\\output\\image.png";
			std::string path3 = curr_path + "\\output\\object.png";
			std::string path4 = curr_path + "\\output\\hologram.png";

			cout << endl << "Saving images: " << endl;

			cout << "Spectrum... ";
			texture.getTexture().copyToImage().saveToFile(path);
			cout << "Done." << endl << "Image... ";
			texture2.getTexture().copyToImage().saveToFile(path2);
			cout << "Done." << endl << "Object... ";
			texture3.getTexture().copyToImage().saveToFile(path3);
			cout << "Done." << endl << "Hologram... ";
			texture4.getTexture().copyToImage().saveToFile(path4);
			cout << "Done." << endl;

			std::string path_out_SQ = curr_path + "\\output\\image\\tab_SQ_image.txt";
			ofstream save1_1(path_out_SQ.c_str(), ios::out | ios::trunc);

			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{

					save1_1 << tab_SQ[i][j];
					save1_1 << " ";

				}

				save1_1 << endl;
			}

			save1_1.close();

			std::string path_out_AM = curr_path + "\\output\\image\\tab_AM_image.txt";
			ofstream save2_1(path_out_AM.c_str(), ios::out | ios::trunc);

			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{

					save2_1 << tab_Ampl[i][j];
					save2_1 << " ";

				}

				save2_1 << endl;
			}

			save2_1.close();

			std::string path_out_PH = curr_path + "\\output\\image\\tab_PH_image.txt";
			ofstream save3_1(path_out_PH.c_str(), ios::trunc | ios::out);
			
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{

					save3_1 << tab_Phase[i][j];
					save3_1 << " ";

				}

				save3_1 << endl;
			}

			save3_1.close();

			cout << "Saving finished." << endl;

			flag1 = true;

		}
	
	system("pause");

	return 0;
}