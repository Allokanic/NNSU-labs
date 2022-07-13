#include "menu.h"

Menu::MenuItem::MenuItem() {
	type = -1;
	function = nullptr;
	inner_menu = nullptr;
}

Menu::Menu() {
	prev = nullptr;

	posX = posY = 0;

	major_back_color = BACK_COLOR::BLACK;
	major_text_color = TEXT_COLOR::TLIGHT_PURPLE;
	minor_back_color = BACK_COLOR::BLACK;
	minor_text_color = TEXT_COLOR::TPURPLE;
	main_background = BACK_COLOR::BLACK;
	center = false;
	
	HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD crd = { static_cast<short>(width), static_cast<short>(height) };
	SMALL_RECT src = { 0, 0, crd.X - 1, crd.Y - 1 };
	SetConsoleWindowInfo(out_handle, true, &src);
	SetConsoleScreenBufferSize(out_handle, crd);

	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(fontInfo);
	GetCurrentConsoleFontEx(out_handle, TRUE, &fontInfo);
	wcscpy_s(fontInfo.FaceName, L"Cascadia Code Semibold"); 
	fontInfo.dwFontSize.Y = font;
	SetCurrentConsoleFontEx(out_handle, TRUE, &fontInfo);
}

Menu::Menu(Menu *prev_object) {
	prev = prev_object;

	posX = posY = 0;

	major_back_color = BACK_COLOR::BLACK;
	major_text_color = TEXT_COLOR::TLIGHT_PURPLE;
	minor_back_color = BACK_COLOR::BLACK;
	minor_text_color = TEXT_COLOR::TPURPLE;
	main_background = BACK_COLOR::BLACK;
	center = false;

	HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD crd = { static_cast<short>(width), static_cast<short>(height) };
	SMALL_RECT src = { 0, 0, crd.X - 1, crd.Y - 1 };
	SetConsoleWindowInfo(out_handle, true, &src);
	SetConsoleScreenBufferSize(out_handle, crd);

	CONSOLE_FONT_INFOEX fontInfo;
	fontInfo.cbSize = sizeof(fontInfo);
	GetCurrentConsoleFontEx(out_handle, TRUE, &fontInfo);
	wcscpy_s(fontInfo.FaceName, L"Cascadia Code Semibold");
	fontInfo.dwFontSize.Y = font;
	SetCurrentConsoleFontEx(out_handle, TRUE, &fontInfo);
}

Menu Menu::operator =(const Menu& other) {
	major_back_color = other.major_back_color;
	major_text_color = other.major_text_color;
	major_index = other.major_index;
	minor_back_color = other.minor_back_color;
	minor_text_color = other.minor_text_color;
	center = other.center;
	posX = other.posX;
	posY = other.posY;
	cursor_size = other.cursor_size;
	prev = other.prev;
	menu_header = other.menu_header;
	name_holder = other.name_holder;
	object_holder = other.object_holder;
	return *this;
}

void Menu::set_center(bool value) {
	center = value;
}

void Menu::intitalize_data_list(const std::vector<std::string>& _data) {
	name_holder = _data;
	object_holder.resize(_data.size());
}

void Menu::set_menu_position(const int& coordX, const int& coordY) {
	posX = coordX;
	posY = coordY;
	HANDLE menu_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(menu_handle, {posX, posY});
}

void Menu::set_menu_header(const std::string& header) {
	SetConsoleTitleA(header.c_str());
}

void Menu::make_cursor_visible() {
	HANDLE menu_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cur_cursor;
	GetConsoleCursorInfo(menu_handle, &cur_cursor);
	cur_cursor.bVisible = true;
	SetConsoleCursorInfo(menu_handle, &cur_cursor);
}
void Menu::make_cursor_invisible() {
	HANDLE menu_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cur_cursor;
	GetConsoleCursorInfo(menu_handle, &cur_cursor);
	cur_cursor.bVisible = false;
	SetConsoleCursorInfo(menu_handle, &cur_cursor);
}

void Menu::set_major_text_color(const WORD color) {
	major_text_color = color;
}
void Menu::set_minor_text_color(const WORD color) {
	minor_text_color = color;
}
void Menu::set_major_back_color(const WORD color) {
	major_back_color = color;
}
void Menu::set_minor_back_color(const WORD color) {
	minor_back_color = color;
}

void Menu::add_func_to_list(const int index, void (*_function)()) {
	object_holder[index].type = ITEM_TYPE::FUNCTION;
	object_holder[index].function = _function;
}
void Menu::add_menu_to_list(const int index, Menu *inner) {
	object_holder[index].type = ITEM_TYPE::MENU;
	object_holder[index].inner_menu = inner;
}

void Menu::reprint_menu() {
	HANDLE menu_handler = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(menu_handler, main_background);
	system("cls");

	SetConsoleTextAttribute(menu_handler, minor_back_color | minor_text_color);

	int i = 0;
	for (auto el : name_holder) {
		if (i == major_index) {
			SetConsoleTextAttribute(menu_handler, major_back_color | major_text_color);
		}
		std::cout << el << '\n';
		if (i == major_index) {
			SetConsoleTextAttribute(menu_handler, minor_back_color | minor_text_color);
		}
		i++;
	}
}

void Menu::reprint_menu_by_center() {
	HANDLE menu_handler = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(menu_handler, main_background);
	system("cls");

	SetConsoleTextAttribute(menu_handler, minor_back_color | minor_text_color);

	short int startY = height / 2 - name_holder.size() / 2 - 1;

	int i = 0;
	for (auto el : name_holder) {
		short int startX = width / 2 - el.size() / 2 - 1;
		SetConsoleCursorPosition(menu_handler, { startX, startY });
		if (i == major_index) {
			SetConsoleTextAttribute(menu_handler, major_text_color | major_back_color);
		}
		std::cout << el << '\n';
		if (i == major_index) {
			SetConsoleTextAttribute(menu_handler, minor_text_color | minor_back_color);
		}
		i++;
		startY++;
	}
}

void Menu::MenuItem::open_item() {
	if (type == ITEM_TYPE::MENU) 
		inner_menu->launch();
	else 
		function();
}

void Menu::call_reprint_manager() {
	if (center) reprint_menu_by_center();
	else reprint_menu();
}

void Menu::launch() {
	call_reprint_manager();

	while (1) {
		char button;
		button = _getch();
		if (button == 13) {
			object_holder[major_index].open_item();
		}
		else if (button == 27) {
			HANDLE menu_handler = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(menu_handler, 0 
				| FOREGROUND_RED 
				| FOREGROUND_GREEN 
				| FOREGROUND_BLUE 
				| FOREGROUND_INTENSITY);

			system("cls");
			break;
		}
		else if (button == -32) {
			button = _getch();
			switch (button) {
			case 72:
				if (major_index) major_index--;
				break;
			case 80:
				if (major_index < name_holder.size() - 1) major_index++;
				break;
			}
			call_reprint_manager();
		}
	}
}