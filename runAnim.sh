#!/bin/bash
for i in {0..110}
do
	echo "$i"
   ./bin/RayTracer "$i" "$i"
   
done
echo "Fin Render"
cd imagenes
#mkdir temp
echo "Convertir Imágenes"
convert *.ppm temp/%05d.jpg
#cp *.jpg temp/.
#convert temp/*.jpg -delay 10 -morph 10 temp/%05d.jpg
#echo "Creando video"
#export LD_LIBRARY_PATH=/usr/local/lib
#ffmpeg -r 25 -qscale 2  -i temp/%05d.jpg output.mp4
#rm -R temp
cd ..
