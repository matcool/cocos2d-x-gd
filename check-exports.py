import subprocess

# symbols that gd imports from cocos, at least in 2.2074
with open("gd-cocos-imports.txt") as file:
    gd_symbols = set(x.strip() for x in file.readlines())

# symbols that libExtension.dll imports
with open("gd-extension-imports.txt") as file:
    gd_symbols = gd_symbols.union(set(x.strip() for x in file.readlines()))

# symbols that we export
output = subprocess.run(["dumpbin", "/exports", "build/libcocos2d.dll", "/nologo"], capture_output=True).stdout.decode("utf-8")

symbols = output.splitlines()[16:-11]
symbols = set(x.split()[3] for x in symbols)

missing = list(gd_symbols - symbols)

def get_method_name(symbol):
    names = symbol.lstrip('?').split("@@", 1)[0].split("@")
    names.reverse()
    return "::".join(names)

missing.sort(key=get_method_name)

demangled = subprocess.run(["demumble"], input='\n'.join(missing).encode("utf-8"), capture_output=True).stdout.decode("utf-8").splitlines()
demangled = [
    x.strip()
        .replace(" __cdecl", "")
        .replace("class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char>>", "std::string")
    for x in demangled
]

print('\n'.join(demangled))
print(f"\nMissing methods: {len(missing)}")