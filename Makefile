CC=g++ -std=c++11
CFLAGS=-I. -I.. -g 
EXE=tracey

$(EXE): main.o perspectivecamera.o boundingbox.o color.o texture.o vector2d.o vector3d.o pointlight.o spotlight.o ambientlight.o infiniteplane.o sphere.o triangle.o smoothtriangle.o objmodel.o simplerenderer.o scene.o simplescene.o flatshader.o lambertshader.o mirrorshader.o refractionshader.o simpleshadowshader.o
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
