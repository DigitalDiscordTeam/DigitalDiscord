files = src/mac.cpp src/InternalSys.cpp src/InternalErrors.cpp src/InternalErrorLogger.cpp src/Cryp.cpp src/InternalLib.cpp src/Memory.cpp src/InternalFsys.cpp src/InternalEvents.cpp src/InternalFileVec.cpp src/InternalPrettyConsoleOut.cpp src/Chars.cpp src/CommandFile.cpp src/Game.cpp src/Terminal.cpp src/main.cpp

dist/DigitalDiscord.exe: $(files) logs dist
	@echo Compiling 
	g++ $(files) -std=c++17 -o dist/DigitalDiscord.exe -static 2> logs/`date +%Y-%m-%d--%H-%M-%S`
	@echo Done! If you're on Linux, just execute DigitalDiscord.exe, it's a linux binary if built on linux even though it has .exe in its name

dist:
	mkdir dist

logs:
	mkdir logs

clean:
	rm -rf dist logs
