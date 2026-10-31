#ifndef APPLICATION_H
#define APPLICATION_H

#include <stdint.h>
#include "view.h"
#include "model.h"
#include "controller.h"

#ifndef DEBUG
#define DEBUG 0
#endif

enum class ApplicationInitError : uint8_t {
	NONE,
	MODEL_INIT_FAILED
};

class Application {
private:
	Model model;
	Controller controller;
	View view;
public:
	Application();
	ApplicationInitError init();
	void run();
};

#endif