#include <Zefir.h>
#include <App.h>

int main(int argc, char* argv[])
{
	Zefir::Engine engine = Zefir::Engine();
	ZefirApp::SandboxApp sandbox = ZefirApp::SandboxApp();

	engine.Run(sandbox);

	return 0;
}