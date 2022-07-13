#include <functional>
#include <vector>
#include <string>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <list>
	
enum TEXT_COLOR {
	TBLACK = 0,
	TGREY = FOREGROUND_INTENSITY,
	TLIGHT_GREY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	TWHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	TBLUE = FOREGROUND_BLUE,
	TGREEN = FOREGROUND_GREEN, 
	TCYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
	TRED = FOREGROUND_RED,
	TPURPLE = FOREGROUND_RED | FOREGROUND_BLUE,
	TLIGHT_BLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	TLIGHT_GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	TLIGHT_CYAN = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	TLIGHT_RED = FOREGROUND_RED | FOREGROUND_INTENSITY,
	TLIGHT_PURPLE = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	TORANGE = FOREGROUND_RED | FOREGROUND_GREEN,
	TYELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
};

enum BACK_COLOR {
	BLACK = 0,
	GREY = BACKGROUND_INTENSITY, 
	LIGHT_GREY = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
	WHITE = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
	BLUE = BACKGROUND_BLUE,
	GREEN = BACKGROUND_GREEN,
	CYAN = BACKGROUND_GREEN | BACKGROUND_BLUE,
	RED = BACKGROUND_RED,
	PURPLE = BACKGROUND_RED | BACKGROUND_BLUE,
	LIGHT_BLUE = BACKGROUND_BLUE | BACKGROUND_INTENSITY,
	LIGHT_GREEN = BACKGROUND_GREEN | BACKGROUND_INTENSITY,
	LIGHT_CYAN = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
	LIGHT_RED = BACKGROUND_RED | BACKGROUND_INTENSITY,
	LIGHT_PURPLE = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
	ORANGE = BACKGROUND_RED | BACKGROUND_GREEN,
	YELLOW = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY
};

enum ITEM_TYPE {
	FUNCTION,
	MENU
};

class Menu {
public:
	Menu();
	Menu(Menu* prev);
	~Menu() = default;

	Menu operator =(const Menu& other);

	void launch();
	void set_menu_position(const int& coordX, const int& coordY);
	void set_menu_header(const std::string& header);
	void make_cursor_visible();
	void make_cursor_invisible();
	void set_major_text_color(const WORD color);
	void set_minor_text_color(const WORD color);
	void set_major_back_color(const WORD color);
	void set_minor_back_color(const WORD color);
	void intitalize_data_list(const std::vector<std::string>& _data);
	void set_center(bool value);
	void add_func_to_list(const int index, void (*function)());
	void add_menu_to_list(const int index, Menu *inner); 

private:
	void call_reprint_manager();
	void reprint_menu();
	void reprint_menu_by_center();

	short int posX, posY, cursor_size = 25;
	Menu* prev;
	int height = 25, width = 80, font = 25;
	WORD minor_text_color, major_text_color, minor_back_color, major_back_color, main_background;
	int major_index = 0;
	bool center;
	
	class MenuItem {
	public:
		MenuItem();
		~MenuItem() = default;
		void open_item();

		int type;
		Menu *inner_menu;
		void (*function)();
	};

	std::vector<std::string> name_holder;
	std::vector<MenuItem> object_holder;
	std::string menu_header;
};