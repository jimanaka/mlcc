mlcc:
	$(MAKE) -C c/

commands:
	rm -f mlcc
	bear -- $(MAKE) -C c/

clean:
	$(MAKE) -C c/ clean


