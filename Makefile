a.out: main.cpp
	g++ main.cpp -llz4 -lopencv_core -lopencv_highgui -lopencv_imgproc
