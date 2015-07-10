#-----------Comentar luego de la primera ejecucion---------------------
#sudo apt-get install --install-recommends jstest* joystick xboxdrv 
#----------------------------------------------------------------------
sudo echo "PASO 1) blacklist xpad" | sudo tee -a /etc/modprobe.d/blacklist.conf
echo "PASO 2) rmmod xpad"
rmmod xpad
echo "PASO 3) xboxdrv --silent --config ROBOCOL.xboxdrv --detach-kernel-driver"
#Este paso falla cuando se conecta el control de JMGG, pero sirve con el control de Robocol.
sudo xboxdrv --silent --detach-kernel-driver --config ROBOCOL.xboxdrv
