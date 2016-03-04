g++ -o main DisplayImage.cpp $(pkg-config opencv --cflags --libs)
./main lena.jpg
