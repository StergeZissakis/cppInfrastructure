
all: googletest googletest/libgtest.a install


install: 
	install `find . -name libgtest\*.a -type f` ../lib
	cp -Raf googletest/googletest/include/* ../include/

clean:
	rm -rf googletest
	rm -rf ../include/gtest
	rm -rf ../lib/libgtest*

googletest: 
	git clone https://github.com/google/googletest.git

googletest/libgtest.a: 
	cmake -B./googletest -H./googletest
	$(MAKE) -C googletest
