
echo "Los ejecutables quedan en la carpeta Ejecutables"
####################################
#            PASO 1                #
####################################

#Entro a la carpeta correcta
echo "Paso 1: crear cliente java"
cd Cliente_Java
#Compilo el cliente en un jar
javac ClienteChat.java AuxThread.java
echo "Main-Class: ClienteChat" > Manifest.txt
jar cfm ClienteChat.jar Manifest.txt ClienteChat.class AuxThread.class

#Muevo el jar a la carpeta de ejecutables
mv ClienteChat.jar ../Ejecutables/

#Borro los binarios
rm *.txt && rm *.class

####################################
#            PASO 2                #
####################################

echo "Paso 2: crear cliente c"
cd ../Cliente_c
gcc -pthread -o chatClient main.c comn_sockets.c
mv chatClient ../Ejecutables/

####################################
#            PASO 3                #
####################################

echo "Paso 3: crear servidor c"
cd ../Servidor_c
gcc -pthread -o chatServer main.c comn_sockets1.c comn_sockets2.c
mv chatServer ../Ejecutables/
