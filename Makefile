CC=g++ -std=c++11
CFLAGS=-I. -I.. -g
EXE=tracey

$(EXE): main.o progressbar.o perspectivecamera.o boundingbox.o color.o texture.o vector2d.o vector3d.o ambientlight.o directionallight.o pointlight.o infiniteplane.o sphere.o triangle.o smoothtriangle.o objmodel.o simplerenderer.o depthrenderer.o desaturationrenderer.o hazerenderer.o scene.o simplescene.o flatshader.o lambertshader.o mirrorshader.o refractionshader.o simpleshadowshader.o brdfshader.o phongshader.o
	$(CC) $(CFLAGS) -o $@ $^

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
