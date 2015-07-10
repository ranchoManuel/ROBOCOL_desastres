package comunicacionSerial;

import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.Enumeration;

public class Comunicacion_USART implements SerialPortEventListener
{
	/** The streams to the port, and the port */
	private BufferedReader input;
	private OutputStream output;
	private SerialPort serialPort;
	private String leido;

	private Control mainControl;

	@SuppressWarnings("rawtypes")
	public Comunicacion_USART(Control control, String port_name, int time_out, int data_rate) throws IOException
	{
		mainControl=control;

		CommPortIdentifier portId=null;
		Enumeration portEnum=CommPortIdentifier.getPortIdentifiers();

		System.out.println("----------Puertos Disponibles----------");
		// iterate through, looking for the port
		while(portEnum.hasMoreElements())
		{
			CommPortIdentifier currPortId=(CommPortIdentifier)portEnum.nextElement();
			System.out.println("\t"+currPortId.getName());

			if(port_name.equals(currPortId.getName())) portId=currPortId;
		}
		System.out.println("---------------------------------------");

		if(portId!=null)
		{
			try
			{
				// open serial port, and use class name for the appName.
				serialPort=(SerialPort)portId.open(this.getClass().getName(),time_out);

				// set port parameters
				serialPort.setSerialPortParams(data_rate,SerialPort.DATABITS_8, SerialPort.STOPBITS_1,SerialPort.PARITY_NONE);

				// open the streams
				output=serialPort.getOutputStream();
				input=new BufferedReader(new InputStreamReader(serialPort.getInputStream()));

				// add event listeners
				serialPort.addEventListener(this);
				serialPort.notifyOnDataAvailable(true);
			}
			catch(Exception e){e.printStackTrace();}
		}
		else System.err.println("No se pudo encontara el puerto de comunicacion: "+port_name);
	}


	public void enviarLinea(String linea)
	{
		try
		{
			output.write(linea.getBytes());
		}
		catch(IOException e) {e.printStackTrace();}
	}

	@Override
	public synchronized void serialEvent(SerialPortEvent oEvent)
	{
		if(oEvent.getEventType()==SerialPortEvent.DATA_AVAILABLE)
		{
			try
			{
				while((leido=input.readLine())!=null)
					mainControl.tomarDato(leido);
			}
			catch(Exception e){/*System.err.print(".");*/}
		}
		else System.out.println("OTRO TIPO DE EVENTO: "+oEvent.getEventType());
	}

	public void close()
	{
		if(serialPort!=null)
		{
			serialPort.removeEventListener();
			serialPort.close();
		}
	}
}