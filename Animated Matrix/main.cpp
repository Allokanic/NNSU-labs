#include "menu.h"

int main() {
	Menu main_menu;
	main_menu.set_center(true);
	main_menu.make_cursor_invisible();
	setlocale(0, "");
	std::vector<std::string> base = {
		"Создать новую матрицу",
		"Показать текущую матрицу",
		/*"Найти определитель",
		"Умножить на число",
		"Умножить на другую матрицу",
		"Сложить с другой матрицей",
		"Вычесть другую матрицу",
		"Транспонировать",
		"Найти обратную матрицу"*/
	};
	main_menu.intitalize_data_list(base);
	main_menu.add_func_to_list(0, &Constructor::get_matrix);
	/*main_menu.add_func_to_list(0, Matrix::print);
	main_menu.add_func_to_list(0, Matrix::get_determinant);
	main_menu.add_func_to_list(0, Matrix::multiplicate_on_number);
	main_menu.add_func_to_list(0, Matrix::multiplicate_on_matrix);
	main_menu.add_func_to_list(0, Matrix::add_matrix);
	main_menu.add_func_to_list(0, Matrix::substract_matrix);
	main_menu.add_func_to_list(0, Matrix::transpose);
	main_menu.add_func_to_list(0, Matrix::inverse);*/
	main_menu.launch();
	return 0;
}