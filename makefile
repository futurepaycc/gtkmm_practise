# https://www.unix.com/programming/168019-how-define-dynamic-target-prerequisite-makefile.html (成功)
# https://stackoverflow.com/questions/21585080/make-with-dynamic-target-names (失败)
# make sourcename=button1
build = g++ -g `pkg-config --cflags-only-I --libs gtkmm-3.0` `pkg-config --cflags --libs webkit2gtk-4.0` `pkg-config --cflags --libs goocanvasmm-2.0`

all:
	${build} ${sourcename}.cpp -o bin/${sourcename}

# make test sourcename=hello 
test:
	@echo ${sourcename}


# 下面是手工版
# gtkmm1: gtkmm1.cpp
# 	g++ -g `pkg-config --cflags-only-I --libs gtkmm-3.0` gtkmm1.cpp -o bin/gtkmm1 

# button1: button1.cpp
# 	g++ -g `pkg-config --cflags-only-I --libs gtkmm-3.0` button1.cpp -o bin/button1 