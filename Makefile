papi:
	cd src/Papi_Testing && $(MAKE) clean && $(MAKE) && $(MAKE) run-papi

results:
	cd test && $(MAKE) run-final > ignore.txt

papi-results:
	$(MAKE) run-papi
	$(MAKE) make-results