#include"Application.h"
#define var(T) std::unique_ptr<T>
#define mvar(T) std::make_unique<T>
// todo: - check build output , why all that stuff is there. // for cube i guess.

int main() {
	var(Application) app = mvar(Application)() ;
	app->run();
	return 0;
}