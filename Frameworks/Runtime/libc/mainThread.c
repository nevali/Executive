#include <Runtime/Runtime.h>

EXTERN_C int main(int argc, const char *argv[], const char *envp[]);

STATUS
mainThread(IThread *self)
{
	const char *args[] = { "Task", NULL };
	const char *env[] = { "HOSTNAME=localhost", NULL };
	int nargs = (sizeof(args) / sizeof(const char *)) - 1;

	return main(nargs, args, env);
}
