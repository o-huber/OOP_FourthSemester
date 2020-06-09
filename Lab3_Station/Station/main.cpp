#include "simulation.h"
#include "menu.h"

int main() {
    system("chcp 1251 & cls");
    Simulation sm(init_menu());
	loop_menu(sm);
}
