.PHONY: all compile_sanity compile_data run_sanity run_individual run_tests clean_sanity clean_data clean

all: compile_sanity compile_data run_sanity run_tests

compile_sanity:
	cd Sanity_Checks && make && cd ..

compile_data:
	cd Data_Testing && make && cd ..

run_sanity: run_ChainingTest run_CuckooHashingTest run_OpenAddressingTest

run_ChainingTest:
	./Executables/ChainingTest && cd ..

run_CuckooHashingTest:
	./Executables/CuckooHashingTest && cd ..

run_OpenAddressingTest:
	./Executables/OpenAddressingTest && cd ..

run_tests:
	./Executables/MainTest

clean_sanity:
	cd Sanity_Checks && make clean && cd ..

clean_data:
	cd Data_Testing && make clean && cd ..

clean: clean_sanity clean_data