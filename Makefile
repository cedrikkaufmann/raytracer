CC=/usr/local/Cellar/llvm/3.9.1/bin/clang++ -std=c++11 -fopenmp -march=native -O3 -pipe
CFLAGS=-I. -I.. -I/usr/local/opt/llvm/include
LDFLAGS=-L/usr/local/opt/llvm/lib
EXE=tracey

$(EXE): main.o progressbar.o perspectivecamera.o omnidirectionalcamera.o boundingbox.o kdtree.o texture.o spotlight.o ambientlight.o directionallight.o pointlight.o infiniteplane.o sphere.o triangle.o smoothtriangle.o texturedtriangle.o objmodel.o depthoffieldrenderer.o superrenderer.o simplerenderer.o backgroundrenderer.o depthrenderer.o desaturationrenderer.o hazerenderer.o scene.o simplescene.o toonshader.o flatshader.o lambertshader.o mirrorshader.o refractionshader.o simpleshadowshader.o materialshader.o brdfshader.o phongshader.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

main.o: main.cpp
	$(CC) -I. -g -c $<

%.o: camera/%.cpp
	$(CC) $(CFLAGS) -I. -g -c $<

%.o: common/%.cpp
	$(CC) $(CFLAGS) -I. -g -c $<

%.o: light/%.cpp
	$(CC) $(CFLAGS) -I. -g -c $<

%.o: primitive/%.cpp
	$(CC) $(CFLAGS) -I. -g -c $<

%.o: renderer/%.cpp
	$(CC) $(CFLAGS) -I. -g -c $<

%.o: scene/%.cpp
	$(CC) $(CFLAGS) -I. -g -c $<

%.o: shader/%.cpp
	$(CC) $(CFLAGS) -I. -g -c $<

clean:
	rm -f *.o *~ $(EXE)
