run:
	@echo "" > ./temp/test.txt && \
	cat $(FILE) >> ./temp/test.txt && \
	python3 ./scripts/process.py

run-all:
	$(MAKE) run FILE=$(FILE1)
	mv ./temp/output.json ./p_input/output1.json
	$(MAKE) run FILE=$(FILE2)
	mv ./temp/output.json ./p_input/output2.json
	$(MAKE) run FILE=$(FILE3)
	mv ./temp/output.json ./p_input/output3.json
	python3 ./scripts/graphCache.py

run-dir-all:
	$(MAKE) run-all FILE1=./input/file1.txt FILE2=./input/file2.txt FILE3=./input/file3.txt
	
run-final:
	python3 produceFiles.py
	python3 groupFiles.py
	python3 graph_all.py

run-sample:
	python3 graph_all.py

run-graph:
	python3 ./scripts/process.py