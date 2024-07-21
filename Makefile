#VCPKG_INSTALLED = ./vcpkg_installed/x64-linux
#VCPKG_PKGCONFIG = ${VCPKG_INSTALLED}/lib/pkgconfig

CC = gcc-13 -Wall -Wpedantic
CCFLAGS = --std=gnu2x#-O3
LDFLAGS = 
INCLUDES = -I"./library"
LIBRARIES = -lm

EXECUTABLE = raytracing.exe
OBJECTS = linalg.o Array.o Ray.o Hittables.o Hittable.o Camera.o Interval.o HitRecord.o main.o
BUILD = build
OBJECTS := $(addprefix $(BUILD)/,$(OBJECTS))

all: $(BUILD) $(EXECUTABLE)
$(BUILD):
	mkdir -p ./$@/
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(CCFLAGS) -o $@ $+ $(LIBRARIES)
$(BUILD)/main.o: main.c
	$(CC) $(INCLUDES) $(CCFLAGS) -o $@ -c $<
$(BUILD)/linalg.o: library/linear/MatrixN.c library/linear/Matrix.c library/linear/VectorN.c library/linear/Vector.c
	$(CC) $(INCLUDES) $(CCFLAGS) -o $@ library/linear/*.c -shared
$(BUILD)/Hittable.o: Hittable/Sphere.c Hittable/Hittable.c
	$(CC) $(INCLUDES) $(CCFLAGS) -o $@ Hittable/*.c -shared
$(BUILD)/Array.o: library/rxi/Array.c
	$(CC) $(INCLUDES) $(CCFLAGS) -o $@ -c $<
$(BUILD)/Hittables.o: Hittables.c
	$(CC) $(INCLUDES) $(CCFLAGS) -o $@ -c $<
$(BUILD)/Ray.o: Ray.c
	$(CC) $(INCLUDES) $(CCFLAGS) -o $@ -c $<
$(BUILD)/Camera.o: Camera.c
	$(CC) $(INCLUDES) $(CCFLAGS) -o $@ -c $<
$(BUILD)/Interval.o: Interval.c
	$(CC) $(INCLUDES) $(CCFLAGS) -o $@ -c $<
$(BUILD)/HitRecord.o: HitRecord.c
	$(CC) $(INCLUDES) $(CCFLAGS) -o $@ -c $<
clean:
	rm -f $(EXECUTABLE) ./build/*

#bear -- make
