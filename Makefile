SUBDIRS := src

.PHONY: all clean $(SUBDIRS)
all: $(SUBDIRS)
	@echo "Build complete."

# For each subdirectory run make inside it
$(SUBDIRS):
	$(MAKE) -C $@

# Clean target: ask subdirs to clean
clean:
	@for dir in $(SUBDIRS); do \
	  $(MAKE) -C $$dir clean; \
	done
	@echo "Clean complete."
install: all
	mkdir -p /usr/local/bin
	mkdir -p /usr/local/share/man/man1
	cp ./bin/client /usr/local/bin/client
	cp ./man/man1/client.1 /usr/local/share/man/man1/client.1
	@echo "Installed client and its man page."
