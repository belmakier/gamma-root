prefix = "./built"
opts = 

# makefile uses bash
SHELL:=/bin/bash
build:
	@echo "------------------------------------------------"
	@echo ":: SETTING UP FOR BUILD."
	@echo ":: make build prefix=${prefix}"
	@echo ":: opts=${opts}"
	@echo "------------------------------------------------"
	mkdir build; cd build; cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo  -DCMAKE_INSTALL_PREFIX=${prefix} -DBUILD_TESTING=ON ${opts} ..
	@echo ""
	@echo "------------------------------------------------"
	@echo ":: SETUP COMPLETE. cd build; {make/ninja} help"
	@echo ":: Run make clean here to start over"
	@echo "------------------------------------------------"	

lazy:
	mkdir build; cd build; cmake -DCMAKE_BUILD_TYPE=RELEASE  -DCMAKE_INSTALL_PREFIX="~/.local" ${opts} ..; make -j$(nproc) --no-print-directory; echo "Installing..."; make install > install.log

format:
	find src/ -iname '*.hh' | xargs clang-format -i -style=file
	find src/ -iname '*.tt' | xargs clang-format -i -style=file
	find src/ -iname '*.cc' | xargs clang-format -i -style=file

lazydoc:
	cd build; make doc --no-print-directory; echo "Installing docs..."; make install > install.log;

verylazy: clean lazy lazydoc

	@echo ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
	@echo ░░░░░░░▄▄▀▀▀▀▀▀▀▀▀▀▄▄█▄░░░░▄░░░░█░░░░░░░
	@echo ░░░░░░█▀░░░░░░░░░░░░░▀▀█▄░░░▀░░░░░░░░░▄░
	@echo ░░░░▄▀░░░░░░░░░░░░░░░░░▀██░░░▄▀▀▀▄▄░░▀░░
	@echo ░░▄█▀▄█▀▀▀▀▄░░░░░░▄▀▀█▄░▀█▄░░█▄░░░▀█░░░░
	@echo ░▄█░▄▀░░▄▄▄░█░░░▄▀▄█▄░▀█░░█▄░░▀█░░░░█░░░
	@echo ▄█░░█░░░▀▀▀░█░░▄█░▀▀▀░░█░░░█▄░░█░░░░█░░░
	@echo ██░░░▀▄░░░▄█▀░░░▀▄▄▄▄▄█▀░░░▀█░░█▄░░░█░░░
	@echo ██░░░░░▀▀▀░░░░░░░░░░░░░░░░░░█░▄█░░░░█░░░
	@echo ██░░░░░░░░░░░░░░░░░░░░░█░░░░██▀░░░░█▄░░░
	@echo ██░░░░░░░░░░░░░░░░░░░░░█░░░░█░░░░░░░▀▀█▄
	@echo ██░░░░░░░░░░░░░░░░░░░░█░░░░░█░░░░░░░▄▄██
	@echo ░██░░░░░░░░░░░░░░░░░░▄▀░░░░░█░░░░░░░▀▀█▄
	@echo ░▀█░░░░░░█░░░░░░░░░▄█▀░░░░░░█░░░░░░░▄▄██
	@echo ░▄██▄░░░░░▀▀▀▄▄▄▄▀▀░░░░░░░░░█░░░░░░░▀▀█▄
	@echo ░░▀▀▀▀░░░░░░░░░░░░░░░░░░░░░░█▄▄▄▄▄▄▄▄▄██

opendoc:
	xdg-open build/docs/html/index.html

getreqs:
	@echo "------------------------------------------------"
	@echo ":: Updating / initializing submodules"
	@echo "------------------------------------------------"
	git submodule update --recursive --remote --init

clean:
	rm -rf build

.PHONY:
	build lazy lazydocs format getreqs clean
