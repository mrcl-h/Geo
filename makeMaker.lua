--local mainHandle = io.popen ("g++ -MM main.cpp")
--local sourceHandle = io.popen ("g++ -MM source/*.cpp")
local sourceFiles = io.popen ("ls source"):read("a")

local cppFiles = {n=0}
for i in string.gmatch (sourceFiles, "%f[%a]%a*%.cpp") do
    cppFiles[cppFiles.n+1] = i
    cppFiles.n = cppFiles.n+1
end

local mf = io.open ("Makefile", "w")
mf:write ("CFLAGS = -g -Wshadow -std=c++11 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept  -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused -Wold-style-cast -Wformat-nonliteral -Wpointer-arith -Winline -Wwrite-strings -Wno-unused-parameter -Wfloat-equal -fsanitize=undefined -fsanitize=unreachable -fsanitize=leak -fsanitize=enum -fsanitize=builtin -fsanitize=shift-exponent -fsanitize=pointer-compare -fsanitize=pointer-subtract -fsanitize=address -Werror\n\n")

mf:write ("OBJECTS = obj/main.o")

for _, i in ipairs (cppFiles) do
    mf:write (" obj/" .. string.gsub (i, "%.cpp", ".o"))
end


mf:write ("\n\n")
mf:write ("bin/app: $(OBJECTS)\n\tg++ $(OBJECTS) -o bin/app -lsfml-window -lsfml-system -lsfml-graphics $(CFLAGS)\n\n")

mf:write ("obj/")
mf:write ((string.gsub(io.popen("g++ -MM main.cpp"):read("a"), "\n%s*$", "")))
mf:write (" | obj\n")
mf:write ("\tg++ main.cpp -o obj/main.o -c $(CFLAGS)")
mf:write ("\n\n")

for _, i in ipairs (cppFiles) do
    mf:write ("obj/")
    mf:write ((string.gsub(io.popen("g++ -MM source/" .. i):read("a"), "\n%s*$", "")))
    mf:write (" | obj\n")
    mf:write ("\tg++ source/" .. i .. " -o obj/" .. string.gsub (i, "%.cpp", ".o") .. " -c $(CFLAGS)")
    mf:write ("\n\n")
end

mf:write ("obj:\n\tmkdir obj\n\n")
mf:write ("clean:\n\trm -r obj")
