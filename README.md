# dog_feeder
개 오줌사면 밥주기

opencv 필요

build 
> g++ -c detect_dog_pee/detectMain.cpp -I./src <br>
> g++ -c src/DogPeeDetector.cpp <br>
> g++ DogPeeDetector.o detectMain.o -o dog "`pkg-config opencv --cflags --libs`" <br>
> ./dog dog.jpg <br>

so 없다하면

export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/local/lib
