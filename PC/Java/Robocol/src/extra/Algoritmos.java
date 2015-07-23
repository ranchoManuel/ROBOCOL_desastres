package extra;

public class Algoritmos
{
	private static final double TO_ANG  = 180.0/Math.PI;
	
	public static double map(double value, double start1, double stop1, double start2, double stop2)
	{
		return start2+(stop2-start2)*((value-start1)/(stop1-start1));
	}
	
	public static double anguloEntreVectores3D(double[] a, double[] b)
	{
		double nA=Math.sqrt(a[0]*a[0]+a[1]*a[1]+a[2]*a[2]);
		double nB=Math.sqrt(b[0]*b[0]+b[1]*b[1]+b[2]*b[2]);
		return Math.acos((a[0]*b[0]+a[1]*b[1]+a[2]*b[2])/(nA*nB));
	}
	
	public static void main(String[] args)
	{
		double[] a={0,0,1};
		double[] b={1,0,0};
		System.out.println(anguloEntreVectores3D(a, b)*TO_ANG);
	}
}