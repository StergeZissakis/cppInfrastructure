BUILD_DIRECTORIES= share src


all:
	$(foreach dir,$(BUILD_DIRECTORIES), $(MAKE) -C $(dir) $@; )

install: all
	$(foreach dir,$(BUILD_DIRECTORIES), $(MAKE) -C $(dir) $@; )

clean:
	$(foreach dir,$(BUILD_DIRECTORIES), $(MAKE) -C $(dir) $@; )
	rm -f bin/* lib/*

test: install





