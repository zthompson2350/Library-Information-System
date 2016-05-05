CC=g++
CFLAGS=-I.
DEPS = banners.h controller.h item.h fiction.h nonfiction.h user.h owner.h employee.h patron.h scanner.h


LIS: main.cpp banners.cpp controller.cpp user.cpp owner.cpp employee.cpp
	$(CC) -o LIS main.cpp banners.cpp controller.cpp user.cpp owner.cpp employee.cpp -I.
