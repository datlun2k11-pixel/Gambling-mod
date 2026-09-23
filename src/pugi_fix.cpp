// Dummy fix for pugi::xml_node destructor linker error
// Provide symbols via inline assembly without including headers to avoid redefinition
// This satisfies the linker when bindings are patched to remove the destructor.

#if defined(_WIN32) || defined(_MSC_VER) || defined(GEODE_IS_WINDOWS)
// MSVC mangling for pugi::xml_node::~xml_node is ??1xml_node@pugi@@QEAA@XZ
// Use inline assembly to define it
__asm__(".globl \"??1xml_node@pugi@@QEAA@XZ\"\n\"??1xml_node@pugi@@QEAA@XZ\":\n\tret\n");
#else
// Itanium ABI
__asm__(".globl _ZN4pugi8xml_nodeD1Ev\n_ZN4pugi8xml_nodeD1Ev:\n\tret\n");
__asm__(".globl _ZN4pugi8xml_nodeD2Ev\n_ZN4pugi8xml_nodeD2Ev:\n\tret\n");
#endif
// Dummy function to ensure file is not empty for compiler
void pugi_fix_dummy() {}
