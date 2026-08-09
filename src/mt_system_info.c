#include <mt_system_info.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#elif defined(__linux__) || defined(__gnu_linux__)
#include <unistd.h>
#elif defined(__APPLE__) && defined(__MACH__)
#include <sys/sysctl.h>
#endif

int mt_cpu_core_size(void)
{
#if defined(_WIN32) || defined(_WIN64)
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	return sysinfo.dwNumberOfProcessors;
#elif defined(__linux__) || defined(__gnu_linux__)
	return sysconf(_SC_NPROCESSORS_ONLN);
#elif defined(__APPLE__) && defined(__MACH__)
	int mib[2];
	int num_cores = 0;
	size_t len = sizeof(num_cores);
	mib[0] = CTL_HW;
	mib[1] = HW_NCPU;
	if (sysctl(mib, 2, &num_cores, &len, NULL, 0) == 0) {
		return num_cores;
	}
	return 1; // Fallback
#else
	return 1; // Unsupported platform fallback
#endif
}
