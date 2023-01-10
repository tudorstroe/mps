build:
	g++ -std=c++17 main_global.cpp -o main_global -lstdc++fs
	g++ -std=c++17 main_local.cpp -o main_local -lstdc++fs
	g++ -std=c++17 check_global.cpp -o check_global -lstdc++fs
	g++ -std=c++17 check_local.cpp -o check_local -lstdc++fs

run_main_global:
	./main_global

run_main_local:
	./main_local

run_check_global:
	./check_global

run_check_local:
	./check_local

clean:
	rm -f main_global check_global main_local check_local