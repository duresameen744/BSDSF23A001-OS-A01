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
