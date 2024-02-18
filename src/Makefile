.PHONY: all compile_sanity compile_data run_sanity run_individual run_tests clean_sanity clean_data clean

all: compile_sanity compile_data run_sanity run_tests

compile_sanity:
	cd Sanity_Checks && make > ../log.txt 2>&1 && cd ..

compile_data:
	cd Data_Testing && make >> ../log.txt 2>&1 && cd ..

run_sanity: run_ChainingTest run_CuckooHashingTest run_OpenAddressingTest

run_ChainingTest:
	./Executables/ChainingTest >> log.txt 2>&1

run_CuckooHashingTest:
	./Executables/CuckooHashingTest >> log.txt 2>&1

run_OpenAddressingTest:
	./Executables/OpenAddressingTest >> log.txt 2>&1

run_tests:
	./Executables/MainTest >> log.txt 2>&1

clean_sanity:
	cd Sanity_Checks && make clean >> ../log.txt 2>&1 && cd ..

clean_data:
	cd Data_Testing && make clean >> ../log.txt 2>&1 && cd ..

clean: clean_sanity clean_data