// Returns the name of the operating system, e.g. "Microsoft Windows 8.1 Enterprise"
const char* getOSName();

// Returns the version of the operating system, e.g. "6.3.9600"
const char* getOSVersion();

// Returns the number of seconds since last boot
const long int getUptime();

// Returns the name of a CPU, e.g. "Intel(R) Core(TM) i7-4770K CPU @ 3.50GHz"
const char* getCPUName(const int cpuID);

// Returns the number of installed CPUs
const int getCPUCount();

// Returns the number of physical cores of a CPU
const int getCoreCount(const int cpuID);

// Returns the current clock speed of a CPU. Will not be accurate in Windows.
const int getCPUSpeed(const int cpuID);

// Returns the percentage CPU utilisation.
// cpuID of -1 will return total for all CPUs (implies core of -1)
// core of -1 will return total for specified coreID
const int getCPULoad(const int cpuID, const int core);

// Returns the total amount of physical memory in bytes
const int getTotalRAM();

// Returns the available amount of physical memory in bytes
const int getFreeRAM();

// Returns the name of a GPU
const char* getGPUName(const int gpuID);

// Returns the number of installed GPUs
const int getGPUCount();

// Returns the hostname of the system
const char* getHostname();

// Returns the architecture of the system
const char* getArchitecture();