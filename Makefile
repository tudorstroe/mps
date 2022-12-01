build:
	g++ -std=c++17 main_global.cpp -o main_global -lstdc++fs
	g++ -std=c++17 check_global.cpp -o check_global -lstdc++fs

run_main_global:
	./main_global

run_check_global:
	./check_global

run_check_local:
	./check_local

clean:
	rm -f main_global check_global