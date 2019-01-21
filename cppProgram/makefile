CFLAGS = -I ~/Downloads/Eigen -I ~/Downloads/boost

proj.exe: main.o GlrmClass.o QRPcaClass.o QSPcaClass.o RSPcaClass.o 
	g++ main.o GlrmClass.o QRPcaClass.o QSPcaClass.o RSPcaClass.o -o proj.exe

main.o: main.cpp
	g++ -c main.cpp $(CFLAGS) -o main.o

GlrmClass.o: GlrmClass.h GlrmClass.cpp
	g++ -c GlrmClass.cpp $(CFLAGS) -o GlrmClass.o

QRPcaClass.o: QRPcaClass.h QRPcaClass.cpp
	g++ -c QRPcaClass.cpp $(CFLAGS) -o QRPcaClass.o

QSPcaClass.o: QSPcaClass.h QSPcaClass.cpp
	g++ -c QSPcaClass.cpp $(CFLAGS) -o QSPcaClass.o

RSPcaClass.o: RSPcaClass.h RSPcaClass.cpp
	g++ -c RSPcaClass.cpp $(CFLAGS) -o RSPcaClass.o

clean:
	rm -rf main.o GlrmClass.o QRPcaClass.o QSPcaClass.o RSPcaClass.o proj.exe
