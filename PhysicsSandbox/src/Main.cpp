#include <Zefir.h>
#include <App.h>

int main(int argc, char* argv[])
{
	Zefir::Engine engine = Zefir::Engine();
	ZefirApp::PhysicsSandbox sandbox = ZefirApp::PhysicsSandbox();

	engine.Run(sandbox);

	return 0;
}